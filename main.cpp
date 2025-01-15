#include <iostream>
#include <csignal>

#include "Gui/hpp/Gui.hpp"

Gui gui;

bool ctrlc_signal = false;

void ctrlcSignal(int s)
{
    gui.close();
}

int main()
{
    std::signal(SIGINT, ctrlcSignal);

    Window login_form;
    login_form.setTitle("Zaloguj się do aplikacji");
    login_form.setSize(Size(80, 25));
    
    gui.openWindow(login_form);

    gui.start();
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    return EXIT_SUCCESS;
}