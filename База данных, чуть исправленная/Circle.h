#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Закрытая структура круга
typedef struct Circle Circle;

// Создание нового круга
Circle* create_circle(float radius, float x, float y, const char* color);

// Вычисление площади круга
float calculate_circle_area(const Circle* circle);

// Вычисление периметра круга
float calculate_circle_perimeter(const Circle* circle);

// Изменение параметров круга
void update_circle(Circle* circle, float radius, float x, float y, const char* color);

// Вывод информации о круге
void print_circle_info(const Circle* circle);

// Освобождение памяти, выделенной для круга
void free_circle(Circle* circle);

// Получение радиуса круга
float get_circle_radius(const Circle* circle);

// Получение цвета круга
const char* get_circle_color(const Circle* circle);

// Вычисление расстояния от центра круга до начала координат
float calculate_distance_from_origin(const Circle* circle);

// Получение координаты x
float get_circle_x(const Circle* circle);

// Получение координаты y
float get_circle_y(const Circle* circle);

#endif /* CIRCLE_H */
