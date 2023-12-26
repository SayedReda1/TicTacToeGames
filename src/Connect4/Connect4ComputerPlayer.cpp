#include "Connect4Game.h"
#include <random>

Connect4ComputerPlayer::Connect4ComputerPlayer(Game* game, QChar symbol)
    : game(game), symbol(symbol), name("Computer Player")
{
}

Connect4ComputerPlayer::Connect4ComputerPlayer(Game* game, QChar symbol, const QColor& color)
    : game(game), name("Computer Player"), color(color), symbol(symbol)
{
}

QChar Connect4ComputerPlayer::getSymbol()
{
    return symbol;
}

QColor Connect4ComputerPlayer::getColor()
{
    return color;
}

QString Connect4ComputerPlayer::getName()
{
    return name;
}

void Connect4ComputerPlayer::getMove()
{
    // Generate random stack index;
    srand(time(nullptr));
    int x = rand() % 7;

    // Try to update the board;
    while (!game->updateBoard(symbol, x))
        x = rand() % 7;

    game->onButtonClick(-1);
}