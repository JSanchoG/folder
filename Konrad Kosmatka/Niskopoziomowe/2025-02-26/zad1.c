#include <stdio.h>

int main() {
    int a = 20;
    int b = 20;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            int w = i * j;
            printf("%*d", 4, w);
        }
        printf("\n");
    }
}