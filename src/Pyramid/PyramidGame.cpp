// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramidGame.h"
#include <QMessageBox>

PyramidGame::PyramidGame(const QString& playerName1, QWidget* parent)
    : Game(parent), ui(new Ui_Form()), n_moves(0)
    , turn(0)
{
    ui->setupUi(this);

    // Take the two players
    this->players[0] = new PyramidPlayer(this, 'X', playerName1, QColor(0, 0, 170));
    this->players[1] = new PyramidComputerPlayer(this, 'O');

    // Show Names
    ui->player1Label->setText(players[0]->get_name());
    ui->player2Label->setText(players[1]->get_name());

    // Fill the board
    board.push_back(ui->pushButton);
    board.push_back(ui->pushButton2);
    board.push_back(ui->pushButton3);
    board.push_back(ui->pushButton4);
    board.push_back(ui->pushButton5);
    board.push_back(ui->pushButton6);
    board.push_back(ui->pushButton7);
    board.push_back(ui->pushButton8);
    board.push_back(ui->pushButton9);

    connect(ui->restartButton, &QPushButton::clicked, this, &PyramidGame::reset_game);

    // Get the first move
    players[turn]->get_move();
}

PyramidGame::PyramidGame(const QString& playerName1, const QString& playerName2, QWidget* parent)
    : PyramidGame(playerName1, parent)
{
    delete this->players[1];
    this->players[1] = new PyramidPlayer(this, 'O', playerName2, QColor(170, 0, 0));
}

PyramidGame::~PyramidGame()
{
    delete ui;
}

bool PyramidGame::is_winner()
{ 
    bool found_winner = false;

    int checks[][3] {
        {1, 2, 3}, {4, 5, 6}, {5, 6, 7}, {6, 7, 8},     // Rows
        {0, 2, 6},                                      // Cols
        {0, 1, 4}, {0, 3, 8}                            // Diagonals
    };
    for (auto [x, y, z] : checks)
    {
        found_winner |= board[x]->text() == board[y]->text() 
            && board[y]->text() == board[z]->text()
            && !board[x]->text().isEmpty();
    }

    return found_winner;
}

bool PyramidGame::is_draw()
{
    return n_moves == 9 && !is_winner();
}

bool PyramidGame::update_board(QChar symbol, int index)
{
    if (board[index]->text().isEmpty())
    {
        board[index]->setText(symbol.toUpper());
        board[index]->setDisabled(true);
        n_moves++;
        return true;
    }
    return false;
}

bool PyramidGame::get_turn()
{
    return turn;
}

QVector<QVector<QChar>> PyramidGame::get_board()
{
    QVector<QVector<QChar>> arr;
    arr.push_back({});

    for (int i = 0; i < 9; ++i)
    {
        if (board[i]->text() == "X")
            arr[0].push_back('X');
        else if (board[i]->text() == "O")
            arr[0].push_back('O');
        else
            arr[0].push_back(' ');
    }

    return arr;
}

bool PyramidGame::increment_moves()
{
    if (n_moves < 9)
    {
        n_moves++;
        return true;
    }
    return false;
}

void PyramidGame::show_status(bool win)
{
    if (win)
        QMessageBox::question(this, "Win", "Player" + players[turn]->get_name() + " WINS", QMessageBox::Ok);
    else
        QMessageBox::question(this, "Draw", "It's a draw", QMessageBox::Ok);
}

void PyramidGame::reset_game()
{
    if (QMessageBox::warning(this, "Reset", "Are you sure to reset the game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        // Buttons
        for (auto& button : board)
        {
            button->setDisabled(false);
            button->setText("");
        }

        // Disconnecting all buttons
        disconnect_buttons();

        // Moves
        n_moves = 0;

        // Turn
        turn = false;

        // PyramidPlayer 1 move
        players[turn]->get_move();
    }
}

void PyramidGame::end_game()
{
    disconnect_buttons();

    // Disable all buttons
    for (int i = 0; i < 9; ++i)
    {
        board[i]->setDisabled(true);
    }
}

void PyramidGame::next_player_move()
{
    turn = !turn;
    players[turn]->get_move();
}

void PyramidGame::connect_buttons()
{
    connect(board[0], &QPushButton::clicked, this, [&]() { onButtonClick(0); });
    connect(board[1], &QPushButton::clicked, this, [&]() { onButtonClick(1); });
    connect(board[2], &QPushButton::clicked, this, [&]() { onButtonClick(2); });
    connect(board[3], &QPushButton::clicked, this, [&]() { onButtonClick(3); });
    connect(board[4], &QPushButton::clicked, this, [&]() { onButtonClick(4); });
    connect(board[5], &QPushButton::clicked, this, [&]() { onButtonClick(5); });
    connect(board[6], &QPushButton::clicked, this, [&]() { onButtonClick(6); });
    connect(board[7], &QPushButton::clicked, this, [&]() { onButtonClick(7); });
    connect(board[8], &QPushButton::clicked, this, [&]() { onButtonClick(8); });
}

void PyramidGame::disconnect_buttons()
{
    disconnect(board[0], &QPushButton::clicked, 0, 0);
    disconnect(board[1], &QPushButton::clicked, 0, 0);
    disconnect(board[2], &QPushButton::clicked, 0, 0);
    disconnect(board[3], &QPushButton::clicked, 0, 0);
    disconnect(board[4], &QPushButton::clicked, 0, 0);
    disconnect(board[5], &QPushButton::clicked, 0, 0);
    disconnect(board[6], &QPushButton::clicked, 0, 0);
    disconnect(board[7], &QPushButton::clicked, 0, 0);
    disconnect(board[8], &QPushButton::clicked, 0, 0);

}

void PyramidGame::onButtonClick(int index)
{
    update_board(players[turn]->get_symbol(), index);

    if (is_winner())
    {
        show_status(true);
        end_game();
        return;
    }
    else if (is_draw())
    {
        show_status(false);
        end_game();
        return;
    }

    // Disconnect all buttons
    disconnect_buttons();

    next_player_move();
}