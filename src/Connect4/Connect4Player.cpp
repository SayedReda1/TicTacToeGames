#include "Connect4Game.h"

Connect4Player::Connect4Player(Game* game, QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown")
{
}

Connect4Player::Connect4Player(Game* game, QChar symbol, const QString& name, const QColor& color)
	: game(game), name(name), color(color), symbol(symbol.toUpper())
{
}

QChar Connect4Player::get_symbol()
{
	return symbol;
}

QColor Connect4Player::get_color()
{
	return color;
}

QString Connect4Player::get_name()
{
	return name;
}

void Connect4Player::get_move()
{
	game->connect_buttons();
}