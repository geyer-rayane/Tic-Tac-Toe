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
        for (int i = 0; i < 3; i++) {
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
};

class Game {
private:
    Board board;
    char currentPlayer;

public:
    Game() : currentPlayer('X') {}

    void play() {
        while (true) {
            board.printBoard();
            int row, col;
            std::cout << "Enter row (0-2): ";
            std::cin >> row;
            std::cout << "Enter column (0-2): ";
            std::cin >> col;

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
};

int main() {
    Game game;
    game.play();
    return 0;
}