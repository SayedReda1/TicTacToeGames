#include "Connect4Game.h"
#include "ResultFrame.h"
#include <QTimer>
#include <QMessageBox>

Connect4Game::Connect4Game(Player* player1, Player* player2, QStackedWidget* parent)
    : Game(parent), ui(new Ui_Connect4Game), n_moves(0)
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

    // Fill the stacks vector
    for (int i = 0; i < 7; ++i)
    {
        QVector<QLabel*> stack;
        for (int j = 0; j < 6; ++j)
        {
            // index = i*6 + j + 1
            stack.push_back(ui->boardFrame->findChild<QLabel*>("cell" + QString::number(6 * i + j + 1)));
        }
        this->stacks.push_back(stack);
    }


    // Fill Buttons vector
    for (int i = 1; i <= 7; ++i)
    {
        this->adders.push_back(ui->boardFrame->findChild<QPushButton*>("push" + QString::number(i)));
    }

    // Restart Button & Home Button
    connect(ui->restartButton, &QPushButton::clicked, this, &Connect4Game::resetGame);
    connect(ui->homeButton, &QPushButton::clicked, this, &Connect4Game::onHomeButtonClick);

    // Get the first move
    players[turn]->getMove();
}

Connect4Game::~Connect4Game()
{
    delete players[0];
    delete players[1];
    delete ui;
}


