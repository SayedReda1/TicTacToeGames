// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramicGame.h"
#include <QMessageBox>

GameManager::GameManager(Player* players[2], QWidget* parent)
    : QWidget(parent)
    , ui(new Ui_Form())
    , n_moves(0)
    , turn(0)
{
    ui->setupUi(this);

    // Take the two players
    this->players[0] = players[0];
    this->players[1] = players[1];

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

    connect(ui->homeButton, &QPushButton::clicked, this, &GameManager::reset_game);

    // Get the first move
    players[turn]->get_move(this);
}

GameManager::~GameManager()
{
    delete ui;
}

bool GameManager::is_winner()
{
    bool found_winner = false;

    // rows
    found_winner |= (board[1]->text() == board[2]->text() &&
        board[2]->text() == board[3]->text() &&
        !board[1]->text().isEmpty());

    for (size_t i : {4, 5, 6})
        found_winner |= board[i]->text() == board[i + 1]->text() && 
        board[i + 1]->text() == board[i + 2]->text() && 
        !board[i]->text().isEmpty();

    // col
    found_winner |= (board[0]->text() == board[2]->text() && 
        board[2]->text() == board[6]->text() &&
        !board[0]->text().isEmpty());

    // diags
    found_winner |= (board[0]->text() == board[1]->text() && 
        board[1]->text() == board[4]->text() &&
        !board[0]->text().isEmpty());

    found_winner |= (board[0]->text() == board[3]->text() &&
        board[3]->text() == board[8]->text() &&
        !board[0]->text().isEmpty());

    return found_winner;
}

bool GameManager::is_draw()
{
    return !is_winner() && n_moves == 9;
}

void GameManager::greet_winner(Player* winner)
{
    QMessageBox::question(this, "WINNER", winner->get_name() + " WINS", QMessageBox::Ok);
}

bool GameManager::update_board(QChar symbol, int index)
{
    if (board[index]->text().isEmpty())
    {
        board[index]->setText(symbol.toUpper());
        return true;
    }
    return false;
}

void GameManager::switch_turn()
{
    turn = !turn;
}

bool GameManager::get_turn()
{
    return turn;
}

bool GameManager::increment_counter()
{
    if (n_moves < 9)
    {
        n_moves++;
        return true;
    }
    return false;
}

void GameManager::show_draw()
{
    QMessageBox::question(this, "Draw", "It's a draw", QMessageBox::Ok);
}

void GameManager::reset_game()
{
    if (QMessageBox::warning(this, "Reset", "Are you sure to reset the game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        // Buttons
        for (auto& button : board)
        {
            button->setDisabled(false);
            button->setText("");
        }

        // Moves
        n_moves = 0;

        // Turn
        turn = false;
    }
}

void GameManager::end_game()
{
    // Disable all buttons
    for (int i = 0; i < 9; ++i)
    {
        board[i]->setDisabled(true);
    }
}

void GameManager::connect_buttons()
{
    connect(board[0], &QPushButton::clicked, this, [&]() { onButtonClick(board[0]); });
    connect(board[1], &QPushButton::clicked, this, [&]() { onButtonClick(board[1]); });
    connect(board[2], &QPushButton::clicked, this, [&]() { onButtonClick(board[2]); });
    connect(board[3], &QPushButton::clicked, this, [&]() { onButtonClick(board[3]); });
    connect(board[4], &QPushButton::clicked, this, [&]() { onButtonClick(board[4]); });
    connect(board[5], &QPushButton::clicked, this, [&]() { onButtonClick(board[5]); });
    connect(board[6], &QPushButton::clicked, this, [&]() { onButtonClick(board[6]); });
    connect(board[7], &QPushButton::clicked, this, [&]() { onButtonClick(board[7]); });
    connect(board[8], &QPushButton::clicked, this, [&]() { onButtonClick(board[8]); });
}

void GameManager::onButtonClick(QPushButton* btn)
{
    btn->setText(players[turn]->get_symbol());
    btn->setDisabled(true);
    increment_counter();

    if (is_winner())
    {
        greet_winner(players[turn]);
        end_game();
    }
    else if (is_draw())
    {
        show_draw();
        end_game();
    }

    // Disconnect all buttons
    disconnect(btn, &QPushButton::clicked, 0, 0);

    switch_turn();

    players[turn]->get_move(this);
}