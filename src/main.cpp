// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "HomeFrame.h"
#include "FrameSwitcher.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FrameSwitcher switcher;

    switcher.setStyleSheet("background-color: #0F0F0F; ");
    switcher.insertWidget(0, new HomeFrame(&switcher));
    switcher.show();


    return a.exec();
}
