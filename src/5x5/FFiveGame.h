
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
    bool is_winner();

    // Always returns false unless it's 24 moves
    // and both players have same score
    bool is_draw();

    // Shows a winning message when true is passed
    // Shows a draw message when false is passed
    // checks p1 & p2 then shows a message
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

    // Highlights the winners moves at the end of the game
    //void highlight_wins(QChar winner_symbol);

    // Returns the current player's turn
    bool get_turn();

    // Returns the board in a 2d arrays of Qt characters
    QVector<QVector<QChar>> get_board();

    // Increments n_moves variable & returns if possible increment
    bool increment_moves();

    // Connects all button to the appropriate slots for the next player
    void connect_buttons();

    // Resets all buttons slot connections
    void disconnect_buttons();

    // Updates the players counter labels
    void update_score_labels();

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

class FFiveComputerPlayer : public Player
{
public:

    FFiveComputerPlayer(Game* game, QChar symbol);
    FFiveComputerPlayer(Game* game, QChar symbol, const QColor& color);

    QChar get_symbol();
    QColor get_color();
    QString get_name();

    // use the algorithm to choose a position and use it
    void get_move();

    // Minimax function
    //int minimax(QVector<QChar>& board, bool isMaximizing);

    // Check for a winner
    // 10 -> PyramidComputerPlayer wins
    // -10 -> Opponent wins
    // 0 -> draw
    // 1 -> non of the above
    //int check_winner(QVector<QChar>& board);

private:
    Game* game;
    QString name;
    QChar symbol;
    QColor color;
};

#endif