// CircleDatabase.c

#include "CircleDatabase.h"
#include "Circle.h"
#include <stdio.h>

#pragma warning(disable : 4996)


// ����������� �������� ��������� ���� ������ ������
struct CircleDatabase {
    Circle** circles;  // ��������� �� ������ ���������� �� �����
    size_t size;      // ������� ���������� ������
    size_t capacity;  // ������� ������� ������
};

// �������� ����� ���� ������ ������
CircleDatabase* create_circle_database(size_t capacity) {
    CircleDatabase* database = malloc(sizeof(CircleDatabase));
    if (database == NULL) {
        fprintf(stderr, "������ ��������� ������\n");
        exit(EXIT_FAILURE);
    }
    database->circles = malloc(capacity * sizeof(Circle*));
    if (database->circles == NULL) {
        fprintf(stderr, "������ ��������� ������\n");
        exit(EXIT_FAILURE);
    }
    database->size = 0;
    database->capacity = capacity;
    return database;
}

// ������������ ������, ���������� ��� ���� ������ ������
void free_circle_database(CircleDatabase* database) {
    for (size_t i = 0; i < database->size; ++i) {
        free_circle(database->circles[i]);
    }
    free(database->circles);
    free(database);
}

// ���������� ����� � ���� ������ �� �������
void add_circle_from_console(CircleDatabase* database) {
    float radius, x, y;
    char color[20];
    printf("������� ������: ");
    scanf("%f", &radius);
    printf("������� ���������� x: ");
    scanf("%f", &x);
    printf("������� ���������� y: ");
    scanf("%f", &y);
    printf("������� ����: ");
    scanf("%19s", color);
    if (database->size >= database->capacity) {
        // ����������� ������� ������� ������
        database->capacity += 10; // ��������, �������� ������� �� 10 ���������
        database->circles = realloc(database->circles, database->capacity * sizeof(Circle*));
        if (database->circles == NULL) {
            fprintf(stderr, "������ ������������� ������\n");
            exit(EXIT_FAILURE);
        }
    }
    Circle* new_circle = create_circle(radius, x, y, color);
    database->circles[database->size++] = new_circle;
}

// ��������� ������ � ����� ����� �������
void update_circle_from_console(CircleDatabase* database) {
    int index;
    printf("������� ������ ����� ��� ���������: ");
    scanf("%d", &index);
    if (index < 0 || index >= database->size) {
        printf("�������� ������\n");
        return;
    }
    float radius, x, y;
    char color[20];
    printf("������� ����� ������: ");
    scanf("%f", &radius);
    printf("������� ����� ���������� x: ");
    scanf("%f", &x);
    printf("������� ����� ���������� y: ");
    scanf("%f", &y);
    printf("������� ����� ����: ");
    scanf("%19s", color);
    update_circle(database->circles[index], radius, x, y, color);
}

// �������� ����� ��� ������ �� ������, ��������� �� �������
void delete_circle_from_console(CircleDatabase* database) {
    char color[20];
    printf("������� ���� �����(��) ��� ��������: ");
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

// ����� ����� �� ������, ��������� �� ������� � �������������� ��������� ������
void find_circle_from_console(const CircleDatabase* database) {
    char color[20];
    printf("������� ���� ����� ��� ������: ");
    scanf("%19s", color);

    // �������� ����� �� �����
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
        printf("���� � ������ %s �� ������\n", color);
    }
}

// ���������� ����� �� �������
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


// ����� ����� �� ������� � �������������� ��������� ������
void find_circle_by_radius(const CircleDatabase* database) {
    float radius;
    printf("������� ������ ����� ��� ������: ");
    scanf("%f", &radius);

    // �������� ����� �� �������
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
        printf("���� � �������� %.2f �� ������\n", radius);
    }
}

// ���������� ����� �� �����
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

// ���������� ������ �� ���������� ����
void sort_circles_by_field(CircleDatabase* database) {
    int choice;
    printf("�������� ���� ��� ����������:\n");
    printf("1. ������\n");
    printf("2. ����\n");
    printf("������� ��� �����: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        shell_sort_by_radius(database);
        break;
    case 2:
        shell_sort_by_color(database);
        break;
    default:
        printf("�������� �����\n");
        break;
    }
}

// ����� ���� ������ �� �������
void print_circle_database(const CircleDatabase* database) {
    printf("���� ������ ������:\n");
    for (size_t i = 0; i < database->size; ++i) {
        printf("���� %zu:\n", i + 1);
        print_circle_info(database->circles[i]);
        printf("\n");
    }
}
