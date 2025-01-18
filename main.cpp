#include <iostream>
#include <csignal>

#include "Gui/hpp/Gui.hpp"

Gui gui;

bool ctrlc_signal = false;

void ctrlcSignal(int s)
{
    gui.close();
}

//
// DON'T USE POLISH CHARACTERS YET, THEY BREEEEAK A LOT OF STUFF !!
//

int main()
{
    std::signal(SIGINT, ctrlcSignal);

    Window login_form;
    login_form.setTitle("PassVault login");
    login_form.setSize(Size(29, 8));

    Widget hello_label;
    hello_label.setSize(Size(19, 1));
    hello_label.setPosition(Point(5, 2));
    hello_label.setContent("Witaj! Wprowadz PIN");
    login_form.addWidget(hello_label);

    Widget passw_label;
    passw_label.setSize(Size(30, 1));
    passw_label.setPosition(Point(8, 5));
    passw_label.setContent("[ ][ ][ ][ ]");
    login_form.addWidget(passw_label);

    // Widget symbols;
    // symbols.setSize(Size(30,1));
    // symbols.setPosition(Point(0, 6));
    // symbols.setContent("🔒 🔓 🛡 • ");
    // login_form.addWidget(symbols);
    
    gui.openWindow(login_form);

    gui.start();
    //std::this_thread::sleep_for(std::chrono::seconds(2));

    return EXIT_SUCCESS;
}