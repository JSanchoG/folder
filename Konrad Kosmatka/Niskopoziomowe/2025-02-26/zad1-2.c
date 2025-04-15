#include <stdio.h>

int main() {
    int a;
    printf("Podaj wartość a: ");
    scanf("%d", &a);
    int b;
    printf("Podaj wartość b: ");
    scanf("%d", &b);
    int padding = 0;
    int w = a * b;
    do {
        padding++;
        w = w / 10;
    } while (w != 0);
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            int wynik = i * j;
            printf("%*d ", padding, wynik);
        }
        printf("\n");
    }
}