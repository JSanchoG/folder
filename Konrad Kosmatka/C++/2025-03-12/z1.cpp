#include <iostream>
#include <ctime>

////////////////
// Ustawienia //
////////////////
int BOARD_SIZE = 3; // Rozmiar pola
int INAROW = 3; // Ilość pól do wygranej
bool choosePlayer = true; // Wybieranie graczy
bool autoNewGame = false; // Automatycznie nowa gra
bool computerPlaying = false; // Komputer

void showSettings() {
    std::cout << "[⚙️] " << (choosePlayer ? "\033[1;32m" : "\033[1;31m") << "Wybieranie graczy" << "\033[0m\n";
    std::cout << "[⚙️] " << (autoNewGame ? "\033[1;32m" : "\033[1;31m") << "Automatycznie nowa gra" << "\033[0m\n";
    std::cout << "[⚙️] " << (computerPlaying ? "\033[1;32m" : "\033[1;31m") << "Komputer" << "\033[0m\n";
    // std::cout << "Wybieranie graczy: " << (choosePlayer ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
    // std::cout << "Automatycznie nowa gra: " << (autoNewGame ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
    // std::cout << "Komputer: " << (computerPlaying ? "\033[1;32mON" : "\033[1;31mOFF") << "\033[0m\n";
}

////////////////
bool scrollUp = true;
char lastMove[2];
////////////////

void clearBoard(char **board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void showBoard(char **board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((lastMove[0] != 0 && lastMove[1] != 0) && (i == lastMove[0] - 1 && j == lastMove[1] - 1)) std::cout << "\033[1;93m" << board[i][j] << "\033[0m";
            else std::cout << board[i][j];
            std::cout << (j == BOARD_SIZE - 1 ? "  " : " | ");
        }
        std::cout << std::endl;
    }
}

bool checkWin(char **board, int row, int col, int dRow, int dCol, char player) {
    int count = 0;
    for (int i = -INAROW + 1; i < INAROW; i++) {
        int r = row + i * dRow;
        int c = col + i * dCol;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == player) {
            count++;
            if (count == INAROW) return true;
        } else count = 0;
    }
    return false;
}

bool isFinished(char **board, char *winner) {
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


bool setPoint(char **board, unsigned int x, unsigned int y, char player) {
    if ((!(x <= BOARD_SIZE && y <= BOARD_SIZE)) || (x <= 0 && y <= 0)) return false;
    if (board[x - 1][y - 1] == ' ') {
        board[x - 1][y - 1] = player;
        return true;
    } else return false;
}

void cmdReset(bool scroll) {
    if (scroll) printf("\033c"); // cmd reset
    else std::cout << "\x1B[2J\x1B[H"; // cmd scroll
}

bool firstGame = true;
int main(int argc, char *argv[]) {
    /*
    Funkcja main przyjmuje 2 argumenty:
    - Rozmiar pola
    - Ilość pól do wygranej
    //////////////////////////////
     $ ./z1 5 4
     (5 pól, 4 do wygranej)
    */
    srand(time(0));
    lastMove[0] = 0;
    lastMove[1] = 0;

    if (scrollUp) cmdReset(true);
    else std::cout << std::endl;

    showSettings();

    do {
        int arg1 = 3;
        char **board;
        if (argc > 1) arg1 = (atoi(argv[1]) < 3 ? 3 : atoi(argv[1]));
        board = new char *[arg1];
        for (int i = 0; i < arg1; i++) {
            board[i] = new char[arg1];
        }

        BOARD_SIZE = arg1;
        INAROW = (argc > 2 && atoi(argv[2]) <= arg1 && atoi(argv[2]) > 2 ? atoi(argv[2]) : arg1);

        clearBoard(board);

        char winner;
        char player1 = 'x';
        char player2 = 'o';

        if (choosePlayer && firstGame) {
            std::cout << std::endl;
            std::cout << "[?] Gracz 1: ", std::cin >> player1;
            if (scrollUp) {
                cmdReset(true);
                showSettings();
                std::cout << "\n[" << player1 << "] Gracz 1" << std::endl;
                std::cout << "[?] Gracz 2: ", std::cin >> player2;
                while (player1 == player2) {
                    std::cout << "\n[!] Podaj inną nazwę." << std::endl;
                    std::cout << "[?] Gracz 2: ", std::cin >> player2;
                }
            }
        }

        if (scrollUp) cmdReset(true);
        else std::cout << std::endl;
        
        if (!scrollUp) showBoard(board);

        char playing = player1;
        while (!isFinished(board, &winner)) {
            if (playing == player2 && computerPlaying) {
                std::cout << "\n[Komputer]" << std::endl;
                int rand1 = rand() % BOARD_SIZE;
                int rand2 = rand() % BOARD_SIZE;
                while (!setPoint(board, rand1, rand2, playing)) {
                    rand1 = rand() % BOARD_SIZE;
                    rand2 = rand() % BOARD_SIZE;
                    lastMove[0] = rand1;
                    lastMove[1] = rand2;
                }
                playing = (playing == player1) ? player2 : player1;
            }
            else {
                if (scrollUp) {
                    cmdReset(true);
                    showBoard(board);
                }
                std::cout << std::endl;
                int board_x;
                std::cout << "[" << playing << "] Wiersz: ";
                std::cin >> board_x;
                lastMove[0] = board_x;
                int board_y;
                std::cout << "[" << playing << "] Kolumna: ";
                std::cin >> board_y;
                lastMove[1] = board_y;
                std::cout << std::endl;

                if (!setPoint(board, board_x, board_y, playing)) std::cerr << "[!] Pole zajęte\n" << std::endl;
                else playing = (playing == player1) ? player2 : player1;
            }

            showBoard(board);
        }

        std::cout << "\033[1;33m" << "\n[!]" << (winner == ' ' ? "\n[!] Remis!" : "\n[!] Zwycięzca: " + std::string(1, winner)) << "\n[!]" << "\033[0m" << std::endl;

        for (int i = 0; i < arg1; i++) {
            delete[] board[i];
        }
        delete[] board;

        firstGame = false;
    } while (autoNewGame);

    return 0;
}
