#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// bool pn_str_cmp(const char *a, const char *b) {
//     if (a == NULL || b == NULL) return false;
//     int i = 0;
//     while (a[i] != 0) {
//         if (b[i] == 0) return false;
//         if (a[i] != b[i]) return false;
//         i++;
//     }
//     if (a[i] == b[i]) return true;
//     return false;
// }
enum Operation {
    PLUS,
    MINUS,
    RAZY,
    PRZEZ,
    DO
};

struct Calculation {
    double a;
    double b;
    enum Operation op;
};

enum Operation parse_operation(const char* op_str) {
    if (strcmp(op_str, "plus") == 0 || strcmp(op_str, "+") == 0) return PLUS;
    if (strcmp(op_str, "minus") == 0 || strcmp(op_str, "-") == 0) return MINUS;
    if (strcmp(op_str, "razy") == 0 || strcmp(op_str, "*") == 0) return RAZY;
    if (strcmp(op_str, "przez") == 0 || strcmp(op_str, "/") == 0) return PRZEZ;
    if (strcmp(op_str, "do") == 0 || strcmp(op_str, "**") == 0) return DO;
    return PLUS;
}

double calc(struct Calculation *ca) {
    switch (ca -> op) {
        case PLUS: return ca->a + ca->b;
        case MINUS: return ca->a - ca->b;
        case RAZY: return ca->a * ca->b;
        case PRZEZ:
            if (ca->b == 0) return 0;
            return ca->a / ca->b;
        case DO: return pow(ca->a, ca->b);
        default: return 0;
    }
}

void cmdReset(bool scroll) {
    if (scroll) printf("\033c"); // cmd reset
    else printf("\x1B[2J\x1B[H"); // cmd scroll
}

int main(int argc, char *argv[]) {
    cmdReset(true);
    printf("Dostępne operacje: [+] plus, [-] minus, [*] razy, [/] przez, [**] do\nPrzykład: 4 plus 5\n\n");
    // printf("%s\n", argv[1]);
    if (argc != 2) {
        printf("[!] Prawidłowe użycie: %s", argv[0]);
        printf(" <int>\n");
        return 1;
    }
    if (!atoi(argv[1])) {
        printf("[!] Prawidłowe użycie: %s", argv[0]);
        printf(" <int>\n");
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        printf("[!] Prawidłowe użycie: %s", argv[0]);
        printf(" <int>\n");
        return 1;
    }
    double *results = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        double a, b;
        char op_str[20];
        printf("Podaj dane: ");
        if (scanf("%lf %19s %lf", &a, op_str, &b) != 3) {
            printf("Błędne dane wejściowe\n");
            return 1;
        }

        struct Calculation c = {a, b, parse_operation(op_str)};
        results[i] = calc(&c);
    }

    double sum;
    printf("\nWyniki: ");
    for (int i = 0; i < N; i++) {
        printf("%.5f ", results[i]);
        sum += results[i];
    }

    double avg = sum / N;
    printf("\nŚrednia: %.5f\n\n", avg);
    free(results);
    return 0;
}