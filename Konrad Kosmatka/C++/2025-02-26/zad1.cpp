#include <iostream>

int main (int argc, char *argv[]) {
    int liczba;
    int argument;
    do {
        std::cout << "\n1. Wypisz ilość argumentów programu\n2. Wypisz wybrany argument programu\n3. Wypisz wszystkie argumenty programu\n4. Zakończ program" << std::endl;
        std::cout << "Wprowadź liczbę: ", std::cin >> liczba;
        switch(liczba) {
            case 1:
                std::cout << "\n> Ilość argumentów programu: " << argc - 1 << std::endl;
                break;
            case 2:
                std::cout << "Wybierz argument: ", std::cin >> argument;
                if (argument >= 0 && argument < argc) {
                    std::cout << "\n> Wybrany argument programu: " << argv[argument] << std::endl;
                } else std::cout << "\n> Podano niepoprawny argument" << std::endl;
                break;
            case 3:
                std::cout << "\nArgumenty programu:" << std::endl;
                for (int i = 1; i < argc; i++) {
                    std::cout << "> " << argv[i] << std::endl;
                }
                break;
            case 4:
                std::cout << "\n> Zakończono program" << std::endl;
                break;
            default:
                std::cerr << "\n> Podano niepoprawną liczbę" << std::endl;
        }
    } while (liczba != 4);
}