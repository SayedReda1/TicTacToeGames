#include "PyramidGame.h"


PyramidComputerPlayer::PyramidComputerPlayer(Game* game, QChar symbol)
	: game(game), symbol(symbol), name("Computer Player")
{
}

PyramidComputerPlayer::PyramidComputerPlayer(Game* game, QChar symbol, const QColor& color)
	: game(game), name("Computer Player"), color(color), symbol(symbol)
{
}

QChar PyramidComputerPlayer::getSymbol()
{
    return symbol;
}

QColor PyramidComputerPlayer::getColor()
{
    return color;
}

QString PyramidComputerPlayer::getName()
{
    return name;
}

void PyramidComputerPlayer::getMove()
{
	// 1) Try the algo and make a move
	QVector<QChar> board = game->getBoard()[0];

	int maxScore = -1000, x = -1;
	for (int i = 0; i < 9; ++i)
	{
		if (board[i] == ' ')
		{
			board[i] = symbol;

			int score = minimax(board, false);

            board[i] = ' ';

			if (score >= maxScore)
			{
				maxScore = score;
				x = i;
			}
		}
	}
	game->updateBoard(symbol, x);

	// 2) Check for a winner
	if (game->isWinner())
	{
		game->showStatus(true);
		game->endGame();
		return;
	}
	else if (game->isDraw())
	{
		game->showStatus(false);
		game->endGame();
		return;
	}

	// 3) Next player
	game->nextPlayerMove();
}

int PyramidComputerPlayer::minimax(QVector<QChar>& board, bool isMaximizing)
{
    int check = this->check(board);
    if (check != 1)
        return check;

    if (isMaximizing)
    {
        int maxScore = -1000;
        for (int i = 0; i < 9; ++i)
        {
            if (board[i] == ' ')
            {
                board[i] = symbol;

                int score = minimax(board, false);

                board[i] = ' ';

                // Maximizing
                maxScore = std::max(maxScore, score);
            }
        }

        return maxScore;
    }
    else
    {
        int minScore = 1000;
        for (int i = 0; i < 9; ++i)
        {
            if (board[i] == ' ')
            {
                board[i] = (symbol == 'X') ? 'O' : 'X';

                int score = minimax(board, true);

                board[i] = ' ';

                // Maximizing
                minScore = std::min(minScore, score);
            }
        }

        return minScore;
    }
}

int PyramidComputerPlayer::check(QVector<QChar>& board)
{
	// 10	-> PyramidComputerPlayer wins
	// -10	-> Opponent wins
	// 0	-> draw
	// 1	-> non of the above

    bool me = false, opp = false;
    QChar oppSymbol = symbol == 'X' ? 'O' : 'X';

    int checks[][3]{ 
        {1, 2, 3}, {4, 5, 6}, {5, 6, 7}, {6, 7, 8},     // Rows
        {0, 2, 6},                                      // Cols
        {0, 1, 4}, {0, 3, 8}                            // Diagonals
    };

    for (auto [x, y, z] : checks)
    {
        me |= board[x] == board[y] && board[y] == board[z] && board[x] == symbol;
        opp |= board[x] == board[y] && board[y] == board[z] && board[x] == oppSymbol;
    }

    if (me || opp)
        return me ? 10 : -10;
    else
    {
        for (int i = 0; i < 9; ++i)
            if (board[i] == ' ')
                return 1;
        return 0;
    }
}
