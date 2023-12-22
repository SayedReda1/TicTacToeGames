// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

//#include "5x5/FFiveGame.h"
//#include "Pyramid/PyramidGame.h"
//#include "Connect4/Connect4Game.h"
#include "Main/HomeWindow.h"
#include <QStackedWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QStackedWidget stack;

    stack.setStyleSheet("background-color: #0F0F0F; ");
    stack.insertWidget(0, new HomeWindow(&stack));
    stack.setCurrentIndex(0);

    stack.show();

    return a.exec();
}
