#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip> 
#include "json.hpp"

using json = nlohmann::json;

//////////////////////
// USTAWIENIA START //
//////////////////////
bool SETTINGS_firstName = true;
float SETTINGS_passThreshold = 50.0f;
bool SETTINGS_paginationEnabled = false;
int SETTINGS_entriesPerPage = 10;
////////////////////
// USTAWIENIA END //
////////////////////

void cmdReset(bool scroll) {
    if (scroll) printf("\033c"); // cmd reset
    else std::cout << "\x1B[2J\x1B[H"; // cmd scroll
}

std::string color(std::string color, std::string str) {
    std::string endColor = "\033[0m";
    std::string outColor = "\033[1;";
    if (color == "black") outColor += "30m";
    else if (color == "red") outColor += "31m";
    else if (color == "green") outColor += "32m";
    else if (color == "yellow") outColor += "33m";
    else if (color == "blue") outColor += "34m";
    else if (color == "magenta") outColor += "35m";
    else if (color == "cyan") outColor += "36m";
    else if (color == "white") outColor += "37m";
    else if (color == "brightBlack") outColor += "90m";
    else if (color == "brightRed") outColor += "91m";
    else if (color == "brightGreen") outColor += "92m";
    else if (color == "brightYellow") outColor += "93m";
    else if (color == "brightBlue") outColor += "94m";
    else if (color == "brightMagenta") outColor += "95m";
    else if (color == "brightCyan") outColor += "96m";
    else if (color == "brightWhite") outColor += "97m";
    else outColor += "37m";

    return outColor + str + endColor;
}

////////////////////////////
// Funkcje programu START //
////////////////////////////
struct Student {
    int id;
    std::string firstName;
    std::string lastName;
    double score;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, id, firstName, lastName, score)
};

// void from_json(const nlohmann::json &j, Student &t) {
//     t.id = j.at("id").get<int>();
//     t.firstName = j.at("firstName").get<std::string>();
//     t.lastName = j.at("lastName").get<std::string>();
//     t.score = j.at("score").get<double>();
// }

// void to_json(nlohmann::json &j, const Student &t) {
//     j["id"] = t.id;
//     j["firstName"] = t.firstName;
//     j["lastName"] = t.lastName;
//     j["score"] = t.score;
// }

void loadEntries(std::vector<Student> &entries, const std::string &filename = "students.json") {
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf(); 
    json data = json::parse(buffer.str());

    std::vector<Student> v = data.get<std::vector<Student>>();

    for (const auto &item : v) {
        entries.push_back(item);
    }
}

void saveEntries(const std::vector<Student> &entries, const std::string &filename = "students.json") {
    std::ofstream file(filename);
    json j = entries;
    file << std::setw(4) << j;
}

// void parse() {
//     std::ifstream t("students.json");
//     std::stringstream buffer;
//     buffer << t.rdbuf(); 
//     json data = json::parse(buffer.str());

//     std::vector<Student> v = data.get<std::vector<Student>>();

//     std::cout << color("blue", "Lista studentów:") << std::endl;
//     for (const auto &item : v) {
//         if (SETTINGS_firstName) std::cout << "[" << item.id << "] " << item.firstName << " " << item.lastName << " (" << item.score << ")" << std::endl;
//         else std::cout << "[" << item.id << "] " << item.lastName << " " << item.firstName << " (" << item.score << ")" << std::endl;
//     }
// }

void displayProducts(const std::vector<Student> &entries) {
    std::cout << color("blue", "Lista studentów:") << std::endl;
    for (const auto &item : entries) {
        if (SETTINGS_firstName) std::cout << "[" << item.id << "] " << item.firstName << " " << item.lastName << " (" << item.score << ")" << std::endl;
        else std::cout << "[" << item.id << "] " << item.lastName << " " << item.firstName << " (" << item.score << ")" << std::endl;
    }
}

void sortStudents(std::vector<Student> &entries) {
    int sortField, sortOrder;
    std::string sortedBy;
    std::cout << "[1] ID\n[2] Imię\n[3] Nazwisko\n[4] Wynik\n\n" << color("blue", "Wybierz pole do sortowania: ");
    std::cin >> sortField;
    if (std::cin.fail()) return;
    if (sortField < 1 || sortField > 4) {
        cmdReset(true);
        std::cout << color("red", "[!] Nieprawidłowy numer pola") << std::endl;
        return;
    }

    std::cout << color("blue", "Sortuj rosnąco [1] czy malejąco [2]: ");
    std::cin >> sortOrder;
    if (std::cin.fail()) return;
    if (sortOrder < 1 || sortOrder > 2) {
        cmdReset(true);
        std::cout << color("red", "[!] Nieprawidłowy wybór kolejności") << std::endl;
        return;
    }

    bool ascending = (sortOrder == 1);
    auto comparator = [sortField, ascending, &sortedBy](const Student &a, const Student &b) {
        switch(sortField) {
            case 1:
                sortedBy = "ID";
                return ascending ? (a.id < b.id) : (a.id > b.id);
            case 2:
                sortedBy = "imię";
                return ascending ? (a.firstName < b.firstName) : (a.firstName > b.firstName);
            case 3:
                sortedBy = "nazwisko";
                return ascending ? (a.lastName < b.lastName) : (a.lastName > b.lastName);
            case 4:
                sortedBy = "wynik";
                return ascending ? (a.score < b.score) : (a.score > b.score);
            default:
                return false;
        }
    };

    std::sort(entries.begin(), entries.end(), comparator);
    cmdReset(true);
    std::cout << color("green", "[✓] Posortowano ") << color("green", (ascending == 1 ? "rosnąco" : "malejąco")) << color("green", " przez ") << color("green", sortedBy) << std::endl;
    // displayProducts(entries);
}

