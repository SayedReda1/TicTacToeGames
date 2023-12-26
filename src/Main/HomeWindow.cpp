#include "HomeWindow.h"
#include <Windows.h>
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
	resetWindow();
}

HomeWindow::~HomeWindow()
{
	delete ui;
}

void HomeWindow::resetWindow()
{
	// Combo boxes
	ui->gameCombo->setCurrentIndex(-1);
	ui->modeCombo->setCurrentIndex(-1);

	// Players
	ui->player1Line->clear();
	ui->player2Line->clear();

	// Disabling fields
	disable(ui->modeCombo, "background-color: rgb(24, 31, 43);" );
	disable(ui->player1Line, "background-color: rgb(24, 31, 43);");
	disable(ui->player2Line, "background-color: rgb(24, 31, 43);");
	disable(ui->goButton, "background-color: rgb(24, 31, 43);");
}

void HomeWindow::enable(QWidget* widget)
{
	widget->setDisabled(false);
	widget->setStyleSheet("");
}

void HomeWindow::disable(QWidget* widget, const QString& style)
{
	widget->setDisabled(true);
	widget->setStyleSheet(style);
}


////////////// SLOTS //////////////////
void HomeWindow::onGoButton()
{
	PlaySound(TEXT("media/click.wav"), NULL, SND_ASYNC);
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

	resetWindow();
}

void HomeWindow::onGameChange()
{
	if (ui->gameCombo->currentIndex() >= 0)
	{
		enable(ui->modeCombo);
	}
}

void HomeWindow::onModeChange()
{
	if (ui->modeCombo->currentIndex() >= 0)
	{
		enable(ui->player1Line);
		enable(ui->goButton);

		// Show the other one
		if (ui->modeCombo->currentText() == "PvP")
		{
			ui->player2Line->clear();
			enable(ui->player2Line);
		}
		else
		{
			ui->player2Line->setText("Computer Player");
			disable(ui->player2Line, "background-color: rgb(24, 31, 43);");
		}
	}
	else
	{
		disable(ui->player1Line, "background-color: rgb(24, 31, 43);");
		disable(ui->player2Line, "background-color: rgb(24, 31, 43);");
		disable(ui->goButton, "background-color: rgb(24, 31, 43);");
	}
}