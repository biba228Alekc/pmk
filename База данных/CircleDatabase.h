#ifndef CIRCLE_DATABASE_H
#define CIRCLE_DATABASE_H

#include "Circle.h"

// Закрытая структура базы данных кругов
typedef struct CircleDatabase CircleDatabase;

// Создание новой базы данных кругов
CircleDatabase* create_circle_database(size_t capacity);

// Освобождение памяти, выделенной для базы данных кругов
void free_circle_database(CircleDatabase* database);

// Добавление круга в базу данных из консоли
void add_circle_from_console(CircleDatabase* database);

// Изменение данных о круге через консоль
void update_circle_from_console(CircleDatabase* database);

// Удаление круга или кругов по данным, введенным из консоли
void delete_circle_from_console(CircleDatabase* database);

// Поиск круга по данным, введенным из консоли
void find_circle_from_console(const CircleDatabase* database);

// Сортировка данных по выбранному полю
void sort_circles_by_field(CircleDatabase* database);

// Вывод базы данных на консоль
void print_circle_database(const CircleDatabase* database);

#endif /* CIRCLE_DATABASE_H */
