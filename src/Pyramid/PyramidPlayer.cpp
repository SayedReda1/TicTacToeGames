// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramidGame.h"


PyramidPlayer::PyramidPlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown")
{
}

PyramidPlayer::PyramidPlayer(Game* game, QChar symbol, const QString& name, const QColor& color)
	: game(game), name(name), color(color), symbol(symbol.toUpper())
{
}

QChar PyramidPlayer::get_symbol()
{
	return symbol;
}

QColor PyramidPlayer::get_color()
{
	return color;
}

QString PyramidPlayer::get_name()
{
	return name;
}

void PyramidPlayer::get_move()
{
	game->connect_buttons();
}