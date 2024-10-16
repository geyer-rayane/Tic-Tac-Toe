#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


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
        sf::RenderWindow window(sf::VideoMode(600, 600), "Tic-Tac-Toe");
        sf::Font font;
        //font.loadFromFile("arial.ttf"); // load a font

        sf::Text text[9];
        for (int i = 0; i < 9; i++) {
            text[i].setFont(font);
            text[i].setCharacterSize(100);
            text[i].setPosition(220 + (i % 3) * 100, 100 + (i / 3) * 100);
            text[i].setFillColor(sf::Color::Black); //ssssss
        }

        sf::RectangleShape rect[9];
        for (int i = 0; i < 9; i++) {
            rect[i].setSize(sf::Vector2f(100, 100));
            rect[i].setPosition(200 + (i % 3) * 100, 100 + (i / 3) * 100);
            rect[i].setFillColor(sf::Color::White);
            rect[i].setOutlineColor(sf::Color::Black);
            rect[i].setOutlineThickness(2);
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

             if (event.type == sf::Event::MouseButtonPressed) {
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;

    int row = (y - 100) / 100;
    int col = (x - 200) / 100;

    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        int move = row * 3 + col;
        if (board.isValidMove(row, col)) {
            board.makeMove(row, col, 'X');
            text[move].setString("X");
            rect[move].setFillColor(sf::Color::Blue); // Set rectangle color to blue for player X

            if (board.isWin('X')) {
                std::cout << "Player X wins!\n";
                window.close();
            }

            int aiMove = getAiMove();
            int aiRow = aiMove / 3;
            int aiCol = aiMove % 3;
            board.makeMove(aiRow, aiCol, 'O');
            text[aiMove].setString("O");
            rect[aiMove].setFillColor(sf::Color::Red); // Set rectangle color to red for IA O
        }
    }
}
            }

            window.clear();
            for (int i = 0; i < 9; i++) {
                window.draw(rect[i]);
                window.draw(text[i]);
            }
            window.display();
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

