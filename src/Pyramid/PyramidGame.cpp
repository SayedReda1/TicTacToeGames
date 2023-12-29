// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "PyramidGame.h"
#include "ResultFrame/ResultFrame.h"
#include <QTimer>
#include <QMessageBox>
#include <Windows.h>


PyramidGame::PyramidGame(Player* player1, Player* player2, QStackedWidget* parent)
    : Game(parent), ui(new Ui_PyramidGame), n_moves(0)
    , turn(0), stack(parent)
{
    ui->setupUi(this);

    // Take the two players
    this->players[0] = player1;
    this->players[1] = player2;

    // Pass them the game
    this->players[0]->setGame(this);
    this->players[1]->setGame(this);

    // Show Names
    ui->player1Label->setText(players[0]->getName());
    ui->player2Label->setText(players[1]->getName());

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

    connect(ui->restartButton, &QPushButton::clicked, this, &PyramidGame::resetGame);
    connect(ui->homeButton, &QPushButton::clicked, this, &PyramidGame::onHomeButtonClick);

    // Get the first move
    players[turn]->getMove();
}

PyramidGame::~PyramidGame()
{
    delete players[0];
    delete players[1];

    delete ui;
}

bool PyramidGame::isWinner()
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

        if (found_winner)
        {
            styleCells({ board[x], board[y], board[z] }, "background-color: #65B741;");
            return found_winner;
        }
    }

    return found_winner;
}

bool PyramidGame::isDraw()
{
    return n_moves == 9 && !isWinner();
}

bool PyramidGame::updateBoard(QChar symbol, const QColor& color, int index)
{
    if (board[index]->text().isEmpty())
    {
        board[index]->setText(symbol.toUpper());
        board[index]->setStyleSheet("color: " + color.name() + ";");
        board[index]->setDisabled(true);
        n_moves++;
        return true;
    }
    return false;
}

bool PyramidGame::getTurn()
{
    return turn;
}

QVector<QVector<QChar>> PyramidGame::getBoard()
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

bool PyramidGame::incrementMoves()
{
    if (n_moves < 9)
    {
        n_moves++;
        return true;
    }
    return false;
}

void PyramidGame::styleCells(const QVector<QPushButton*>& buttons, const QString& qss)
{
    for (auto& button : buttons)
        button->setStyleSheet(qss);
}

void PyramidGame::showStatus(bool win)
{
    if (win)
    {
        stack->insertWidget(2, new ResultFrame("Player: " + players[turn]->getName() + " WINS", 1, stack));
    }
    else
    {
        stack->insertWidget(2, new ResultFrame("TIE!", 0, stack));
    }
    stack->setCurrentIndex(2);
}

void PyramidGame::resetGame()
{
    if (QMessageBox::warning(this, "Reset", "Are you sure to reset the game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        // Buttons
        for (auto& button : board)
        {
            button->setDisabled(false);
            button->setStyleSheet("");
            button->setText("");
        }

        // Disconnecting all buttons
        disconnectButtons();

        // Moves
        n_moves = 0;

        // Turn
        turn = false;

        // PyramidPlayer 1 move
        players[turn]->getMove();
    }
}

void PyramidGame::endGame()
{
    disconnectButtons();

    // Disable all buttons
    for (int i = 0; i < 9; ++i)
    {
        board[i]->setDisabled(true);
    }
}

void PyramidGame::nextPlayerMove()
{
    turn = !turn;
    players[turn]->getMove();
}

void PyramidGame::connectButtons()
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

void PyramidGame::disconnectButtons()
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

void PyramidGame::onHomeButtonClick()
{
    if (QMessageBox::warning(this, "Go To Home", "This will erase your progress\nAre you sure to exit?", 
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        stack->setCurrentIndex(0);
    }
}

void PyramidGame::onButtonClick(int index)
{
    if (index >= 0)
    {
        PlaySound(TEXT("media/click.wav"), NULL, SND_ASYNC);
        updateBoard(players[turn]->getSymbol(), players[turn]->getColor(), index);
    }

    if (isWinner())
    {
        showStatus(true);
        endGame();
        return;
    }
    else if (isDraw())
    {
        showStatus(false);
        endGame();
        return;
    }

    // Disconnect all buttons
    disconnectButtons();

    nextPlayerMove();
}