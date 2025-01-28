#pragma once

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <vector>
#include <locale>
#include <sys/ioctl.h> // ioctl
#include <unistd.h> // sleep(seconds) function, STDOUT_FILENO
#include <thread>
#include <chrono>
#include <stack>
#include <functional>
#include <queue>

#include "Pixel.hpp"
#include "Point.hpp"
#include "Size.hpp"
#include "Window.hpp"
#include "UniStr.hpp"

class Window;

class Gui
{
public:

    Gui();
    ~Gui();

    void start();
    void close();

    void setMaxFPS(int max_fps);
    int getMaxFPS();

    void setOnClose(std::function<void(Gui&)> on_close);

    void openWindow(Window& window);
    void closeTopWindow();

private:

    bool is_running;

    struct termios oldt, newt;

    int max_fps = 25;
    int target_frame_duration = 1000/max_fps;
    std::chrono::time_point<std::chrono::steady_clock> frame_start_time;

    Size terminal_size;

    std::vector<std::vector<Pixel>> screen_buffer;
    bool force_refresh_screen_buffer;

    std::stack<std::reference_wrapper<Window>> window_stack;

    std::function<void(Gui&)> on_close;

    std::queue<char> input_queue;

    void limitRefreshRate();
    void updateTerminalSize();
    void enableRawMode();
    void disableRawMode();

    void readInputStream();

    void switchToSecondBuffer();
    void switchToMainBuffer();
    void hideCursor();
    void showCursor();

    int setPolishLocale();

    void handleInputs();

    void render();

    //friend class Window;
    
};