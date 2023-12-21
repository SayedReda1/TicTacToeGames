#include "FFiveGame.h"
#include <random>

FFiveComputerPlayer::FFiveComputerPlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol), name("Random Player")
{
}

FFiveComputerPlayer::FFiveComputerPlayer(Game* game, QChar symbol, const QColor& color)
	: game(game), name("Random Player"), color(color), symbol(symbol)
{
}

QChar FFiveComputerPlayer::get_symbol()
{
    return symbol;
}

QColor FFiveComputerPlayer::get_color()
{
    return color;
}

QString FFiveComputerPlayer::get_name()
{
    return name;
}

void FFiveComputerPlayer::get_move()
{
    srand(time(nullptr));
    int index = rand() % 25;

    while (!game->update_board(symbol, index))
    {
        index = rand() % 25;
    }

    game->onButtonClick(index);
}