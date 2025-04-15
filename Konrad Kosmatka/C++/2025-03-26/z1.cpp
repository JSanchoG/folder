#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

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

struct Product {
    std::string name;
    int price;
    int qty;
};

////////////////////////////
// Funkcje programu START //
////////////////////////////

void displayProducts(const std::vector<Product> &products) {
    // std::cout << "Spis produktów:\n";
    std::cout << color("blue", "Nazwa:") << "\t" << color("blue", "Cena:") << "\t" << color("blue", "Ilość:") << "\n";
    for (const auto& p : products) {
        std::cout << p.name << "\t" << p.price << "\t" << p.qty << "\n";
    }
}

void addProduct(std::vector<Product> &products) {
    Product p;
    std::cout << "Podaj nazwę: ";
    std::cin >> p.name;
    std::cout << "Podaj cenę: ";
    std::cin >> p.price;
    std::cout << "Podaj ilość: ";
    std::cin >> p.qty;

    if (p.price < 0 || p.qty < 0 || p.name.empty()) {
        std::cout << color("red", "\n[!] Nieprawidłowa cena lub ilość\n");
        return;
    }

    for (auto &pr : products) {
        if (pr.name == p.name && pr.price == p.price) {
            pr.qty += p.qty;
            return;
        }
    }

    products.push_back(p);
}

void removeProduct(std::vector<Product> &products) {
    std::string name;
    std::cout << "Podaj nazwę: ";
    std::cin >> name;
    products.erase(std::remove_if(products.begin(), products.end(), [&](const Product &p) { return p.name == name; }), products.end());
}

void changeQuantity(std::vector<Product> &products) {
    std::string name;
    int qty;
    std::cout << "Podaj nazwę: ";
    std::cin >> name;
    std::cout << "Podaj nową ilość: ";
    std::cin >> qty;
    if (qty < 0) {
        std::cout << color("red", "\n[!] Nieprawidłowa ilość\n");
        return;
    }
    int oldQty;
    for (auto &p : products) {
        if (p.name == name) {
            oldQty = p.qty;
            p.qty = qty;
            std::cout << color("blue", "\n[?] Zmieniono ilość ") << p.name << color("blue", " z ") << oldQty << color("blue", " na ") << qty << color("blue", ".\n");
            return;
        }
    }
    std::cout << color("blue", "[!] Nie znaleziono produktu\n");
    return;
}

void searchProduct(const std::vector<Product> &products) {
    std::string name;
    std::cout << "Podaj nazwę: ";
    std::cin >> name;
    std::cout << std::endl;
    for (const auto &p : products) {
        if (p.name == name) {
            std::cout << color("blue", "Nazwa:") << "\t" << color("blue", "Cena:") << "\t" << color("blue", "Ilość:") << "\n";
            std::cout << p.name << "\t" << p.price << "\t" << p.qty << "\n";
            return;
        }
    }
    std::cout << color("blue", "[!] Nie znaleziono produktu\n");
}

void saveProducts(const std::vector<Product> &products, const std::string &filename) {
    std::ofstream file(filename);
    for (const auto &p : products) file << p.name << " " << p.price << " " << p.qty << "\n";
}

void loadProducts(std::vector<Product> &products, const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        Product p;
        if (iss >> p.name >> p.price >> p.qty) products.push_back(p);
    }
}

//////////////////////////
// Funkcje programu END //
//////////////////////////

int main(int argc, char *argv[]) {
    std::string filename = (argc > 1) ? argv[1] : "magazyn.txt";
    std::vector<Product> products;
    loadProducts(products, filename);

    cmdReset(true);

    int option;
    bool firstRun = false;
    do {
        if (firstRun) std::cout << std::endl;
        firstRun = true;

        std::cout << "1. Wyświetl spis wszystkich produktów\n2. Dodaj produkt\n3. Usuń produkt\n4. Zmień ilośc produktu\n5. Wyszukaj produkt po nazwie\n6. Zakończ program\n\n" + color("blue", "Wybierz: ");
        std::cin >> option;

        cmdReset(true);

        if (option == 1) displayProducts(products);
        else if (option == 2) addProduct(products);
        else if (option == 3) removeProduct(products);
        else if (option == 4) changeQuantity(products);
        else if (option == 5) searchProduct(products);
        else if (option == 6) {
            saveProducts(products, (argc > 1 ? argv[1] : "magazyn.txt"));
            return 0;
        }
        else std::cout << color("red", "[!] Nieprawidłowy input");
    } while (true);

    return 0;
}