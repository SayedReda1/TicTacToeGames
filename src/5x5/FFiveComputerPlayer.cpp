#include "FFiveGame.h"
#include <random>

FFiveComputerPlayer::FFiveComputerPlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol), name("Computer Player")
{
}

FFiveComputerPlayer::FFiveComputerPlayer(Game* game, QChar symbol, const QColor& color)
	: game(game), name("Computer Player"), color(color), symbol(symbol)
{
}

QChar FFiveComputerPlayer::getSymbol()
{
    return symbol;
}

QColor FFiveComputerPlayer::getColor()
{
    return color;
}

QString FFiveComputerPlayer::getName()
{
    return name;
}

void FFiveComputerPlayer::getMove()
{
    srand(time(nullptr));
    int index = rand() % 25;

    while (!game->updateBoard(symbol, index))
    {
        index = rand() % 25;
    }

    game->onButtonClick(index);
}