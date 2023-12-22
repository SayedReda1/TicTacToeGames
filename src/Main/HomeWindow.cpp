#include "HomeWindow.h"
#include "Pyramid/PyramidGame.h"
#include "5x5/FFiveGame.h"
#include "Connect4/Connect4Game.h"


HomeWindow::HomeWindow(QStackedWidget* parent)
	: QWidget(parent)
	, ui(new Ui_Home)
	, stack(parent)
{
	ui->setupUi(this);
	reset_window();

	connect(ui->goButton, &QPushButton::clicked, this, &HomeWindow::onGoButton);
}

HomeWindow::~HomeWindow()
{
	delete ui;
}

void HomeWindow::reset_window()
{
	// Combo boxes
	ui->gameCombo->setCurrentIndex(-1);
	ui->modeCombo->setCurrentIndex(-1);

	// Players
	ui->player1Line->clear();
	ui->player2Line->clear();
}

void HomeWindow::onGoButton()
{
	QString game = ui->gameCombo->currentText();
	QString mode = ui->modeCombo->currentText();

	if (stack->count() > 1)
	{
		auto widget = stack->widget(1);
		stack->removeWidget(widget);
		delete widget;
	}

	Game* chosen_game = nullptr;
	if (game == "Pyramid XO")
	{
		if (mode == "PvP")
		{
			chosen_game = new PyramidGame(ui->player1Line->text(), ui->player2Line->text(), stack);
		}
		else if (mode == "Vs Computer")
		{
			chosen_game = new PyramidGame(ui->player1Line->text(), stack);
		}
	}
	else if (game == "5x5 XO")
	{
		if (mode == "PvP")
		{
			chosen_game = new FFiveGame(ui->player1Line->text(), ui->player2Line->text(), stack);
		}
		else if (mode == "Vs Computer")
		{
			chosen_game = new FFiveGame(ui->player1Line->text(), ui->player2Line->text(), stack);
		}
	}
	else if (game == "Connect4")
	{
		if (mode == "PvP")
		{
			chosen_game = new Connect4Game(ui->player1Line->text(), ui->player2Line->text(), stack);
		}
		else if (mode == "Vs Computer")
		{
			chosen_game = new Connect4Game(ui->player1Line->text(), stack);
		}
	}
	stack->insertWidget(1, chosen_game);
	stack->setCurrentIndex(1);

	reset_window();
}