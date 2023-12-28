#include "5x5/FFiveGame.h"
#include "ResultFrame/ResultFrame.h"
#include <QMessageBox>
#include <Windows.h>

FFiveGame::FFiveGame(Player* player1, Player* player2, QStackedWidget* parent)
    : Game(parent), ui(new Ui_FFiveGame()), n_moves(0)
    , turn(0), p1(0), p2(0), stack(parent)
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
    for (int i = 1; i <= 25; ++i)
        board.push_back(this->findChild<QPushButton*>("pushButton" + QString::number(i)));

    // Connecting restart & home buttons
    connect(ui->restartButton, &QPushButton::clicked, this, &FFiveGame::resetGame);
    connect(ui->homeButton, &QPushButton::clicked, this, &FFiveGame::onHomeButton);

    // Get the first move
    players[turn]->getMove();
}

FFiveGame::~FFiveGame()
{
    delete players[0];
    delete players[1];
    delete ui;
}

bool FFiveGame::isWinner()
{
    int x_score{0}, o_score{0};
    
    // Rows
    for (int i = 0; i <= 20; i += 5)
    {
        for (size_t j : {i, i+1, i+2})
        {
            x_score += board[j]->text() == board[j + 1]->text() && board[j + 1]->text() == board[j + 2]->text()
                && board[j]->text() == "X";
            o_score += board[j]->text() == board[j + 1]->text() && board[j + 1]->text() == board[j + 2]->text()
                && board[j]->text() == "O";
        }
    }

    // Cols
    for (int i = 0; i < 5; ++i)
    {
        for (size_t j : {i, i + 5, i + 10})
        {
            x_score += board[j]->text() == board[j + 5]->text() && board[j + 5]->text() == board[j + 10]->text()
                && board[j]->text() == "X";
            o_score += board[j]->text() == board[j + 5]->text() && board[j + 5]->text() == board[j + 10]->text()
                && board[j]->text() == "O";
        }
    }

    // Left Diagonals
    for (int i = 0; i <= 10; i += 5)
    {
        for (int j = i; j < i + 3; ++j)
        {
            x_score += board[j]->text() == board[j + 6]->text() && board[j + 6]->text() == board[j + 12]->text()
                && board[j]->text() == "X";
            o_score += board[j]->text() == board[j + 6]->text() && board[j + 6]->text() == board[j + 12]->text()
                && board[j]->text() == "O";
        }
    }
    
    // Right Diagonals
    for (int i = 2; i <= 12; i += 5)
    {
        for (int j = i; j < i + 3; ++j)
        {
            x_score += board[j]->text() == board[j + 4]->text() && board[j + 4]->text() == board[j + 8]->text()
                && board[j]->text() == "X";
            o_score += board[j]->text() == board[j + 4]->text() && board[j + 4]->text() == board[j + 8]->text()
                && board[j]->text() == "O";
        }
    }

    p1 = x_score;
    p2 = o_score;

    // Update scores on screen
    updateScoreLabels();

    if (n_moves == 24 && (x_score > o_score || o_score > x_score))
    {
        turn = p1 < p2;
        return true;
    }
    return false;
}


bool FFiveGame::isDraw()
{
    return n_moves == 24 && !isWinner();
}

void FFiveGame::showStatus(bool win)
{
    if (win)
    {
        stack->insertWidget(2, new ResultFrame("Player: " + players[turn]->getName() + " WINS" + 
            "\nScore: " + (turn ? ui->player2Score->text() : ui->player1Score->text()), 1, stack));
    }
    else
    {
        stack->insertWidget(2, new ResultFrame("TIE!", 0, stack));
    }
    stack->setCurrentIndex(2);
}

void FFiveGame::resetGame()
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

        // Scores
        p1 = p2 = 0;
        updateScoreLabels();

        // Moves
        n_moves = 0;

        // Turn
        turn = false;

        // PyramidPlayer 1 move
        players[turn]->getMove();
    }
}

void FFiveGame::endGame()
{
    disconnectButtons();

    for (auto& button : board)
    {
        button->setDisabled(true);
    }
}

