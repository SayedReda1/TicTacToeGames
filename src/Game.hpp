#include <QWidget>

// -----------------------------
// ------ Game Blueprint -------
// -----------------------------

class Game : public QWidget
{
public:
	Game(QWidget* parent = nullptr)
		: QWidget(parent) {};

	// ------------ Game Functions -------------

	// To check if there is a winner
	virtual bool is_winner() = 0;

	// To state if there is a draw()
	virtual bool is_draw() = 0;

	// Shows a winning message passed true
	// Shows a draw message passed false
	virtual void show_status(bool) = 0;

	// Resets the game and all buttons and labels
	virtual void reset_game() = 0;

	// Ends the game by disabling all buttons & disconnecting them
	virtual void end_game() = 0;

	// Prepares for the next player move
	virtual void next_player_move() = 0;


	// ------------ Gui Modifiers ---------------

	// Updates the board at the given index with a specific value
	virtual bool update_board(QChar, int) = 0;

	// Returns the current player's turn
	virtual bool get_turn() = 0;

	// Returns the board in a 2d arrays of Qt characters
	virtual QVector<QVector<QChar>> get_board() = 0;

	// Increments n_moves variable
	virtual bool increment_moves() = 0;

	// Connects all button to the appropriate slots for the next player
	virtual void connect_buttons() = 0;

	// Resets all buttons slot connections
	virtual void disconnect_buttons() = 0;

	// Board button slot
	// Button index is passed to it
	virtual void onButtonClick(int) = 0;
};


class Player
{
public:
	
	// To get the player's name
	virtual QString get_name() = 0;

	// To get the player's chosen color
	virtual QColor get_color() = 0;

	// Get the symbol
	virtual QChar get_symbol() = 0;

	// Take the next move
	virtual void get_move() = 0;
};