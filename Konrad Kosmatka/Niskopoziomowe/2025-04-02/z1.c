#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

enum Shape {
    SHAPE_CIRCLE,
    SHAPE_SQUARE,
    SHAPE_INVALID
};

enum Oper {
    OPER_FROM_LENGTH,
    OPER_FROM_AREA,
    OPER_FROM_PERIMETER,
    OPER_INVALID
};

enum Shape parse_shape(const char *shape) {
    if (strcmp(shape, "circle") == 0) return SHAPE_CIRCLE;
    if (strcmp(shape, "square") == 0) return SHAPE_SQUARE;
    return SHAPE_INVALID;
}

enum Oper parse_operation(const char *operation) {
    if (strcmp(operation, "length") == 0) return OPER_FROM_LENGTH;
    if (strcmp(operation, "area") == 0) return OPER_FROM_AREA;
    if (strcmp(operation, "perimeter") == 0) return OPER_FROM_PERIMETER;
    return OPER_INVALID;
}

struct Result {
    double length;
    double area;
    double perimeter;
};

void calculate(struct Result *result, enum Shape shape, enum Oper operation, double value) {
    if (shape == SHAPE_CIRCLE) {
        if (operation == OPER_FROM_LENGTH) {
            result -> length = value;
            result -> area = M_PI * value * value;
            result -> perimeter = 2 * M_PI * value;
        } else if (operation == OPER_FROM_AREA) {
            result -> length = sqrt(value / M_PI);
            result -> area = value;
            result -> perimeter = 2 * M_PI * result -> length;
        } else if (operation == OPER_FROM_PERIMETER) {
            result -> length = value / (2 * M_PI);
            result -> area = M_PI * result -> length * result -> length;
            result -> perimeter = value;
        }
    } else if (shape == SHAPE_SQUARE) {
        if (operation == OPER_FROM_LENGTH) {
            result -> length = value;
            result -> area = value * value;
            result -> perimeter = 4 * value;
        } else if (operation == OPER_FROM_AREA) {
            result -> length = sqrt(value);
            result -> area = value;
            result -> perimeter = 4 * result -> length;
        } else if (operation == OPER_FROM_PERIMETER) {
            result -> length = value / 4;
            result -> area = result -> length * result -> length;
            result -> perimeter = value;
        }
    }
}

void print(const struct Result *result) {
    printf("Length: %.3f\n", result -> length);
    printf("Area: %.3f\n", result -> area);
    printf("Perimeter: %.3f\n", result -> perimeter);
}

int main(int argc, char *argv[]) {
    printf("\n");

    if (argc != 4) return printf("[!] Invalid number of arguments!\n\n");

    enum Shape shape = parse_shape(argv[1]);
    if (shape == SHAPE_INVALID) return printf("[!] Invalid input shape!\n\n");

    enum Oper operation = parse_operation(argv[2]);
    if (operation == OPER_INVALID) return printf("[!] Invalid input type!\n\n");

    double value = atof(argv[3]);
    if (value <= 0) return printf("[!] Invalid input value!\n\n");

    struct Result result;
    calculate(&result, shape, operation, value);
    print(&result);

    printf("\n");

    return 0;
}