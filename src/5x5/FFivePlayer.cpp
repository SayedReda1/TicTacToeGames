#include "FFiveGame.h"

FFivePlayer::FFivePlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown Player")
{
}

FFivePlayer::FFivePlayer(Game* game, QChar symbol, const QString& name, const QColor& color)
	: game(game), symbol(symbol), name(name), color(color)
{
}

QChar FFivePlayer::getSymbol()
{
	return symbol;
}

QColor FFivePlayer::getColor()
{
	return color;
}

QString FFivePlayer::getName()
{
	return name;
}

void FFivePlayer::getMove()
{
	game->connectButtons();
}