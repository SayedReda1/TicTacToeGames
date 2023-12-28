#include "Connect4Game.h"
#include <random>

Connect4RandomPlayer::Connect4RandomPlayer(QChar symbol)
    : game(nullptr), symbol(symbol), name("Random Player")
{
}

Connect4RandomPlayer::Connect4RandomPlayer(QChar symbol, const QColor& color)
    : game(nullptr), name("Random Player"), color(color), symbol(symbol)
{
}

QChar Connect4RandomPlayer::getSymbol()
{
    return symbol;
}

QColor Connect4RandomPlayer::getColor()
{
    return color;
}

QString Connect4RandomPlayer::getName()
{
    return name;
}

void Connect4RandomPlayer::setGame(Game* game)
{
    this->game = game;
}

void Connect4RandomPlayer::getMove()
{
    // Generate random stack index;
    srand(time(nullptr));
    int x = rand() % 7;

    // Try to update the board;
    while (!game->updateBoard(symbol, color, x))
        x = rand() % 7;

    game->onButtonClick(-1);
}