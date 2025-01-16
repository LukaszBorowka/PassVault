#include "../hpp/Gui.hpp"


Gui::Gui()
{
    //std::cout << "starting...\n";
    setPolishLocale();
    enableRawMode();
    switchToSecondBuffer();
    updateTerminalSize();
    hideCursor();

    //this->isRunning = true;

    this->force_refresh_screen_buffer = true; // set this flag so that the initial render is performed fully, with no optimization
}

Gui::~Gui()
{
    disableRawMode();
    switchToMainBuffer();
    showCursor();
    //std::cout << "terminating...\n";
    if (on_close) on_close(*this);
}

void Gui::start()
{
    this->isRunning = true;

    while (this->isRunning)
    //for (int i = 0; i < 3*this->max_fps; i++)
    {
        this->frame_start_time = std::chrono::steady_clock::now();
        this->readInputStream();
        this->handleInputs();
        this->render();
        this->limitRefreshRate();
    }
}

void Gui::close()
{
    this->isRunning = false;
}

void Gui::setMaxFPS(int max_fps) 
{
    this->max_fps = max_fps;
    this->target_frame_duration = 1000/max_fps;
}

int Gui::getMaxFPS()
{
    return this->max_fps;
}

void Gui::setOnClose(std::function<void(Gui&)> on_close)
{
    this->on_close = on_close;
}

void Gui::openWindow(Window& window)
{
    window_stack.push(window);
    if(window.on_open) window.on_open(window);
}

void Gui::closeTopWindow()
{
    if (window_stack.empty()) return; // early exit if no windows are open
    if (window_stack.top().get().on_close) window_stack.top().get().on_close(window_stack.top().get()); // if window has an on_close, call it
    window_stack.pop(); // remove top window from stack
}

// private

void Gui::limitRefreshRate()
{
    auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - frame_start_time).count();
    int sleep_time = target_frame_duration - frame_duration;
    if (sleep_time > 0) std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
}

void Gui::updateTerminalSize()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w))
    {
        std::cout << "Could now get terminal size.\n";
        return; // exit if ioctl returns error (return not 0)
    }
    terminal_size.w = w.ws_col;
    terminal_size.h = w.ws_row;
}

void Gui::enableRawMode()
{
    tcgetattr(STDIN_FILENO, &oldt);             // save terminal settings
    newt = oldt;                                // copy them
    newt.c_lflag &= ~ICANON;                    // disable canonical mode
    newt.c_lflag &= ~ECHO;                      // disable echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    // apply
}

void Gui::disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);    // restore terminal setting (enable canonical and echoing)
}

void Gui::readInputStream()
{
    char ch;

    //read(STDIN_FILENO, &ch, 1);
    //codes.push_back(ch);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);        // save read() behaviour flags
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);   // enable non-blocking

    while (read(STDIN_FILENO, &ch, 1) > 0) this->input_queue.push(ch); // as long as anything is read, push it to the queue

    fcntl(STDIN_FILENO, F_SETFL, flags);        // restore the original read() flags (disable non-blocking)
}

void Gui::switchToSecondBuffer()
{
    std::cout << "\033[?1049h" << "\033[2J" << "\033[H" << std::flush;
}

void Gui::switchToMainBuffer()
{
    std::cout << "\033[?1049l" << std::flush;
}

void Gui::hideCursor()
{
    std::cout << "\033[?25l" << std::flush;
}

void Gui::showCursor()
{
    std::cout << "\033[?25h" << std::flush;
}

int Gui::setPolishLocale()
{
    try
    {
        std::locale polish("pl_PL.UTF-8");
        std::locale::global(polish);
        std::cout.imbue(polish);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Nie udalo sie wlaczyc jezyka polskiego w Twoim terminalu.\n";
        std::cout << "Sprawdz, czy posiadasz zainstalowany pakiet jezyka polskiego uzywajac \"locale -a\".\n";
        std::cout << "Jezeli na liscie zaistalowanych jezykow brakuje \"pl_PL.UTF-8\" mozesz go zainstalowac uzywajac:\n";
        std::cout << "   sudo locale-gen pl_PL.UTF-8\n";
        std::cout << "   sudo update-locale\n";
        std::cout << "Uwaga! Aplikacja moze nie dzialac poprawnie. Zalecane zamkniecie aplikacji i zainstalowanie jezyka polskiego." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void Gui::handleInputs()
{
    while (!this->input_queue.empty())
    {
        this->input_queue.pop();
    }
}

void Gui::render()
{
    Window& window = window_stack.top().get();

    updateTerminalSize();
    if ((window.size.w + 2 > terminal_size.w) || (window.size.h + 2 > terminal_size.h))
    {
        std::cout << "\033[2J" << "\033[H"; // clear, go to top left
        std::cout << "Za mały terminal, aby wyświetlić okno.\nMinimalny rozmiar: " << window.size.w + 2 << "x" << window.size.h + 2 << "\nRozmiar Twojego terminala: " << this->terminal_size.w << "x" << this->terminal_size.h << std::endl;
        return;
    }

    window.render();
    Pixel window_buffer[window.size.w][window.size.h];
    for (int x = 0; x < window.size.w; x++)
    {
        for (int y = 0; y < window.size.h; y++)
        {
            window_buffer[x][y] = window.getPixelFromRender(Point(x, y));
        }
    }

    // currently no optimization is set up so no matter if force_refresh_screen_buffer is set

    int top_margin = (terminal_size.h - window.size.h - 2) / 2;
    int left_margin = (terminal_size.w - window.size.w - 2) / 2;

    std::cout << "\033[2J" << "\033[H";

    //std::cout << "\033[40m";
    for (int i = 0; i < top_margin; i++) std::cout << "\n";
    for (int i = 0; i < left_margin; i++) std::cout << " ";
    for (int i = 0; i < window.size.w + 2; i++) std::cout << "█";
    std::cout << "\n";
    for (int y = 0; y < window.size.h; y++)
    {
        for (int i = 0; i < left_margin; i++) std::cout << " ";
        std::cout << "█";
        for (int x = 0; x < window.size.w; x++) std::cout << window_buffer[x][y].ch;
        std::cout << "█";
        std::cout << "\n";
    }
    for (int i = 0; i < left_margin; i++) std::cout << " ";
    for (int i = 0; i < window.size.w + 2; i++) std::cout << "█";
    //std::cout << "\033[0m";
    std::cout << std::flush;

}