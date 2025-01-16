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

    Button login_button;
    login_button.setSize(Size(20, 3));
    login_button.setPosition(Point(30, 20));
    login_button.setLabel("Zaloguj");
    login_button.setOnClick([](Button& button) { std::cout << "Zalogowano!\n"; });

    login_form.addWidget(login_button);
    
    gui.openWindow(login_form);

    gui.start();
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    return EXIT_SUCCESS;
}