void findStudent(std::vector<Student> &entries) {
    int findID;
    std::cout << color("blue", "Szukaj ID: ");
    std::cin >> findID;
    if (std::cin.fail()) return;
    cmdReset(true);

    for (const auto &item : entries) {
        if (item.id == findID) {
            std::cout << color("blue", "Znaleziono studenta o identyfikatorze ") << std::to_string(item.id) << color("blue", ":") << std::endl;
            if (SETTINGS_firstName) std::cout << "[" << item.id << "] " << item.firstName << " " << item.lastName << " (" << item.score << ")" << std::endl;
            else std::cout << "[" << item.id << "] " << item.lastName << " " << item.firstName << " (" << item.score << ")" << std::endl;
            return;
        }
    }
    std::cout << color("blue", "[!] Nie znaleziono studenta o identyfikatorze ") << findID << std::endl;
}

void averageScore(const std::vector<Student> &entries) {
    float combinedScore = 0.0f;
    int studentsAmount = 0;

    for (const auto &item : entries) {
        combinedScore += item.score;
        studentsAmount ++;
        // studentsAmount += (item.score != 0);
    }

    if (studentsAmount > 0) std::cout << std::fixed << std::setprecision(2) << color("blue", "Średni wynik studentów: ") << (combinedScore / studentsAmount) << std::endl;
    else std::cout << "Brak dostępnych wyników" << std::endl;
}

void passFailCount(const std::vector<Student> &entries) {
    int passed = 0;
    int failed = 0;

    for (const auto &student : entries) {
        if (student.score >= 50.0) passed++;
        else failed++;
    }
    std::cout << color("green", "Zdało: ") << passed << "\n" << color("red", "Nie zdało: ") << failed << "\n" << color("blue", "Próg zdawalności: ") << color("blue", std::to_string(SETTINGS_passThreshold)) << color("blue", "%") << std::endl;
}

void removeFailedStudents(std::vector<Student> &entries) {
    auto it = std::remove_if(entries.begin(), entries.end(), [](const Student &s) {
        return s.score < SETTINGS_passThreshold;
    });
    entries.erase(it, entries.end());
}

void displayPaginated(const std::vector<Student>& entries, int currentPage) {
    const int totalEntries = entries.size();
    const int totalPages = (totalEntries + SETTINGS_entriesPerPage - 1) / SETTINGS_entriesPerPage;
    
    int start = currentPage * SETTINGS_entriesPerPage;
    int end = std::min(start + SETTINGS_entriesPerPage, totalEntries);

    std::cout << color("blue", "Lista studentów") << " (strona "  << currentPage + 1 << "/" << totalPages << ")" << color("blue", ":") << std::endl;

    for(int i = start; i < end; i++) {
        const auto& item = entries[i];
        if(SETTINGS_firstName) {
            std::cout << "[" << item.id << "] " << item.firstName << " " 
                     << item.lastName << " (" << item.score << ")\n";
        } else {
            std::cout << "[" << item.id << "] " << item.lastName << " " 
                     << item.firstName << " (" << item.score << ")\n";
        }
    }

    std::cout << "\n" << color("yellow", "Nawigacja: ") << "[" << color("yellow", "N") << "]astępna | [" << color("yellow", "P") << "]oprzednia | [" << color("yellow", "G") << "]oto (nr strony) | [" << color("yellow", "Q") << "]uit\n";
    std::cout << color("blue", "Wybierz akcję: ");
}

