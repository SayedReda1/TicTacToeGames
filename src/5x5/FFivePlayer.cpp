#include "FFiveGame.h"

FFivePlayer::FFivePlayer(QChar symbol)
	: game(game), symbol(symbol.toUpper()), name("Unkown Player")
{
}

FFivePlayer::FFivePlayer(QChar symbol, const QString& name, const QColor& color)
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

void FFivePlayer::setGame(Game* game)
{
	this->game = game;
}

void FFivePlayer::getMove()
{
	game->connectButtons();
}