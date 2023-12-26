
#ifndef _FFIVE_GAME
#define _FFIVE_GAME

#include "Game.h"
#include <QStackedWidget>
#include "ui_5x5Game.h"


class FFiveGame : public Game
{
    Q_OBJECT

public:
    FFiveGame(const QString& playerName1, QStackedWidget* parent = nullptr);
    FFiveGame(const QString& playerName1, const QString& playerName2, QStackedWidget* parent = nullptr);
    ~FFiveGame();

    // Always returns false unless it's 24 moves
    // and one player has more score
    bool isWinner();

    // Always returns false unless it's 24 moves
    // and both players have same score
    bool isDraw();

    // Shows a winning message when true is passed
    // Shows a draw message when false is passed
    // checks p1 & p2 then shows a message
    void showStatus(bool);

    // Resets the game and all buttons and labels
    void resetGame();

    // Ends the game by disabling all buttons & disconnecting them
    void endGame();

    // Prepares for the next player move
    void nextPlayerMove();


    // ------------ Gui Modifiers ---------------

    // Updates the board at the given index with a specific value
    bool updateBoard(QChar, int);

    // Highlights the winners moves at the end of the game
    //void highlight_wins(QChar winner_symbol);

    // Returns the current player's turn
    bool getTurn();

    // Returns the board in a 2d arrays of Qt characters
    QVector<QVector<QChar>> getBoard();

    // Increments n_moves variable & returns if possible increment
    bool incrementMoves();

    // Connects all button to the appropriate slots for the next player
    void connectButtons();

    // Resets all buttons slot connections
    void disconnectButtons();

    // Updates the players counter labels
    void updateScoreLabels();

public slots:
    void onButtonClick(int index);
    void onHomeButton();


private:
    bool turn;
    int n_moves, p1, p2;
    QStackedWidget* stack;
    QVector<QPushButton*> board;
    Player* players[2];
    Ui_FFiveGame* ui;
};


class FFivePlayer : public Player
{
public:
    FFivePlayer(Game* game, QChar symbol);
    FFivePlayer(Game* game, QChar symbol, const QString& name, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();
    // Reconnects the free buttons to suit the next player
    // Different in PyramidComputerPlayer
    void getMove();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

class FFiveComputerPlayer : public Player
{
public:

    FFiveComputerPlayer(Game* game, QChar symbol);
    FFiveComputerPlayer(Game* game, QChar symbol, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();

    // use the algorithm to choose a position and use it
    void getMove();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

#endif