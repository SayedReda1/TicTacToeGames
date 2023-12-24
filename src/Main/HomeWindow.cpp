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

	connect(ui->gameCombo, &QComboBox::activated, this, &HomeWindow::onGameChange);
	connect(ui->modeCombo, &QComboBox::activated, this, &HomeWindow::onModeChange);
	connect(ui->goButton, &QPushButton::clicked, this, &HomeWindow::onGoButton);

	// reset window
	reset_window();
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
	ui->modeCombo->setDisabled(true);

	// Players
	ui->player1Line->clear();
	ui->player2Line->clear();

	// Hide Player 2
	ui->vsIcon->hide();
	ui->player1Line->hide();
	ui->player2Line->hide();

	// Go Button
	ui->goButton->setDisabled(true);
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
			chosen_game = new FFiveGame(ui->player1Line->text(), stack);
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

void HomeWindow::onGameChange()
{
	if (ui->gameCombo->currentIndex() >= 0)
	{
		ui->modeCombo->setDisabled(false);
	}
}

void HomeWindow::onModeChange()
{
	if (ui->modeCombo->currentIndex() >= 0)
	{
		ui->player1Line->show();
		ui->goButton->setDisabled(false);

		// Show the other one
		if (ui->modeCombo->currentText() == "PvP")
		{
			ui->player2Line->show();
			ui->vsIcon->show();
		}
		else
		{
			ui->player2Line->hide();
			ui->vsIcon->hide();
		}
	}
}