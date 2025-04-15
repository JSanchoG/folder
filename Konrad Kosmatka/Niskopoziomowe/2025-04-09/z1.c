#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cmdReset(bool scroll) {
    if (scroll) printf("\033c"); // cmd reset
    else printf("\x1B[2J\x1B[H"); // cmd scroll
}

struct Task {
    char *name;
    struct Task *next;
};

struct Task *head = NULL;
struct Task *tail = NULL;

struct Task* task_new(const char *name) {
    struct Task *new_task = malloc(sizeof(struct Task));
    if (!new_task) return NULL;
    
    new_task->name = strdup(name);
    if (!new_task->name) {
        free(new_task);
        return NULL;
    }
    
    new_task->next = NULL;
    return new_task;
}

void task_free(struct Task *task) {
    if (task) {
        free(task->name);
        free(task);
    }
}

void add_task(const char *name) {
    struct Task *new_task = task_new(name);
    if (!new_task) {
        fprintf(stderr, "Błąd alokacji pamięci!\n");
        return;
    }
    
    if (!head) {
        head = tail = new_task;
    } else {
        tail->next = new_task;
        tail = new_task;
    }
}

void list_tasks(bool text) {
    struct Task *current = head;
    if (!head) {
        printf("Brak zadań\n\n");
        return;
    }
    if (text) printf("Zadania:\n");
    while (current) {
        printf("- ");
        printf("%s\n", current->name);
        current = current->next;
    }
    printf("\n");
}

void remove_first_task() {
    if (!head) {
        printf("Brak zadań\n");
        return;
    }
    
    struct Task *temp = head;
    printf("Usunięto: %s\n", temp->name);
    
    head = head->next;
    if (!head) {
        tail = NULL;
    }
    
    task_free(temp);

    list_tasks(false);
}

int main() {
    char *line = NULL;
    size_t len = 0;
    size_t read;

    while (1) {
        printf("[1] Wyświetl zadania\n[2] Dodaj zadanie\n[3] Usuń pierwsze zadanie\n[4] Zakończ program");
        printf("\n\nWybierz: ");
        fflush(stdout);
        read = getline(&line, &len, stdin);
        if (read == -1) break;
        if (line[read - 1] == '\n') line[read - 1] = '\0';
        
        if (strcmp(line, "1") == 0) {
            cmdReset(true);
            list_tasks(true);
        } else if (strcmp(line, "2") == 0) {
            while (1) {
                printf("Nazwa zadania: ");
                read = getline(&line, &len, stdin);
                if (read == -1) break;
                if (line[read - 1] == '\n') line[read - 1] = '\0';
                if (*line) {
                    add_task(line);
                    cmdReset(true);
                    printf("Dodano zadanie: %s\n", line);
                    printf("\n");
                    break;
                } else {
                    printf("Brak nazwy zadania\n");
                }
            }
        } else if (strcmp(line, "3") == 0) {
            cmdReset(true);
            remove_first_task();
            printf("\n");
        } else if (strcmp(line, "4") == 0) {
            break;
        } else {
            cmdReset(true);
            printf("Nieznana komenda: %s\n", line);
            printf("\n");
        }
    }

    free(line);

    struct Task *current = head;
    while (current) {
        struct Task *temp = current;
        current = current->next;
        task_free(temp);
    }
    head = tail = NULL;

    return 0;
}

// Funkcje programu:
//     Wyświetlanie wszystkich zadań, np:
//         Wynieś śmieci
//         Zapłać rachunki
//         Naucz się na kolokwium
//         Wyśpij się
//     Dodawanie nowego zadania na koniec kolejki.
//     Wyświetlanie i usuwanie zadania z początku kolejki.