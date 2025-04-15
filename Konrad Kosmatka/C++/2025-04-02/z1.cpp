#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <list>

class TimeMeasurement {
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    TimeMeasurement(std::string _name) : name(_name) {
        start = std::chrono::high_resolution_clock::now();
    }

    ~TimeMeasurement() {
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << name << ": " << duration.count() << " sec" << std::endl;
    }
};

/* Przykład użycia: */
int main() {
    const int N = 100000;

    printf("\n");

    // Wektor
    {
        TimeMeasurement t("Wektor");
        std::vector<int> vec;
        vec.reserve(N);
        for (int i = 0; i < N; i++) {
            // vec.push_back(i);
            vec.insert(vec.begin(), 123456);

		}
    }
    // Wektor + sumowanie
    {
        TimeMeasurement t("Wektor + sumowanie");
        std::vector<int> vec;
        vec.reserve(N);
        for (int i = 0; i < N; i++) {
            vec.insert(vec.begin(), 123456);
		}
        auto sum_start = std::chrono::high_resolution_clock::now();
        long long sum = 0;
        for (int val : vec) {
            sum += val;
        }
        auto sum_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sum_duration = sum_end - sum_start;
        std::cout << "Sumowanie: " << sum_duration.count() << " sec" << std::endl;
    }

    printf("\n");

    // Lista
    {
        TimeMeasurement t("Lista");
        std::list<int> lst;
        for (int i = 0; i < N; i++) {
            // lst.push_back(i);
            lst.insert(lst.begin(), 123456);

        }
    }
    // Lista + sumowanie
    {
        TimeMeasurement t("Lista + sumowanie");
        std::list<int> lst;
        for (int i = 0; i < N; i++) {
            lst.insert(lst.begin(), 123456);
        }
        auto sum_start = std::chrono::high_resolution_clock::now();
        long long sum = 0;
        for (int val : lst) {
            sum += val;
        }
        auto sum_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sum_duration = sum_end - sum_start;
        std::cout << "Sumowanie: " << sum_duration.count() << " sec" << std::endl;
    }

    printf("\n");

    return 0;
}