bool Connect4Game::isWinner()
{
    bool found_winner = false;

    // Rows
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            found_winner |= stacks[i][j]->text() == stacks[i][j + 1]->text()
                && stacks[i][j + 1]->text() == stacks[i][j + 2]->text()
                && stacks[i][j + 2]->text() == stacks[i][j + 3]->text()
                && !stacks[i][j]->text().isEmpty();

            if (found_winner)
            {
                styleCells({ stacks[i][j], stacks[i][j + 1], stacks[i][j + 2], stacks[i][j + 3] },
                    "background-color: #65B741;");
                return true;
            }
        }
    }

    // Columns
    for (int j = 0; j < 6; ++j)
    {
        for (int i = 0; i < 4; ++i)
        {
            found_winner |= stacks[i][j]->text() == stacks[i+1][j]->text()
                && stacks[i+1][j]->text() == stacks[i+2][j]->text()
                && stacks[i+2][j]->text() == stacks[i+3][j]->text()
                && !stacks[i][j]->text().isEmpty();

            if (found_winner)
            {
                styleCells({ stacks[i][j], stacks[i+1][j], stacks[i+2][j], stacks[i+3][j] },
                    "background-color: #65B741;");
                return true;
            }
        }
    }

    // Diagonals
    for (int i = 0; i < 4; ++i)
    {
        // +row +col
        for (int j = 0; j < 3; ++j)
        {
            found_winner |= stacks[i][j]->text() == stacks[i + 1][j + 1]->text()
                && stacks[i + 1][j + 1]->text() == stacks[i + 2][j + 2]->text()
                && stacks[i + 2][j + 2]->text() == stacks[i + 3][j + 3]->text()
                && !stacks[i][j]->text().isEmpty();

            if (found_winner)
            {
                styleCells({ stacks[i][j], stacks[i + 1][i + 1], stacks[i + 2][j + 2], stacks[i + 3][j + 3] },
                    "background-color: #65B741;");
                return true;
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        // -j +i
        for (int j = 3; j < 6; ++j)
        {
            found_winner |= stacks[i][j]->text() == stacks[i + 1][j - 1]->text()
                && stacks[i + 1][j - 1]->text() == stacks[i + 2][j - 2]->text()
                && stacks[i + 2][j - 2]->text() == stacks[i + 3][j - 3]->text()
                && !stacks[i][j]->text().isEmpty();

            if (found_winner)
            {
                styleCells({ stacks[i][j], stacks[i + 1][j - 1], stacks[i + 2][j - 2], stacks[i + 3][j - 3] },
                    "background-color: #65B741;");
                return true;
            }
        }
    }


    return found_winner;
}

bool Connect4Game::isDraw()
{
    return n_moves == 42 && !isWinner();
}

bool Connect4Game::updateBoard(QChar symbol, const QColor& color, int index)
{
    int firstFilled = 5;
    while (firstFilled >= 0 && stacks[index][firstFilled]->text().isEmpty())
        firstFilled--;

    if (firstFilled < 5)
    {
        stacks[index][firstFilled + 1]->setText(symbol);
        stacks[index][firstFilled + 1]->setStyleSheet("color: " + color.name() + ";");

        if (firstFilled == 4)      // stack is filled
            disableButton(index);

        return true;
    }
    return false;
}

bool Connect4Game::getTurn()
{
    return turn;
}

QVector<QVector<QChar>> Connect4Game::getBoard()
{
    QVector<QVector<QChar>> arr;

    for (int i = 0; i < 7; ++i)
    {
        QVector<QChar> stack;
        for (int j = 0; j < 6; ++j)
        {
            stack.push_back(stacks[i][j]->text() == "X" ? 'X' : 
                stacks[i][j]->text() == "O" ? 'O' : ' ');
        }
    }

    return arr;
}

bool Connect4Game::incrementMoves()
{
    if (n_moves < 42)
    {
        n_moves++;
        return true;
    }
    return false;
}

void Connect4Game::styleCells(const QVector<QLabel*>& labels, const QString& qss)
{
    for (auto& label : labels)
        label->setStyleSheet(qss);
}

void Connect4Game::enableButton(int index)
{
    adders[index]->setEnabled(true);
    adders[index]->setStyleSheet("");
}

void Connect4Game::disableButton(int index)
{
    adders[index]->setEnabled(false);
    adders[index]->setStyleSheet("background-color: rgb(27, 35, 49);");
}

void Connect4Game::showStatus(bool win)
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

void Connect4Game::resetGame()
{
    if (QMessageBox::warning(this, "Reset", "Are you sure to reset the game?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        // Cells and buttons
        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                stacks[i][j]->setText("");
                stacks[i][j]->setStyleSheet("");
            }
            enableButton(i);
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

void Connect4Game::endGame()
{
    disconnectButtons();

    // Disable all buttons
    for (int i = 0; i < 7; ++i)
    {
        disableButton(i);
    }
}

void Connect4Game::nextPlayerMove()
{
    turn = !turn;
    players[turn]->getMove();
}

void Connect4Game::connectButtons()
{
    connect(adders[0], &QPushButton::clicked, this, [&]() { onButtonClick(0); });
    connect(adders[1], &QPushButton::clicked, this, [&]() { onButtonClick(1); });
    connect(adders[2], &QPushButton::clicked, this, [&]() { onButtonClick(2); });
    connect(adders[3], &QPushButton::clicked, this, [&]() { onButtonClick(3); });
    connect(adders[4], &QPushButton::clicked, this, [&]() { onButtonClick(4); });
    connect(adders[5], &QPushButton::clicked, this, [&]() { onButtonClick(5); });
    connect(adders[6], &QPushButton::clicked, this, [&]() { onButtonClick(6); });
}

void Connect4Game::disconnectButtons()
{
    disconnect(adders[0], &QPushButton::clicked, 0, 0);
    disconnect(adders[1], &QPushButton::clicked, 0, 0);
    disconnect(adders[2], &QPushButton::clicked, 0, 0);
    disconnect(adders[3], &QPushButton::clicked, 0, 0);
    disconnect(adders[4], &QPushButton::clicked, 0, 0);
    disconnect(adders[5], &QPushButton::clicked, 0, 0);
    disconnect(adders[6], &QPushButton::clicked, 0, 0);
}

void Connect4Game::onHomeButtonClick()
{
    if (QMessageBox::warning(this, "Go To Home", "This will erase your progress\nAre you sure to exit?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        stack->setCurrentIndex(0);
    }
}

void Connect4Game::onButtonClick(int index)
{

    // index < 0, means don't update board
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
