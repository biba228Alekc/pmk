#ifndef CIRCLE_H
#define CIRCLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// �������� ��������� �����
typedef struct Circle Circle;

// �������� ������ �����
Circle* create_circle(float radius, float x, float y, const char* color);

// ���������� ������� �����
float calculate_circle_area(const Circle* circle);

// ���������� ��������� �����
float calculate_circle_perimeter(const Circle* circle);

// ��������� ���������� �����
void update_circle(Circle* circle, float radius, float x, float y, const char* color);

// ����� ���������� � �����
void print_circle_info(const Circle* circle);

// ������������ ������, ���������� ��� �����
void free_circle(Circle* circle);

// ��������� ������� �����
float get_circle_radius(const Circle* circle);

// ��������� ����� �����
const char* get_circle_color(const Circle* circle);

// ���������� ���������� �� ������ ����� �� ������ ���������
float calculate_distance_from_origin(const Circle* circle);

// ��������� ���������� x
float get_circle_x(const Circle* circle);

// ��������� ���������� y
float get_circle_y(const Circle* circle);

#endif /* CIRCLE_H */
