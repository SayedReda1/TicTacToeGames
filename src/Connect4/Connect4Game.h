#ifndef _CONNECT4_GAME_H
#define _CONNECT4_GAME_H

#include "Game.h"
#include "ui_Connect4.h"
#include <QStackedWidget.h>


class Connect4Game : public Game
{
    Q_OBJECT

public:
    Connect4Game(Player* player1, Player* player2, QStackedWidget* parent = nullptr);
    ~Connect4Game();

    // ------------ Game Functions -------------

    // To check if there is a winner
    bool isWinner();

    // To state if there is a draw()
    bool isDraw();

    // Shows a winning message passed true
    // Shows a draw message passed false
    // The current player in turn is ALWAYS the winner
    void showStatus(bool);

    // Resets the game and all buttons and labels
    void resetGame();

    // Ends the game by disabling all buttons & disconnecting them
    void endGame();

    // Prepares for the next player move
    void nextPlayerMove();


    // ------------ Gui Modifiers ---------------

    // Updates the board at the given index with a specific value
    bool updateBoard(QChar, const QColor&, int);

    // Returns the current player's turn
    bool getTurn();

    // Returns the board in a 2d arrays of Qt characters
    QVector<QVector<QChar>> getBoard();

    // Increments n_moves variable
    bool incrementMoves();

    // Color 4 cells
    void styleCells(const QVector<QLabel*>&, const QString&);

    // Enable a button
    void enableButton(int index);

    // Disable a button when it's stack is full
    void disableButton(int index);

    // Connects all button to the appropriate slots for the next player
    void connectButtons();

    // Resets all buttons slot connections
    void disconnectButtons();

public slots:
    void onButtonClick(int index);
    void onHomeButtonClick();

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
    Connect4Player(QChar symbol);
    Connect4Player(QChar symbol, const QString& name, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();
    void setGame(Game*);
    // Reconnects the free buttons to suit the next player
    // Different in PyramidAiPlayer
    void getMove();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

class Connect4RandomPlayer : public Player
{
public:

    Connect4RandomPlayer(QChar symbol);
    Connect4RandomPlayer(QChar symbol, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();
    void setGame(Game* game);

    // use the algorithm to choose a position and use it
    void getMove();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

#endif