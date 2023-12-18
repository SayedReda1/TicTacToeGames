// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramicGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Player* players[2] = { new Player('X'), new Player('O') };

    GameManager game(players);

    game.show();
    
    return a.exec();
}
