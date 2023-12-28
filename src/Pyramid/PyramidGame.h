#ifndef _PYRAMIC_GAME_
#define _PYRAMIC_GAME_

#include "Game.h"
#include "ui_PyramidGame.h"
#include <QStackedWidget>


class PyramidGame;
class PyramidPlayer;
class PyramidAiPlayer;

// Game Manager Class
class PyramidGame : public Game
{
    Q_OBJECT

public:
    PyramidGame(Player* player1, Player* player2, QStackedWidget* parent = nullptr);
    ~PyramidGame();

    // ------------ Game Functions -------------

    // To check if there is a winner
    bool isWinner();

    // To state if there is a draw()
    bool isDraw();

    // Shows a winning message passed true
    // Shows a draw message passed false
    void showStatus(bool);

    // Resets the game and all buttons and labels
    void resetGame();

    // Ends the game by disabling all buttons & disconnecting them
    void endGame();

    // Prepares for the next player move
    void nextPlayerMove();


    // ------------ Gui Modifiers ---------------

    // Updates the board at the given index with a specific value
    bool updateBoard(QChar, QColor, int);

    // Returns the current player's turn
    bool getTurn();

    // Returns the board in a 2d arrays of Qt characters
    QVector<QVector<QChar>> getBoard();

    // Increments n_moves variable
    bool incrementMoves();

    // Color cells
    void styleCells(const QVector<QPushButton*>&, const QString&);

    // Connects all button to the appropriate slots for the next player
    void connectButtons();

    // Resets all buttons slot connections
    void disconnectButtons();

public slots:
    void onButtonClick(int index);
    void onHomeButton();

private:
    bool turn;
    int n_moves;
    QVector<QPushButton*> board;
    QStackedWidget* stack;
    Player* players[2];
    Ui_PyramidGame* ui;
};

class PyramidPlayer : public Player
{
public:
    PyramidPlayer(QChar symbol);
    PyramidPlayer(QChar symbol, const QString& name, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();
    void setGame(Game* game);

    // Reconnects the free buttons to suit the next player
    // Different in PyramidAiPlayer
    void getMove();

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

class PyramidRandomPlayer : public Player
{
public:
    PyramidRandomPlayer(QChar symbol);
    PyramidRandomPlayer(QChar symbol, const QColor& color);

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

class PyramidAiPlayer : public Player
{
public:

    PyramidAiPlayer(QChar symbol);
    PyramidAiPlayer(QChar symbol, const QColor& color);

    QChar getSymbol();
    QColor getColor();
    QString getName();
    void setGame(Game* game);

    // use the algorithm to choose a position and use it
    void getMove();

    // Minimax function
    int minimax(QVector<QChar>& board, bool isMaximizing);

    // Check for a winner
    // 10 -> PyramidAiPlayer wins
    // -10 -> Opponent wins
    // 0 -> draw
    // 1 -> non of the above
    int check(QVector<QChar>& board);

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};


#endif