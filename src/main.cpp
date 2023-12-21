// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

//#include "5x5/FFiveGame.h"
//#include "Pyramid/PyramidGame.h"
#include "Connect4/Connect4Game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Game* game = new Connect4Game("Sayed", "Mohammed");
    game->show();

    return a.exec();
}
