#include "CircleDatabase.h"
#include "Circle.h"
#include <stdio.h>

#pragma warning(disable : 4996)


// Определение закрытой структуры базы данных кругов
struct CircleDatabase {
    Circle** circles;  // Указатель на массив указателей на круги
    size_t size;      // Текущее количество кругов
    size_t capacity;  // Емкость массива кругов
};

// Создание новой базы данных кругов
CircleDatabase* create_circle_database(size_t capacity) {
    CircleDatabase* database = malloc(sizeof(CircleDatabase));
    if (database == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    database->circles = malloc(capacity * sizeof(Circle*));
    if (database->circles == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    database->size = 0;
    database->capacity = capacity;
    return database;
}

// Освобождение памяти, выделенной для базы данных кругов
void free_circle_database(CircleDatabase* database) {
    for (size_t i = 0; i < database->size; ++i) {
        free_circle(database->circles[i]);
    }
    free(database->circles);
    free(database);
}

// Добавление круга в базу данных из консоли
void add_circle_from_console(CircleDatabase* database) {
    float radius, x, y;
    char color[20];
    printf("Введите радиус: ");
    scanf("%f", &radius);
    printf("Введите координату x: ");
    scanf("%f", &x);
    printf("Введите координату y: ");
    scanf("%f", &y);
    printf("Введите цвет: ");
    scanf("%19s", color);
    if (database->size >= database->capacity) {
        // Увеличиваем емкость массива кругов
        database->capacity += 10; // Например, увеличим емкость на 10 элементов
        database->circles = realloc(database->circles, database->capacity * sizeof(Circle*));
        if (database->circles == NULL) {
            fprintf(stderr, "Ошибка перевыделения памяти\n");
            exit(EXIT_FAILURE);
        }
    }
    Circle* new_circle = create_circle(radius, x, y, color);
    database->circles[database->size++] = new_circle;
}

// Изменение данных о круге через консоль
void update_circle_from_console(CircleDatabase* database) {
    int index;
    printf("Введите индекс круга для изменения: ");
    scanf("%d", &index);
    if (index < 0 || index >= database->size) {
        printf("Неверный индекс\n");
        return;
    }
    float radius, x, y;
    char color[20];
    printf("Введите новый радиус: ");
    scanf("%f", &radius);
    printf("Введите новую координату x: ");
    scanf("%f", &x);
    printf("Введите новую координату y: ");
    scanf("%f", &y);
    printf("Введите новый цвет: ");
    scanf("%19s", color);
    update_circle(database->circles[index], radius, x, y, color);
}

// Удаление круга или кругов по данным, введенным из консоли
void delete_circle_from_console(CircleDatabase* database) {
    char color[20];
    printf("Введите цвет круга(ов) для удаления: ");
    scanf("%19s", color);
    size_t i = 0;
    while (i < database->size) {
        if (strcmp(get_circle_color(database->circles[i]), color) == 0) {
            free_circle(database->circles[i]);
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
        }
        else {
            ++i;
        }
    }
}

// Поиск круга по данным, введенным из консоли с использованием бинарного поиска
void find_circle_from_console(const CircleDatabase* database) {
    char color[20];
    printf("Введите цвет круга для поиска: ");
    scanf("%19s", color);

    // Бинарный поиск по цвету
    int left = 0, right = database->size - 1;
    int found = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(get_circle_color(database->circles[mid]), color);
        if (cmp == 0) {
            found = 1;
            print_circle_info(database->circles[mid]);
            break;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    if (!found) {
        printf("Круг с цветом %s не найден\n", color);
    }
}

// Сортировка Шелла по радиусу
void shell_sort_by_radius(CircleDatabase* database) {
    size_t n = database->size;
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            Circle* temp = database->circles[i];
            size_t j;
            for (j = i; j >= gap && get_circle_radius(database->circles[j - gap]) > get_circle_radius(temp); j -= gap) {
                database->circles[j] = database->circles[j - gap];
            }
            database->circles[j] = temp;
        }
    }
}


// Поиск круга по радиусу с использованием бинарного поиска
void find_circle_by_radius(const CircleDatabase* database) {
    float radius;
    printf("Введите радиус круга для поиска: ");
    scanf("%f", &radius);

    // Бинарный поиск по радиусу
    int left = 0, right = database->size - 1;
    int found = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (get_circle_radius(database->circles[mid]) == radius) {
            found = 1;
            print_circle_info(database->circles[mid]);
            break;
        }
        else if (get_circle_radius(database->circles[mid]) < radius) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    if (!found) {
        printf("Круг с радиусом %.2f не найден\n", radius);
    }
}

// Сортировка Шелла по цвету
void shell_sort_by_color(CircleDatabase* database) {
    size_t n = database->size;
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            Circle* temp = database->circles[i];
            size_t j;
            for (j = i; j >= gap && strcmp(get_circle_color(database->circles[j - gap]), get_circle_color(temp)) > 0; j -= gap) {
                database->circles[j] = database->circles[j - gap];
            }
            database->circles[j] = temp;
        }
    }
}

// Сортировка данных по выбранному полю
void sort_circles_by_field(CircleDatabase* database) {
    int choice;
    printf("Выберите поле для сортировки:\n");
    printf("1. Радиус\n");
    printf("2. Цвет\n");
    printf("Введите ваш выбор: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        shell_sort_by_radius(database);
        break;
    case 2:
        shell_sort_by_color(database);
        break;
    default:
        printf("Неверный выбор\n");
        break;
    }
}

// Вывод базы данных на консоль
void print_circle_database(const CircleDatabase* database) {
    printf("База данных кругов:\n");
    for (size_t i = 0; i < database->size; ++i) {
        printf("Круг %zu:\n", i + 1);
        print_circle_info(database->circles[i]);
        printf("\n");
    }
}
