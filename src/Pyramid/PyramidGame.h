#ifndef _PYRAMIC_GAME_
#define _PYRAMIC_GAME_

#include "Game.h"
#include "ui_PyramidGame.h"


class PyramidGame;
class PyramidPlayer;
class PyramidComputerPlayer;

// Game Manager Class
class PyramidGame : public Game
{
    Q_OBJECT

public:
    PyramidGame(const QString& playerName1, QWidget* parent = nullptr);
    PyramidGame(const QString& playerName1, const QString& playerName2, QWidget* parent = nullptr);
    ~PyramidGame();

    // ------------ Game Functions -------------

    // To check if there is a winner
    bool is_winner();

    // To state if there is a draw()
    bool is_draw();

    // Shows a winning message passed true
    // Shows a draw message passed false
    virtual void show_status(bool);

    // Resets the game and all buttons and labels
    void reset_game();

    // Ends the game by disabling all buttons & disconnecting them
    void end_game();

    // Prepares for the next player move
    void next_player_move();


    // ------------ Gui Modifiers ---------------

    // Updates the board at the given index with a specific value
    bool update_board(QChar, int);

    // Returns the current player's turn
    bool get_turn();

    // Returns the board in a 2d arrays of Qt characters
    QVector<QVector<QChar>> get_board();

    // Increments n_moves variable
    bool increment_moves();

    // Connects all button to the appropriate slots for the next player
    void connect_buttons();

    // Resets all buttons slot connections
    void disconnect_buttons();

    // signals
    void onButtonClick(int index);

private:
    bool turn;
    int n_moves;
    QVector<QPushButton*> board;
    Player* players[2];
    Ui_Form* ui;
};

class PyramidPlayer : public Player
{
public:
    PyramidPlayer(Game* game, QChar symbol);
    PyramidPlayer(Game* game, QChar symbol, const QString& name, const QColor& color);

    QChar get_symbol();
    QColor get_color();
    QString get_name();
    // Reconnects the free buttons to suit the next player
    // Different in PyramidComputerPlayer
    void get_move();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

class PyramidComputerPlayer : public Player
{
public:

    PyramidComputerPlayer(Game* game, QChar symbol);
    PyramidComputerPlayer(Game* game, QChar symbol, const QColor& color);

    QChar get_symbol();
    QColor get_color();
    QString get_name();

    // use the algorithm to choose a position and use it
    void get_move();

    // Minimax function
    int minimax(QVector<QChar>& board, bool isMaximizing);

    // Check for a winner
    // 10 -> PyramidComputerPlayer wins
    // -10 -> Opponent wins
    // 0 -> draw
    // 1 -> non of the above
    int check_winner(QVector<QChar>& board);

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};


#endif