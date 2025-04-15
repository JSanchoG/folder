#include <iostream>
#include <ctime>

////////////////
// Ustawienia //
////////////////
#define BOARD_SIZE 3 // Rozmiar pola
#define INAROW BOARD_SIZE // Ilość pól do wygranej
bool choosePlayer = true; // Wybieranie graczy
bool autoNewGame = false; // Automatycznie nowa gra
bool computerPlaying = false; // Komputer
////////////////

char board[BOARD_SIZE][BOARD_SIZE];

void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void showBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << (j == BOARD_SIZE - 1 ? "  " : " | ");
        }
        std::cout << std::endl;
    }
}

bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, int dRow, int dCol, char player) {
    int count = 0;
    for (int i = -INAROW + 1; i < INAROW; i++) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
            count++;
            if (count == INAROW) return true;
        } else {
            count = 0;
        }
    }
    return false;
}

bool isFinished(char board[BOARD_SIZE][BOARD_SIZE], char *winner) {
    bool fullBoard = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') fullBoard = false;
            else {
                char player = board[i][j];
                if (checkWin(board, i, j, 1, 0, player) ||  // Pionowo
                    checkWin(board, i, j, 0, 1, player) ||  // Poziomo
                    checkWin(board, i, j, 1, 1, player) ||  // Przekątna
                    checkWin(board, i, j, 1, -1, player)) { // Przekątna
                    *winner = player;
                    return true;
                }
            }
        }
    }
    if (fullBoard) {
        *winner = ' ';
        return true;
    }
    return false;
}


bool setPoint(char board[BOARD_SIZE][BOARD_SIZE], unsigned int x, unsigned int y, char player) {
    if (!(x - 1 <= BOARD_SIZE && y - 1 <= BOARD_SIZE)) return false;
    if (board[x - 1][y - 1] == ' ') {
        board[x - 1][y - 1] = player;
        return true;
    } else {
        return false;
    }
}

bool firstGame = true;
int main() {
    if (firstGame) {
        srand(time(0));
        std::cout << std::endl;
        std::cout << "[⚙️] " << (choosePlayer ? "\033[1;32m" : "\033[1;31m") << "Wybieranie graczy" << "\033[0m\n";
        std::cout << "[⚙️] " << (autoNewGame ? "\033[1;32m" : "\033[1;31m") << "Automatycznie nowa gra" << "\033[0m\n";
        std::cout << "[⚙️] " << (computerPlaying ? "\033[1;32m" : "\033[1;31m") << "Komputer" << "\033[0m\n";
        // std::cout << "Wybieranie graczy: " << (choosePlayer ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
        // std::cout << "Automatycznie nowa gra: " << (autoNewGame ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
        // std::cout << "Komputer: " << (computerPlaying ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
    }
    char winner;
    char player1 = 'x';
    char player2 = 'o';

    clearBoard(board);

    if (choosePlayer && firstGame) {
        std::cout << std::endl;
        std::cout << "[?] Gracz 1: ", std::cin >> player1;
        std::cout << "[?] Gracz 2: ", std::cin >> player2;
        while (player1 == player2) {
            std::cout << "\n[!] Podaj inną nazwę." << std::endl;
            std::cout << "[?] Gracz 2: ", std::cin >> player2;
        }
    }

    std::cout << std::endl;
    showBoard(board);

    char playing = player1;
    while (!isFinished(board, &winner)) {
        if (playing == player2 && computerPlaying) {
            std::cout << "\n[Komputer]" << std::endl;
            int rand1 = rand() % BOARD_SIZE;
            int rand2 = rand() % BOARD_SIZE;
            while (!setPoint(board, rand1, rand2, playing)) {
                rand1 = rand() % BOARD_SIZE;
                rand2 = rand() % BOARD_SIZE;
            }
            playing = (playing == player1) ? player2 : player1;
        } else {
            std::cout << std::endl;
            int board_x;
            std::cout << "[" << playing << "] Wiersz: "; std::cin >> board_x;
            int board_y;
            std::cout << "[" << playing << "] Kolumna: "; std::cin >> board_y;
            std::cout << std::endl;
            
            if (!setPoint(board, board_x, board_y, playing)) std::cerr << "[!] Pole zajęte\n" << std::endl;
            else playing = (playing == player1) ? player2 : player1;
        }

        showBoard(board);
    }

    std::cout << "\033[1;33m" << "\n[!]" << (winner == ' ' ? "\n[!] Remis!" : "\n[!] Zwycięzca: " + std::string(1, winner)) << "\n[!]" << "\033[0m" << std::endl;
    
    if (autoNewGame) {
        firstGame = false;
        main();
    }
}
