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
    login_form.setTitle("PassVault login");
    login_form.setSize(Size(29, 8));

    Label hello_label;
    hello_label.setSize(Size(19, 1));
    hello_label.setPosition(Point(5, 2));
    hello_label.setContent("Witaj! Wprowadź PIN");
    login_form.addLabel(hello_label);

    Label passw_label;
    passw_label.setSize(Size(30, 1));
    passw_label.setPosition(Point(8, 5));
    passw_label.setContent("[ ][ ][ ][ ]");
    login_form.addLabel(passw_label);
    
    gui.openWindow(login_form);

    gui.start();

    return EXIT_SUCCESS;
}