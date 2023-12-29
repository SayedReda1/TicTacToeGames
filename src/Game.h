#include <QWidget>

// -----------------------------
// ------ Game Blueprint -------
// -----------------------------
#ifndef _GAME_H
#define _GAME_H
class Game : public QWidget
{
public:
	Game(QWidget* parent = nullptr)
		: QWidget(parent) {};

	// ------------ Game Functions -------------

	// To check if there is a winner
	virtual bool isWinner() = 0;

	// To state if there is a draw()
	virtual bool isDraw() = 0;

	// Shows a winning message passed true
	// Shows a draw message passed false
	virtual void showStatus(bool) = 0;

	// Resets the game and all buttons and labels
	virtual void resetGame() = 0;

	// Ends the game by disabling all buttons & disconnecting them
	virtual void endGame() = 0;

	// Prepares for the next player move
	virtual void nextPlayerMove() = 0;


	// ------------ Gui Modifiers ---------------

	// Updates the board at the given index with a specific value
	virtual bool updateBoard(QChar,const QColor&, int) = 0;

	// Returns the current player's turn
	virtual bool getTurn() = 0;

	// Returns the board in a 2d arrays of Qt characters
	virtual QVector<QVector<QChar>> getBoard() = 0;

	// Increments n_moves variable
	virtual bool incrementMoves() = 0;

	// Connects all button to the appropriate slots for the next player
	virtual void connectButtons() = 0;

	// Resets all buttons slot connections
	virtual void disconnectButtons() = 0;

	// Board button slot
	// Button index is passed to it
	virtual void onButtonClick(int) = 0;
};


class Player
{
public:
	
	// To get the player's name
	virtual QString getName() = 0;

	// To get the player's chosen color
	virtual QColor getColor() = 0;

	// Get the symbol
	virtual QChar getSymbol() = 0;

	// Set the board
	virtual void setGame(Game*) = 0;

	// Take the next move
	virtual void getMove() = 0;
};

#endif