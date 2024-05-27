// CircleDatabase.c

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
    printf("Введите цвет круга для удаления: ");
    scanf("%19s", color);
    for (size_t i = 0; i < database->size; ++i) {
        if (strcmp(get_circle_color(database->circles[i]), color) == 0) {
            free_circle(database->circles[i]);
            // Сдвигаем оставшиеся круги
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // Проверяем текущий индекс снова, так как на его место сдвинулся следующий круг
        }
    }
}

// Удаление круга по радиусу
void delete_circle_by_radius(CircleDatabase* database) {
    float radius;
    printf("Введите радиус круга для удаления: ");
    scanf("%f", &radius);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_radius(database->circles[i]) == radius) {
            free_circle(database->circles[i]);
            // Сдвигаем оставшиеся круги
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // Проверяем текущий индекс снова, так как на его место сдвинулся следующий круг
        }
    }
}

// Удаление круга по координате x
void delete_circle_by_x(CircleDatabase* database) {
    float x;
    printf("Введите координату x круга для удаления: ");
    scanf("%f", &x);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_x(database->circles[i]) == x) {
            free_circle(database->circles[i]);
            // Сдвигаем оставшиеся круги
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // Проверяем текущий индекс снова, так как на его место сдвинулся следующий круг
        }
    }
}

// Удаление круга по координате y
void delete_circle_by_y(CircleDatabase* database) {
    float y;
    printf("Введите координату y круга для удаления: ");
    scanf("%f", &y);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_y(database->circles[i]) == y) {
            free_circle(database->circles[i]);
            // Сдвигаем оставшиеся круги
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // Проверяем текущий индекс снова, так как на его место сдвинулся следующий круг
        }
    }
}

// Поиск круга по данным, введенным из консоли
void find_circle_from_console(const CircleDatabase* database) {
    char color[20];
    printf("Введите цвет круга для поиска: ");
    scanf("%19s", color);
    for (size_t i = 0; i < database->size; ++i) {
        if (strcmp(get_circle_color(database->circles[i]), color) == 0) {
            print_circle_info(database->circles[i]);
            return;
        }
    }
    printf("Круг с цветом %s не найден\n", color);
}

// Поиск круга по радиусу
void find_circle_by_radius(const CircleDatabase* database) {
    float radius;
    printf("Введите радиус круга для поиска: ");
    scanf("%f", &radius);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_radius(database->circles[i]) == radius) {
            print_circle_info(database->circles[i]);
            return;
        }
    }
    printf("Круг с радиусом %.2f не найден\n", radius);
}

// Сортировка данных по выбранному полю
void sort_circles_by_field(CircleDatabase* database) {
    int field;
    printf("Выберите поле для сортировки (1 - радиус, 2 - цвет): ");
    scanf("%d", &field);
    for (size_t i = 0; i < database->size - 1; ++i) {
        for (size_t j = i + 1; j < database->size; ++j) {
            if ((field == 1 && get_circle_radius(database->circles[i]) > get_circle_radius(database->circles[j])) ||
                (field == 2 && strcmp(get_circle_color(database->circles[i]), get_circle_color(database->circles[j])) > 0)) {
                // Меняем местами
                Circle* temp = database->circles[i];
                database->circles[i] = database->circles[j];
                database->circles[j] = temp;
            }
        }
    }
}

// Сортировка кругов по координате x (методом Шелла)
void shell_sort_by_x(CircleDatabase* database) {
    size_t n = database->size;
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            Circle* temp = database->circles[i];
            size_t j;
            for (j = i; j >= gap && get_circle_x(database->circles[j - gap]) > get_circle_x(temp); j -= gap) {
                database->circles[j] = database->circles[j - gap];
            }
            database->circles[j] = temp;
        }
    }
}

// Сортировка кругов по координате y (методом Шелла)
void shell_sort_by_y(CircleDatabase* database) {
    size_t n = database->size;
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            Circle* temp = database->circles[i];
            size_t j;
            for (j = i; j >= gap && get_circle_y(database->circles[j - gap]) > get_circle_y(temp); j -= gap) {
                database->circles[j] = database->circles[j - gap];
            }
            database->circles[j] = temp;
        }
    }
}

// Вывод базы данных на консоль
void print_circle_database(const CircleDatabase* database) {
    for (size_t i = 0; i < database->size; ++i) {
        printf("Круг %zu:\n", i);
        print_circle_info(database->circles[i]);
    }
}
