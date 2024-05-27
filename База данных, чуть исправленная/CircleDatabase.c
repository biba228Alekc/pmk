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
    printf("������� ���� ����� ��� ��������: ");
    scanf("%19s", color);
    for (size_t i = 0; i < database->size; ++i) {
        if (strcmp(get_circle_color(database->circles[i]), color) == 0) {
            free_circle(database->circles[i]);
            // �������� ���������� �����
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // ��������� ������� ������ �����, ��� ��� �� ��� ����� ��������� ��������� ����
        }
    }
}

// �������� ����� �� �������
void delete_circle_by_radius(CircleDatabase* database) {
    float radius;
    printf("������� ������ ����� ��� ��������: ");
    scanf("%f", &radius);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_radius(database->circles[i]) == radius) {
            free_circle(database->circles[i]);
            // �������� ���������� �����
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // ��������� ������� ������ �����, ��� ��� �� ��� ����� ��������� ��������� ����
        }
    }
}

// �������� ����� �� ���������� x
void delete_circle_by_x(CircleDatabase* database) {
    float x;
    printf("������� ���������� x ����� ��� ��������: ");
    scanf("%f", &x);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_x(database->circles[i]) == x) {
            free_circle(database->circles[i]);
            // �������� ���������� �����
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // ��������� ������� ������ �����, ��� ��� �� ��� ����� ��������� ��������� ����
        }
    }
}

// �������� ����� �� ���������� y
void delete_circle_by_y(CircleDatabase* database) {
    float y;
    printf("������� ���������� y ����� ��� ��������: ");
    scanf("%f", &y);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_y(database->circles[i]) == y) {
            free_circle(database->circles[i]);
            // �������� ���������� �����
            for (size_t j = i; j < database->size - 1; ++j) {
                database->circles[j] = database->circles[j + 1];
            }
            --database->size;
            --i; // ��������� ������� ������ �����, ��� ��� �� ��� ����� ��������� ��������� ����
        }
    }
}

// ����� ����� �� ������, ��������� �� �������
void find_circle_from_console(const CircleDatabase* database) {
    char color[20];
    printf("������� ���� ����� ��� ������: ");
    scanf("%19s", color);
    for (size_t i = 0; i < database->size; ++i) {
        if (strcmp(get_circle_color(database->circles[i]), color) == 0) {
            print_circle_info(database->circles[i]);
            return;
        }
    }
    printf("���� � ������ %s �� ������\n", color);
}

// ����� ����� �� �������
void find_circle_by_radius(const CircleDatabase* database) {
    float radius;
    printf("������� ������ ����� ��� ������: ");
    scanf("%f", &radius);
    for (size_t i = 0; i < database->size; ++i) {
        if (get_circle_radius(database->circles[i]) == radius) {
            print_circle_info(database->circles[i]);
            return;
        }
    }
    printf("���� � �������� %.2f �� ������\n", radius);
}

// ���������� ������ �� ���������� ����
void sort_circles_by_field(CircleDatabase* database) {
    int field;
    printf("�������� ���� ��� ���������� (1 - ������, 2 - ����): ");
    scanf("%d", &field);
    for (size_t i = 0; i < database->size - 1; ++i) {
        for (size_t j = i + 1; j < database->size; ++j) {
            if ((field == 1 && get_circle_radius(database->circles[i]) > get_circle_radius(database->circles[j])) ||
                (field == 2 && strcmp(get_circle_color(database->circles[i]), get_circle_color(database->circles[j])) > 0)) {
                // ������ �������
                Circle* temp = database->circles[i];
                database->circles[i] = database->circles[j];
                database->circles[j] = temp;
            }
        }
    }
}

// ���������� ������ �� ���������� x (������� �����)
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

// ���������� ������ �� ���������� y (������� �����)
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

// ����� ���� ������ �� �������
void print_circle_database(const CircleDatabase* database) {
    for (size_t i = 0; i < database->size; ++i) {
        printf("���� %zu:\n", i);
        print_circle_info(database->circles[i]);
    }
}
