#include "5x5/FFiveGame.h"
#include <QMessageBox>

FFiveGame::FFiveGame(const QString& playerName1, QWidget* parent)
    : Game(parent), ui(new Ui_Form()), n_moves(0)
    , turn(0), p1(0), p2(0)
{
    ui->setupUi(this);

    // Take the two players
    this->players[0] = new FFivePlayer(this, 'X', playerName1, QColor(0, 0, 170));
    this->players[1] = new FFiveComputerPlayer(this, 'O');

    // Show Names
    ui->player1Label->setText(players[0]->get_name());
    ui->player2Label->setText(players[1]->get_name());

    // Fill the board
    board.push_back(ui->pushButton1);
    board.push_back(ui->pushButton2);
    board.push_back(ui->pushButton3);
    board.push_back(ui->pushButton4);
    board.push_back(ui->pushButton5);
    board.push_back(ui->pushButton6);
    board.push_back(ui->pushButton7);
    board.push_back(ui->pushButton8);
    board.push_back(ui->pushButton9);
    board.push_back(ui->pushButton10);
    board.push_back(ui->pushButton11);
    board.push_back(ui->pushButton12);
    board.push_back(ui->pushButton13);
    board.push_back(ui->pushButton14);
    board.push_back(ui->pushButton15);
    board.push_back(ui->pushButton16);
    board.push_back(ui->pushButton17);
    board.push_back(ui->pushButton18);
    board.push_back(ui->pushButton19);
    board.push_back(ui->pushButton20);
    board.push_back(ui->pushButton21);
    board.push_back(ui->pushButton22);
    board.push_back(ui->pushButton23);
    board.push_back(ui->pushButton24);
    board.push_back(ui->pushButton25);

    // Connecting restart game button
    connect(ui->restartButton, &QPushButton::clicked, this, &FFiveGame::reset_game);

    // Get the first move
    players[turn]->get_move();
}

// For human player
FFiveGame::FFiveGame(const QString& playerName1, const QString& playerName2, QWidget* parent)
    : FFiveGame(playerName1, parent)
{
    // Delete Random player
    delete this->players[1];

    // Create new player
    this->players[1] = new FFivePlayer(this, 'O', playerName2, QColor(170, 0, 0));

    // Update the label
    ui->player2Label->setText(players[1]->get_name());
}

FFiveGame::~FFiveGame()
{
    delete ui;
}

bool FFiveGame::is_winner()
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
    update_score_labels();

    if (n_moves == 24 && (x_score > o_score || o_score > x_score))
    {
        turn = p1 < p2;
        return true;
    }
    return false;
}


bool FFiveGame::is_draw()
{
    return n_moves == 24 && !is_winner();
}

void FFiveGame::show_status(bool win)
{
    if (win)
        QMessageBox::question(this, "Win", "Player: " + players[turn]->get_name() + " WINS", QMessageBox::Ok);
    else
        QMessageBox::question(this, "Draw", "It's a draw", QMessageBox::Ok);
}

void FFiveGame::reset_game()
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

        // Scores
        p1 = p2 = 0;
        update_score_labels();

        // Moves
        n_moves = 0;

        // Turn
        turn = false;

        // PyramidPlayer 1 move
        players[turn]->get_move();
    }
}

void FFiveGame::end_game()
{
    disconnect_buttons();

    for (auto& button : board)
    {
        button->setDisabled(true);
    }
}

void FFiveGame::next_player_move()
{
    turn = !turn;
    players[turn]->get_move();
}

bool FFiveGame::update_board(QChar symbol, int index)
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

bool FFiveGame::get_turn()
{
    return turn;
}

QVector<QVector<QChar>> FFiveGame::get_board()
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

bool FFiveGame::increment_moves()
{
    if (n_moves < 24)
    {
        n_moves++;
        return true;
    }
    return false;
}

void FFiveGame::connect_buttons()
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

void FFiveGame::disconnect_buttons()
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

void FFiveGame::update_score_labels()
{
    ui->player1Score->setText(QString::number(p1));
    ui->player2Score->setText(QString::number(p2));
}

void FFiveGame::onButtonClick(int index)
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

    // Next Player's turn
    next_player_move();
}