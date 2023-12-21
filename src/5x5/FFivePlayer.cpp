#include "FFiveGame.h"

FFivePlayer::FFivePlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown Player")
{
}

FFivePlayer::FFivePlayer(Game* game, QChar symbol, const QString& name, const QColor& color)
	: game(game), symbol(symbol), name(name), color(color)
{
}

QChar FFivePlayer::get_symbol()
{
	return symbol;
}

QColor FFivePlayer::get_color()
{
	return color;
}

QString FFivePlayer::get_name()
{
	return name;
}

void FFivePlayer::get_move()
{
	game->connect_buttons();
}