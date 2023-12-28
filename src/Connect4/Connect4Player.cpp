#include "Connect4Game.h"

Connect4Player::Connect4Player(QChar symbol)
	: game(nullptr), symbol(symbol.toUpper()), name("Unkown")
{
}

Connect4Player::Connect4Player(QChar symbol, const QString& name, const QColor& color)
	: game(nullptr), name(name), color(color), symbol(symbol.toUpper())
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

void Connect4Player::setGame(Game* game)
{
	this->game = game;
}

void Connect4Player::getMove()
{
	game->connectButtons();
}