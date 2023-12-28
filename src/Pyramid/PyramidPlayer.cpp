// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramidGame.h"


PyramidPlayer::PyramidPlayer(QChar symbol)
	: game(nullptr), symbol(symbol.toUpper()), name("Unkown")
{
}

PyramidPlayer::PyramidPlayer(QChar symbol, const QString& name, const QColor& color)
	: game(nullptr), name(name), color(color), symbol(symbol.toUpper())
{
}

QChar PyramidPlayer::getSymbol()
{
	return symbol;
}

QColor PyramidPlayer::getColor()
{
	return color;
}

QString PyramidPlayer::getName()
{
	return name;
}

void PyramidPlayer::setGame(Game* game)
{
	this->game = game;
}

void PyramidPlayer::getMove()
{
	game->connectButtons();
}