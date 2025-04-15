#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int pn_str_len(const char *str) {
    if (str == NULL) return -1;
    int i = 0;
    while (str[i] != 0) {
        i++;
    }
    return i;
}

bool pn_str_cmp(const char *a, const char *b) {
    if (a == NULL || b == NULL) return false;
    int i = 0;
    while (a[i] != 0) {
        if (b[i] == 0) return false;
        if (a[i] != b[i]) return false;
        i++;
    }
    if (a[i] == b[i]) return true;
    return false;
}

void pn_str_capitalize(char *str) {
    if (str == NULL) return;
    if (str[0] >= 'a' && str[0] <= 'z') str[0] -= 32;
}

void pn_str_trim(char *str) {
    if (str == NULL) return -1;
    int i = pn_str_len(str) - 1;
    for (i; str[i] == ' '; i--) {
        str[i] = 0;
    }
    int j = 0;
    for (j; str[j] == ' '; j++);
    int k = j;
    for (k; str[k] != 0; k++) {
        str[k - j] = str[k];
    }
    str[k - j] = '\0';
}

void pn_str_rev(char *str) {
    if (str == NULL) return -1;
    int len = pn_str_len(str);
    for (int i = 0; i < pn_str_len(str) / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

int main() {
    //################  1  ################//
    // długość stringu
    printf("pn_str_len: ");
    printf("%d\n", pn_str_len("test"));
    /////////////////////////////////////////

    //################  2  ################//
    // porównywanie stringów
    printf("pn_str_cmp: ");
    printf("%d\n", pn_str_cmp("test", "test"));
    ////////////////////////////////////////

    //################  3  ################//
    // pierwszy znak duży
    printf("pn_str_capitalize: ");
    char testStr[] = "test";
    pn_str_capitalize(testStr);
    printf("%s\n", testStr);
    /////////////////////////////////////////

    //################  4  ################//
    // usuwa spacje z początku i końca
    printf("pn_str_trim: |");
    char testStr2[] = "  te st  ";
    pn_str_trim(testStr2);
    printf("%s", testStr2);
    printf("|\n");
    /////////////////////////////////////////

    //################  4  ################//
    // odwraca stringa
    printf("pn_str_rev: ");
    char testStr3[] = "testowy string";
    pn_str_rev(testStr3);
    printf("%s\n", testStr3);
    /////////////////////////////////////////

    return 0;
}