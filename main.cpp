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

    Widget login_label;
    login_label.setSize(Size(20, 1));
    login_label.setPosition(Point(5, 5));
    login_label.setContent("Login:");
    login_form.addWidget(login_label);

    Widget passw_label;
    passw_label.setSize(Size(20, 1));
    passw_label.setPosition(Point(5, 7));
    passw_label.setContent("Hasło:");
    login_form.addWidget(passw_label);
    
    gui.openWindow(login_form);

    gui.start();
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    return EXIT_SUCCESS;
}