#include <iostream>
#include <vector>

class Board {
private:
    std::vector<std::vector<char>> board;

public:

    Board() {
        board.resize(3, std::vector<char>(3, ' '));
    }

   void printBoard() {
    std::cout << "  0 | 1 | 2\n";
    std::cout << "---+---+---\n";
    for (int i = 0; i < 3; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n";
        if (i < 2) {
            std::cout << "---+---+---\n";
        }
    }
}

    bool isValidMove(int row, int col) {
        return board[row][col] == ' ';
    }

    bool makeMove(int row, int col, char player) {
        if (isValidMove(row, col)) {
            board[row][col] = player;
            return true;
        }
        return false;
    }

    bool isWin(char player) {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }

        // Check diagonals
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
        }

        return false;
    }

    void undoMove(int row, int col) {
    board[row][col] = ' ';
}

    bool isFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
}
};

class Game {
private:
    Board board;
    char currentPlayer;
    char aiPlayer;

public:
    Game() : currentPlayer('X'), aiPlayer('O') {}

    void play() {
        while (true) {
            board.printBoard();
            int move;
            if (currentPlayer == 'X') {
                std::cout << "Enter your move (0-8): ";
                if (!(std::cin >> move)) {
                    std::cout << "Invalid input. Please enter a number.\n";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }
                if (move < 0 || move > 8) {
                    std::cout << "Invalid move. Please enter a number between 0 and 8.\n";
                    continue;
                }
            } else {
                move = getAiMove();
                std::cout << "AI move: " << move << std::endl;
            }

            // Calculate row and column from move
            int row = move / 3;
            int col = move % 3;

            if (board.makeMove(row, col, currentPlayer)) {
                if (board.isWin(currentPlayer)) {
                    board.printBoard();
                    std::cout << "Player " << currentPlayer << " wins!\n";
                    return;
                }

                // Switch player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

            } else {
                std::cout << "Invalid move. Try again.\n";
            }
        }
    }

    int getAiMove() {
        int bestScore = -1000;
        int bestMove = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, aiPlayer);
                    int score = minimax(board, 0, false);
                    board.undoMove(i, j);
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = i * 3 + j;
                    }
                }
            }
        }
        return bestMove;
    }

    int minimax(Board board, int depth, bool isMaximizing) {
        if (board.isWin(aiPlayer)) {
            return 10;
        } else if (board.isWin('X')) {
            return -10;
        } else if (board.isFull()) {
            return 0;
        }

        if (isMaximizing) {
            int bestScore = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, aiPlayer);
                        int score = minimax(board, depth + 1, false);
                        board.undoMove(i, j);
                        bestScore = std::max(score, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isValidMove(i, j)) {
                        board.makeMove(i, j, 'X');
                        int score = minimax(board, depth + 1, true);
                        board.undoMove(i, j);
                        bestScore = std::min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}

