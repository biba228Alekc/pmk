// Circle.c

#include "Circle.h"
#pragma warning(disable : 4996)
#define M_PI 3.14159265358979323846



// Определение закрытой структуры круга
struct Circle {
    float radius;
    float x;          // Координата центра x
    float y;          // Координата центра y
    char color[20];   // Цвет круга
};

// Создание нового круга
Circle* create_circle(float radius, float x, float y, const char* color) {
    Circle* circle = malloc(sizeof(Circle));
    if (circle == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    strncpy(circle->color, color, sizeof(circle->color));
    circle->color[sizeof(circle->color) - 1] = '\0'; // Убеждаемся, что строка завершена нулевым символом
    return circle;
}

// Вычисление площади круга
float calculate_circle_area(const Circle* circle) {
    return M_PI * circle->radius * circle->radius;
}

// Вычисление периметра круга
float calculate_circle_perimeter(const Circle* circle) {
    return 2 * M_PI * circle->radius;
}

// Изменение параметров круга
void update_circle(Circle* circle, float radius, float x, float y, const char* color) {
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    strncpy(circle->color, color, sizeof(circle->color));
    circle->color[sizeof(circle->color) - 1] = '\0'; // Убеждаемся, что строка завершена нулевым символом
}

// Вывод информации о круге
void print_circle_info(const Circle* circle) {
    printf("Информация о круге:\n");
    printf("Радиус: %.2f\n", circle->radius);
    printf("Координаты центра: (%.2f, %.2f)\n", circle->x, circle->y);
    printf("Цвет: %s\n", circle->color);
    printf("Площадь: %.2f\n", calculate_circle_area(circle));
    printf("Периметр: %.2f\n", calculate_circle_perimeter(circle));
}

// Освобождение памяти, выделенной для круга
void free_circle(Circle* circle) {
    free(circle);
}

// Получение радиуса круга
float get_circle_radius(const Circle* circle) {
    return circle->radius;
}

// Получение цвета круга
const char* get_circle_color(const Circle* circle) {
    return circle->color;
}
