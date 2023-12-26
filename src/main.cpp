// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "Main/HomeWindow.h"
#include <QStackedWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QStackedWidget stack;

    stack.setStyleSheet("background-color: #0F0F0F; ");
    stack.insertWidget(0, new HomeWindow(&stack));
    stack.show();


    return a.exec();
}
