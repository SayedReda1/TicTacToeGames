#include "Pyramid/PyramidGame.h"
#include <random>

PyramidRandomPlayer::PyramidRandomPlayer(QChar symbol)
    : game(nullptr), symbol(symbol), name("Random Player")
{
}

PyramidRandomPlayer::PyramidRandomPlayer(QChar symbol, const QColor& color)
    : game(nullptr), name("Random Player"), color(color), symbol(symbol)
{
}

QChar PyramidRandomPlayer::getSymbol()
{
    return symbol;
}

QColor PyramidRandomPlayer::getColor()
{
    return color;
}

QString PyramidRandomPlayer::getName()
{
    return name;
}

void PyramidRandomPlayer::setGame(Game* game)
{
    this->game = game;
}

void PyramidRandomPlayer::getMove()
{
    // Generate random stack index;
    srand(time(nullptr));
    int x = rand() % 9;

    // Try to update the board;
    while (!game->updateBoard(symbol, color, x))
        x = rand() % 9;

    game->onButtonClick(-1);
}