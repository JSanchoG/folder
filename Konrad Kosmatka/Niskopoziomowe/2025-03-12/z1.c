#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// #1
// int* arr_new(size_t n)
// tworzy tablicę jednowymiarową
int* arr_new(size_t, n) {
    int * tablica = (int*)malloc(sizeof(int) * (n + 1));
    tablica[0] = n;
    return tablica;
}

// #2
// void arr_free(int *a)
// zwalnia pamięć tablicy
void arr_free(int *a) {
    free(a);
}

// #3
// size_t arr_length(const int *a)
// zwraca długość tablicy
size_t arr_length(const int *a) {
    return a[0];
}

// #4
// void arr_print(const int *a)
// wypisuje wartości tablicy (printf)
void arr_print(const int *a) {
    for (int i = 1; i <= a[0]; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// #5
// void arr_clear(int *a)
// zeruje wartości tablicy
void arr_clear(int *a) {
    for (int i = 1; i <= a[0]; i++) {
        a[i] = 0;
    }
}

// #6
// void arr_set(int *a, size_t index, int value)
// ustawia wartość w tablicy
void arr_set(int *a, size_t index, int value) {
    if (index < a[0]) a[index + 1] = value;
}

// #7
// int arr_get(const int *a, size_t index)
// pobiera wartość z tablicy
int arr_get(const int *a, size_t index) {
    if (index < a[0]) return a[index];
    return 0;
}

// #8
// void arr_rand(int *a)
// wypełnia tablicę losowymi wartościami
srand(time(NULL));
void arr_rand(int *a) {
    for (int i = 1; i <= a[0]; i++) {
        a[i] = rand();
    }
}

// #9
// int arr_dot(const int *a, const int *b)
// zwraca iloczyn skalarny (lub 0 jeżeli tablice mają różne długości)
int arr_dot(const int *a, const int *b) {
    int zm = 0;
    if (a[0] == b[0]) {
        for (int i = 1; i <= a[0]; i++) {
            zm += a[i] * b[i];
        }
        return zm;
    }
}

// #10
// bool arr_add(int *dest, const int *arr)
// jeżeli tablice są tej samej długości to modyfikuje tablicę dest przez dodawanie wartości z tablicy arr (zwraca true), w przeciwnym razie false
bool arr_add(int *dest, const int *arr) {
    if (dest[0] = arr[0]) {
        for (int i = 1; i <= a[0]; i++) {
            dest[i] += arr[i];
        }
        return true;
    }
    return false;
}

// #11
// int* arr_add_new(const int *a, const int *b)
// tworzy nową tablicę i zapisuje w niej kolejne zsumowane wartości z tablic a i b (długość nowej tablicy jest taka jak najdłuższa z nich)
int* arr_add_new(const int *a, const int *b) {
    if (a[0] > b[0]) size = a[0];
    else size = b[0];
    int* new_arr = arr_new(size);
    for (int i = 1; i <= size; i++) {
        new_arr[i] = arr_get(a, i) + arr_get(b, i); // Funkcja arr_get zwraca 0, jeśli index nie istnieje
    }
    return new_arr;
}
// int* arr_add_new(const int *a, const int *b) {
//     int size = max(a[0], b[0]);
//     int lowest = (a[0] < b[0] ? a : b);
//     int highest = (a[0] > b[0] ? a : b);
//     int* new_arr = arr_new(size);
//     for (int i = 1; i <= min(a[0], b[0]); i++) {
//         new_arr[i] = a[i] + b[i];
//     }
//     for (int i = 1; i <= min(a[0], b[0]); i++) {
//         // 
//     }
// }