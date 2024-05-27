#ifndef CIRCLE_DATABASE_H
#define CIRCLE_DATABASE_H

#include "Circle.h"

// �������� ��������� ���� ������ ������
typedef struct CircleDatabase CircleDatabase;

// �������� ����� ���� ������ ������
CircleDatabase* create_circle_database(size_t capacity);

// ������������ ������, ���������� ��� ���� ������ ������
void free_circle_database(CircleDatabase* database);

// ���������� ����� � ���� ������ �� �������
void add_circle_from_console(CircleDatabase* database);

// ��������� ������ � ����� ����� �������
void update_circle_from_console(CircleDatabase* database);

// �������� ����� ��� ������ �� ������, ��������� �� �������
void delete_circle_from_console(CircleDatabase* database);

// �������� ����� �� �������
void delete_circle_by_radius(CircleDatabase* database);

// �������� ����� �� ���������� x
void delete_circle_by_x(CircleDatabase* database);

// �������� ����� �� ���������� y
void delete_circle_by_y(CircleDatabase* database);

// ����� ����� �� ������, ��������� �� �������
void find_circle_from_console(const CircleDatabase* database);

// ����� ����� �� �������
void find_circle_by_radius(const CircleDatabase* database);

// ���������� ������ �� ���������� ����
void sort_circles_by_field(CircleDatabase* database);

// ���������� ������ �� ���������� x
void shell_sort_by_x(CircleDatabase* database);

// ���������� ������ �� ���������� y
void shell_sort_by_y(CircleDatabase* database);

// ����� ���� ������ �� �������
void print_circle_database(const CircleDatabase* database);

#endif /* CIRCLE_DATABASE_H */