void handlePagination(std::vector<Student>& entries) {
    if(entries.empty()) {
        std::cout << color("red", "Brak studentów do wyświetlenia") << std::endl;
        return;
    }

    int currentPage = 0;
    const int totalPages = (entries.size() + SETTINGS_entriesPerPage - 1) / SETTINGS_entriesPerPage;
    
    while(true) {
        cmdReset(true);
        displayPaginated(entries, currentPage);

        char choice;
        std::cin >> choice;
        choice = toupper(choice);

        switch(choice) {
            case 'N':
                if(currentPage < totalPages - 1) currentPage++;
                break;
            case 'P':
                if(currentPage > 0) currentPage--;
                break;
            case 'G': {
                int page;
                std::cout << color("blue", "Podaj numer strony") << " (1-" << totalPages << "): ";
                if(std::cin >> page && page >= 1 && page <= totalPages) {
                    currentPage = page - 1;
                } else {
                    std::cout << color("red", "Nieprawidłowy numer strony") << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
            case 'Q':
                cmdReset(true);
                return;
            default:
                std::cout << color("red", "Nieprawidłowy wybór") << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
void openSettings() {
    int settings_option;
    bool settingsOpen = true;
    do {
        std::cout << color("blue", "[⚙️] Ustawienia") << std::endl;
        std::cout << "[1] Kolejność: " << (SETTINGS_firstName ? "Imię, Nazwisko" : "Nazwisko, Imię") << std::endl;
        std::cout << "[2] Próg zdawalności: " << SETTINGS_passThreshold << "%" << std::endl;
        std::cout << "[3] Paginacja: " << (SETTINGS_paginationEnabled ? color("green", "ON") : color("red", "OFF")) << std::endl;
        std::cout << "[4] Liczba wyników na stronę: " << SETTINGS_entriesPerPage << std::endl;
        std::cout << "[5] Powrót" << std::endl;
        std::cout << "\n" << color("blue", "Wybierz: ");
        std::cin >> settings_option;
        if (std::cin.fail()) return;
        switch(settings_option) {
            case 1:
                cmdReset(true);
                SETTINGS_firstName = !SETTINGS_firstName;
                break;
            case 2:
                cmdReset(true);
                std::cout << color("blue", "Aktualny próg zdawalności: ") << SETTINGS_passThreshold << "%" << std::endl;
                std::cout << color("blue", "Podaj nowy próg") << " (0-100)" << color("blue", ": ");
                float newThreshold;
                std::cin >> newThreshold;
                if (newThreshold >= 0 && newThreshold <= 100) {
                    SETTINGS_passThreshold = newThreshold;
                    cmdReset(true);
                    std::cout << color("green", "[✓] Zaktualizowano próg zdawalności\n") << std::endl;
                } else {
                    cmdReset(true);
                    std::cout << color("red", "[!] Nieprawidłowa wartość") << std::endl;
                }
                break;
            case 3:
                cmdReset(true);
                SETTINGS_paginationEnabled = !SETTINGS_paginationEnabled;
                break;
            case 4:
                std::cout << color("blue", "Podaj nową liczbę wyników na stronę: ");
                std::cin >> SETTINGS_entriesPerPage;
                cmdReset(true);
                SETTINGS_entriesPerPage = std::max(1, SETTINGS_entriesPerPage);
                break;
            case 5:
                cmdReset(true);
                settingsOpen = false;
                break;
            default:
                cmdReset(true);
                std::cout << color("red", "[!] Nieprawidłowy input\n") << std::endl;
        }
    } while (settingsOpen);
}
//////////////////////////
// Funkcje programu END //
//////////////////////////

int main(int argc, char *argv[]) {
    std::vector<Student> entries;
    loadEntries(entries);

    cmdReset(true);

    int option;
    bool firstRun = false;
    do {
        if (firstRun) std::cout << std::endl;
        else firstRun = true;

        // std::cout << "1. Wypisz dane wszystkich studentów wraz z wyliczoną oceną\n2. Sortuj studentów według pola w wybranej kolejności\n3. Znajdź studenta (ID)\n4. Średni wynik studentów\n5. Policz ilu studentów zdało i ilu nie zdało\n6. Usuń studentów, którzy nie zdali\n7. Ustawienia\n8. Zakończ program\n\n" << color("blue", "Wybierz: ");
        std::cout << "1. Wypisz dane wszystkich studentów\n2. Sortuj studentów\n3. Znajdź studenta (ID)\n4. Średni wynik studentów\n5. Policz ilu studentów zdało i ilu nie zdało\n6. Usuń studentów, którzy nie zdali\n7. Ustawienia\n8. Zakończ program\n\n" << color("blue", "Wybierz: ");
        std::cin >> option;
        if (std::cin.fail()) break;

        cmdReset(true);

        switch(option) {
            case 1:
                // parse();
                if(SETTINGS_paginationEnabled) handlePagination(entries);
                else displayProducts(entries);
                break;
            case 2:
                sortStudents(entries);
                break;
            case 3:
                findStudent(entries);
                break;
            case 4:
                averageScore(entries);
                break;
            case 5:
                passFailCount(entries);
                break;
            case 6:
                removeFailedStudents(entries);
                cmdReset(true);
                std::cout << color("green", "[✓] Usunięto studentów z wynikiem poniżej 50%") << std::endl;
                break;
            case 7:
                openSettings();
                break;
            case 8:
                saveEntries(entries);
                return 0;
            default:
                std::cout << color("red", "[!] Nieprawidłowy input") << std::endl;
        }
    } while (true);

    return 0;
}