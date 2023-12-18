#ifndef _PYRAMIC_GAME_
#define _PYRAMIC_GAME_

#include <QtWidgets/QWidget>
#include "ui_XOFrame.h"


class GameManager;
class Player;
//class ComputerPlayer;

// Game Manager Class
class GameManager : public QWidget
{
    Q_OBJECT

public:
    GameManager(Player* players[2], QWidget* parent = nullptr);
    ~GameManager();

    // Program Design
    bool is_winner();
    bool is_draw();

    // Gui Modifiers
    void greet_winner(Player* winner);
    void show_draw();
    void reset_game();
    void end_game();

    bool update_board(QChar symbol, int index);
    void switch_turn();
    bool get_turn();
    bool increment_counter();

    void connect_buttons();

    // signals
    void onButtonClick(QPushButton* btn);

private:
    bool turn;
    int n_moves;
    QVector<QPushButton*> board;
    Player* players[2];
    Ui_Form* ui;
};

class Player
{
public:
    Player(QChar symbol);
    Player(const QString& name, const QColor& color, QChar symbol);

    QChar get_symbol();
    QColor get_color();
    QString get_name();
    // Reconnects the free buttons to suit the next player
    // Different in ComputerPlayer
    virtual void get_move(GameManager* game);

protected:
    QString name;
    QChar symbol;
    QColor color;
};

//class ComputerPlayer : public Player
//{
//public:
//    ComputerPlayer(QPushButton* board, const QColor& color, QChar symbol);
//
//    // use the algorithm to choose a position and use it
//    void get_move();
//};


#endif