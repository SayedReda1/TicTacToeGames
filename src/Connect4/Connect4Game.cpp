#include "Connect4Game.h"
#include <QMessageBox>


Connect4Game::Connect4Game(const QString& playerName1, QStackedWidget* parent)
    : Game(parent), ui(new Ui_Connect4Game), n_moves(0)
    , turn(0), stack(parent)
{
    ui->setupUi(this);

    // Take the two players
    this->players[0] = new Connect4Player(this, 'X', playerName1, QColor(0, 0, 170));
    this->players[1] = new Connect4Player(this, 'O');

    // Show Names
    ui->player1Label->setText(players[0]->get_name());
    ui->player2Label->setText(players[1]->get_name());

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
    connect(ui->restartButton, &QPushButton::clicked, this, &Connect4Game::reset_game);
    connect(ui->homeButton, &QPushButton::clicked, this, &Connect4Game::onHomeButton);

    // Get the first move
    players[turn]->get_move();
}

// PvP
Connect4Game::Connect4Game(const QString& playerName1, const QString& playerName2, QStackedWidget* parent)
    : Connect4Game(playerName1, parent)
{
    delete this->players[1];
    this->players[1] = new Connect4Player(this, 'O', playerName2, QColor(170, 0, 0));

    // Retype the name
    ui->player2Label->setText(players[1]->get_name());
}

Connect4Game::~Connect4Game()
{
    delete ui;
}


bool Connect4Game::is_winner()
{
    bool found_winner = false;

    // Rows
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            found_winner |= stacks[i][j]->text() == stacks[i][j + 1]->text()
                && stacks[i][j + 1]->text() == stacks[i][j + 2]->text()
                && stacks[i][j + 2]->text() == stacks[i][j + 3]->text()
                && !stacks[i][j]->text().isEmpty();

            if (found_winner)
            {
                color_cells({ stacks[i][j], stacks[i][j + 1], stacks[i][j + 2], stacks[i][j + 3] },
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
                color_cells({ stacks[i][j], stacks[i+1][j], stacks[i+2][j], stacks[i+3][j] },
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
                color_cells({ stacks[i][j], stacks[i + 1][i + 1], stacks[i + 2][j + 2], stacks[i + 3][j + 3] },
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
                color_cells({ stacks[i][j], stacks[i + 1][j - 1], stacks[i + 2][j - 2], stacks[i + 3][j - 3] },
                    "background-color: #65B741;");
                return true;
            }
        }
    }


    return found_winner;
}

bool Connect4Game::is_draw()
{
    return n_moves == 42 && !is_winner();
}

bool Connect4Game::update_board(QChar symbol, int index)
{
    int first_filled = 5;
    while (first_filled >= 0 && stacks[index][first_filled]->text().isEmpty())
        first_filled--;

    if (first_filled < 5)
    {
        if (first_filled == 4)      // stack is filled
            disable_button(index);

        stacks[index][first_filled + 1]->setText(symbol);
        return true;
    }
    return false;
}

bool Connect4Game::get_turn()
{
    return turn;
}

QVector<QVector<QChar>> Connect4Game::get_board()
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

bool Connect4Game::increment_moves()
{
    if (n_moves < 42)
    {
        n_moves++;
        return true;
    }
    return false;
}

void Connect4Game::color_cells(const QVector<QLabel*>& labels, const QString& qss)
{
    for (auto& label : labels)
    {
        label->setStyleSheet(qss);
    }
}

void Connect4Game::enable_button(int index)
{
    adders[index]->setEnabled(true);
    adders[index]->setStyleSheet("");
}

void Connect4Game::disable_button(int index)
{
    adders[index]->setEnabled(false);
    adders[index]->setStyleSheet("background-color: rgb(27, 35, 49);");
}

void Connect4Game::show_status(bool win)
{
    if (win)
        QMessageBox::question(this, "Win", "Player: " + players[turn]->get_name() + " WINS", QMessageBox::Ok);
    else
        QMessageBox::question(this, "Draw", "It's a draw", QMessageBox::Ok);
}

void Connect4Game::reset_game()
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
            enable_button(i);
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

void Connect4Game::end_game()
{
    disconnect_buttons();

    // Disable all buttons
    for (int i = 0; i < 7; ++i)
    {
        disable_button(i);
    }
}

void Connect4Game::next_player_move()
{
    turn = !turn;
    players[turn]->get_move();
}

void Connect4Game::connect_buttons()
{
    connect(adders[0], &QPushButton::clicked, this, [&]() { onButtonClick(0); });
    connect(adders[1], &QPushButton::clicked, this, [&]() { onButtonClick(1); });
    connect(adders[2], &QPushButton::clicked, this, [&]() { onButtonClick(2); });
    connect(adders[3], &QPushButton::clicked, this, [&]() { onButtonClick(3); });
    connect(adders[4], &QPushButton::clicked, this, [&]() { onButtonClick(4); });
    connect(adders[5], &QPushButton::clicked, this, [&]() { onButtonClick(5); });
    connect(adders[6], &QPushButton::clicked, this, [&]() { onButtonClick(6); });
}

void Connect4Game::disconnect_buttons()
{
    disconnect(adders[0], &QPushButton::clicked, 0, 0);
    disconnect(adders[1], &QPushButton::clicked, 0, 0);
    disconnect(adders[2], &QPushButton::clicked, 0, 0);
    disconnect(adders[3], &QPushButton::clicked, 0, 0);
    disconnect(adders[4], &QPushButton::clicked, 0, 0);
    disconnect(adders[5], &QPushButton::clicked, 0, 0);
    disconnect(adders[6], &QPushButton::clicked, 0, 0);
}

void Connect4Game::onHomeButton()
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