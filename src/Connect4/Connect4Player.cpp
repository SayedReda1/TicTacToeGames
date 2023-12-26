#include "Connect4Game.h"

Connect4Player::Connect4Player(Game* game, QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown")
{
}

Connect4Player::Connect4Player(Game* game, QChar symbol, const QString& name, const QColor& color)
	: game(game), name(name), color(color), symbol(symbol.toUpper())
{
}

QChar Connect4Player::getSymbol()
{
	return symbol;
}

QColor Connect4Player::getColor()
{
	return color;
}

QString Connect4Player::getName()
{
	return name;
}

void Connect4Player::getMove()
{
	game->connectButtons();
}