#include "FFiveGame.h"
#include <random>

FFiveRandomPlayer::FFiveRandomPlayer(QChar symbol)
	: game(nullptr), symbol(symbol), name("Random Player")
{
}

FFiveRandomPlayer::FFiveRandomPlayer(QChar symbol, const QColor& color)
	: game(nullptr), name("Random Player"), color(color), symbol(symbol)
{
}

QChar FFiveRandomPlayer::getSymbol()
{
    return symbol;
}

QColor FFiveRandomPlayer::getColor()
{
    return color;
}

QString FFiveRandomPlayer::getName()
{
    return name;
}

void FFiveRandomPlayer::setGame(Game* game)
{
    this->game = game;
}

void FFiveRandomPlayer::getMove()
{
    srand(time(nullptr));
    int index = rand() % 25;

    while (!game->updateBoard(symbol, color, index))
    {
        index = rand() % 25;
    }

    game->onButtonClick(-1);
}