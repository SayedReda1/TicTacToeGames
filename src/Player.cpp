// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramicGame.h"


Player::Player(QChar symbol)
	: symbol(symbol)
{
	this->name = "Unkown";
}

Player::Player(const QString& name, const QColor& color, QChar symbol)
	: name(name), color(color), symbol(symbol)
{
}

QChar Player::get_symbol()
{
	return symbol;
}

QColor Player::get_color()
{
	return color;
}

QString Player::get_name()
{
	return name;
}

void Player::get_move(GameManager* game)
{
	game->connect_buttons();
}