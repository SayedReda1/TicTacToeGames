#include "Connect4Game.h"
#include <random>

Connect4ComputerPlayer::Connect4ComputerPlayer(Game* game, QChar symbol)
    : game(game), symbol(symbol), name("Random Player")
{
}

Connect4ComputerPlayer::Connect4ComputerPlayer(Game* game, QChar symbol, const QColor& color)
    : game(game), name("Random Player"), color(color), symbol(symbol)
{
}

QChar Connect4ComputerPlayer::get_symbol()
{
    return symbol;
}

QColor Connect4ComputerPlayer::get_color()
{
    return color;
}

QString Connect4ComputerPlayer::get_name()
{
    return name;
}

void Connect4ComputerPlayer::get_move()
{
    // Generate random stack index;
    srand(time(nullptr));
    int x = rand() % 7;

    // Try to update the board;
    while (!game->update_board(symbol, x))
        x = rand() % 7;

    game->onButtonClick(-1);
}