void FFiveGame::nextPlayerMove()
{
    turn = !turn;
    players[turn]->getMove();
}

bool FFiveGame::updateBoard(QChar symbol, QColor color, int index)
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

bool FFiveGame::getTurn()
{
    return turn;
}

QVector<QVector<QChar>> FFiveGame::getBoard()
{
    QVector<QVector<QChar>> ans;

    for (int i = 0; i <= 20; i += 5)
    {
        QVector<QChar> row;
        for (int j = i; j < i + 5; ++j)
        {
            row.push_back(board[j]->text() == "X" ? 'X' : 'O');
        }
        ans.push_back(row);
    }

    return ans;
}

bool FFiveGame::incrementMoves()
{
    if (n_moves < 24)
    {
        n_moves++;
        return true;
    }
    return false;
}

void FFiveGame::connectButtons()
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
    connect(board[9], &QPushButton::clicked, this, [&]() { onButtonClick(9); });
    connect(board[10], &QPushButton::clicked, this, [&]() { onButtonClick(10); });
    connect(board[11], &QPushButton::clicked, this, [&]() { onButtonClick(11); });
    connect(board[12], &QPushButton::clicked, this, [&]() { onButtonClick(12); });
    connect(board[13], &QPushButton::clicked, this, [&]() { onButtonClick(13); });
    connect(board[14], &QPushButton::clicked, this, [&]() { onButtonClick(14); });
    connect(board[15], &QPushButton::clicked, this, [&]() { onButtonClick(15); });
    connect(board[16], &QPushButton::clicked, this, [&]() { onButtonClick(16); });
    connect(board[17], &QPushButton::clicked, this, [&]() { onButtonClick(17); });
    connect(board[18], &QPushButton::clicked, this, [&]() { onButtonClick(18); });
    connect(board[19], &QPushButton::clicked, this, [&]() { onButtonClick(19); });
    connect(board[20], &QPushButton::clicked, this, [&]() { onButtonClick(20); });
    connect(board[21], &QPushButton::clicked, this, [&]() { onButtonClick(21); });
    connect(board[22], &QPushButton::clicked, this, [&]() { onButtonClick(22); });
    connect(board[23], &QPushButton::clicked, this, [&]() { onButtonClick(23); });
    connect(board[24], &QPushButton::clicked, this, [&]() { onButtonClick(24); });
}

void FFiveGame::disconnectButtons()
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
    disconnect(board[9], &QPushButton::clicked, 0, 0);
    disconnect(board[10], &QPushButton::clicked, 0, 0);
    disconnect(board[11], &QPushButton::clicked, 0, 0);
    disconnect(board[12], &QPushButton::clicked, 0, 0);
    disconnect(board[13], &QPushButton::clicked, 0, 0);
    disconnect(board[14], &QPushButton::clicked, 0, 0);
    disconnect(board[15], &QPushButton::clicked, 0, 0);
    disconnect(board[16], &QPushButton::clicked, 0, 0);
    disconnect(board[17], &QPushButton::clicked, 0, 0);
    disconnect(board[18], &QPushButton::clicked, 0, 0);
    disconnect(board[19], &QPushButton::clicked, 0, 0);
    disconnect(board[20], &QPushButton::clicked, 0, 0);
    disconnect(board[21], &QPushButton::clicked, 0, 0);
    disconnect(board[22], &QPushButton::clicked, 0, 0);
    disconnect(board[23], &QPushButton::clicked, 0, 0);
    disconnect(board[24], &QPushButton::clicked, 0, 0);
}

void FFiveGame::updateScoreLabels()
{
    ui->player1Score->setText(QString::number(p1));
    ui->player2Score->setText(QString::number(p2));
}

void FFiveGame::onHomeButton()
{
    if (QMessageBox::warning(this, "Go To Home", "This will erase your progress\nAre you sure to exit?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        stack->setCurrentIndex(0);
    }
}

void FFiveGame::onButtonClick(int index)
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

    // Next Player's turn
    nextPlayerMove();
}