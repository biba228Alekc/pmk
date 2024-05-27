// Circle.c

#include "Circle.h"
#pragma warning(disable : 4996)
#define M_PI 3.14159265358979323846



// ����������� �������� ��������� �����
struct Circle {
    float radius;
    float x;          // ���������� ������ x
    float y;          // ���������� ������ y
    char color[20];   // ���� �����
};

// �������� ������ �����
Circle* create_circle(float radius, float x, float y, const char* color) {
    Circle* circle = malloc(sizeof(Circle));
    if (circle == NULL) {
        fprintf(stderr, "������ ��������� ������\n");
        exit(EXIT_FAILURE);
    }
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    strncpy(circle->color, color, sizeof(circle->color));
    circle->color[sizeof(circle->color) - 1] = '\0'; // ����������, ��� ������ ��������� ������� ��������
    return circle;
}

// ���������� ������� �����
float calculate_circle_area(const Circle* circle) {
    return M_PI * circle->radius * circle->radius;
}

// ���������� ��������� �����
float calculate_circle_perimeter(const Circle* circle) {
    return 2 * M_PI * circle->radius;
}

// ��������� ���������� �����
void update_circle(Circle* circle, float radius, float x, float y, const char* color) {
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    strncpy(circle->color, color, sizeof(circle->color));
    circle->color[sizeof(circle->color) - 1] = '\0'; // ����������, ��� ������ ��������� ������� ��������
}

// ����� ���������� � �����
void print_circle_info(const Circle* circle) {
    printf("���������� � �����:\n");
    printf("������: %.2f\n", circle->radius);
    printf("���������� ������: (%.2f, %.2f)\n", circle->x, circle->y);
    printf("����: %s\n", circle->color);
    printf("�������: %.2f\n", calculate_circle_area(circle));
    printf("��������: %.2f\n", calculate_circle_perimeter(circle));
}

// ������������ ������, ���������� ��� �����
void free_circle(Circle* circle) {
    free(circle);
}

// ��������� ������� �����
float get_circle_radius(const Circle* circle) {
    return circle->radius;
}

// ��������� ����� �����
const char* get_circle_color(const Circle* circle) {
    return circle->color;
}
