#include "HomeFrame.h"
#include <Windows.h>
#include "PyramidGame.h"
#include "FFiveGame.h"
#include "Connect4Game.h"


HomeFrame::HomeFrame(QStackedWidget* parent)
	: QWidget(parent)
	, ui(new Ui_Home)
	, stack(parent)
{
	ui->setupUi(this);

	connect(ui->gameCombo, &QComboBox::activated, this, &HomeFrame::onGameChange);
	connect(ui->modeCombo, &QComboBox::activated, this, &HomeFrame::onModeChange);
	connect(ui->goButton, &QPushButton::clicked, this, &HomeFrame::onGoButton);

	// reset window
	resetWindow();
}

HomeFrame::~HomeFrame()
{
	delete ui;
}

void HomeFrame::resetWindow()
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

void HomeFrame::enable(QWidget* widget)
{
	widget->setDisabled(false);
	widget->setStyleSheet("");
}

void HomeFrame::disable(QWidget* widget, const QString& style)
{
	widget->setDisabled(true);
	widget->setStyleSheet(style);
}


////////////// SLOTS //////////////////
void HomeFrame::onGoButton()
{
	PlaySound(TEXT("media/click.wav"), NULL, SND_ASYNC);
	int game = ui->gameCombo->currentIndex();
	int mode = ui->modeCombo->currentIndex();


	Game* chosenGame = nullptr;

	switch (game)
	{
	case 0:		// Pyramid
	{
		if (mode == 0)		// vs Player
			chosenGame = new PyramidGame(new PyramidPlayer('X', ui->player1Line->text(), "#e94141")
				, new PyramidPlayer('O', ui->player2Line->text(), "#0086f4"), stack);

		else if (mode == 1)	// vs Random Player
			chosenGame = new PyramidGame(new PyramidPlayer('X', ui->player1Line->text(), "#e94141")
				, new PyramidRandomPlayer('O', "#0086f4"), stack);

		else if (mode == 2)	// vs Ai Player
			chosenGame = new PyramidGame(new PyramidPlayer('X', ui->player1Line->text(), "#e94141")
				, new PyramidAiPlayer('O', "#0086f4"), stack);

		break;
	}

	case 1:		// 5x5
	{
		if (mode == 0)		// vs Player
			chosenGame = new FFiveGame(new FFivePlayer('X', ui->player1Line->text(), "#e94141")
				, new PyramidPlayer('O', ui->player2Line->text(), "#0086f4"), stack);

		else if (mode == 1)	// vs Random Player
			chosenGame = new FFiveGame(new FFivePlayer('X', ui->player1Line->text(), "#e94141")
				, new FFiveRandomPlayer('O', "#0086f4"), stack);
		break;
	}

	case 2:		// Connect4
	{
		if (mode == 0)		// vs Player
			chosenGame = new Connect4Game(new Connect4Player('X', ui->player1Line->text(), "#e94141")
				, new Connect4Player('O', ui->player2Line->text(), "#0086f4"), stack);

		else if (mode == 1)	// vs Random Player
			chosenGame = new Connect4Game(new Connect4Player('X', ui->player1Line->text(), "#e94141")
				, new Connect4RandomPlayer('O', "#0086f4"), stack);
		break;
	}
	}


	stack->insertWidget(1, chosenGame);
	stack->setCurrentIndex(1);

	resetWindow();
}

void HomeFrame::onGameChange()
{
	if (ui->gameCombo->currentIndex() >= 0)
	{
		if (ui->gameCombo->currentIndex() == 0)	// if pyramid game is chosen
		{
			if (ui->modeCombo->count() < 3)
				ui->modeCombo->insertItem(2, "vs Ai Player");
		}
		else if (ui->modeCombo->count() > 2)	// if other games, remove Ai option
			ui->modeCombo->removeItem(2);

		enable(ui->modeCombo);
	}
}

void HomeFrame::onModeChange()
{
	if (ui->modeCombo->currentIndex() >= 0)
	{
		enable(ui->player1Line);
		enable(ui->goButton);

		// Show the other one
		if (ui->modeCombo->currentText() == "vs Player")
		{
			ui->player2Line->clear();
			enable(ui->player2Line);
		}
		else if (ui->modeCombo->currentText() == "vs Random")
		{
			ui->player2Line->setText("Random Player");
			disable(ui->player2Line, "background-color: rgb(24, 31, 43);");
		}
		else
		{
			ui->player2Line->setText("Ai Player");
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
