#ifndef _CONNECT4_GAME_H
#define _CONNECT4_GAME_H

#include "Game.h"
#include "ui_Connect4.h"
#include <QStackedWidget.h>


class Connect4Game : public Game
{
    Q_OBJECT

public:
    Connect4Game(const QString& playerName1, QStackedWidget* parent = nullptr);
    Connect4Game(const QString& playerName1, const QString& playerName2, QStackedWidget* parent = nullptr);
    ~Connect4Game();

    // ------------ Game Functions -------------

    // To check if there is a winner
    bool is_winner();

    // To state if there is a draw()
    bool is_draw();

    // Shows a winning message passed true
    // Shows a draw message passed false
    // The current player in turn is ALWAYS the winner
    void show_status(bool);

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

    // Color 4 cells
    void color_cells(const QVector<QLabel*>&, const QString&);

    // Enable a button
    void enable_button(int index);

    // Disable a button when it's stack is full
    void disable_button(int index);

    // Connects all button to the appropriate slots for the next player
    void connect_buttons();

    // Resets all buttons slot connections
    void disconnect_buttons();

public slots:
    void onButtonClick(int index);
    void onHomeButton();

private:
    bool turn;
    int n_moves;
    QVector<QVector<QLabel*>> stacks;
    QVector<QPushButton*> adders;
    Player* players[2];
    QStackedWidget* stack;
    Ui_Connect4Game* ui;
};

class Connect4Player : public Player
{
public:
    Connect4Player(Game* game, QChar symbol);
    Connect4Player(Game* game, QChar symbol, const QString& name, const QColor& color);

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

class Connect4ComputerPlayer : public Player
{
public:

    Connect4ComputerPlayer(Game* game, QChar symbol);
    Connect4ComputerPlayer(Game* game, QChar symbol, const QColor& color);

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