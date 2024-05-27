// main.c

#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "CircleDatabase.h"
#include "HelperFunctions.h"
#include <locale.h>

#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "CircleDatabase.h"
#include "HelperFunctions.h"

int main() {
    setlocale(LC_ALL, "Russian");
    CircleDatabase* database = create_circle_database(10); // ��������� ������� 10
    int choice;

    do {
        printf("\n=== ���������� ����� ������ ������ ===\n");
        printf("1. �������� ����\n");
        printf("2. �������� ����\n");
        printf("3. ������� ����\n");
        printf("4. ����� ���� �� �����\n");
        printf("5. ����� ���� �� �������\n");
        printf("6. ����������� �����\n");
        printf("7. ������� ���� ������\n");
        printf("0. �����\n");
        printf("������� ��� �����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            add_circle_from_console(database);
            break;
        case 2:
            update_circle_from_console(database);
            break;
        case 3:
            delete_circle_from_console(database);
            break;
        case 4:
            find_circle_from_console(database);
            break;
        case 5:
            find_circle_by_radius(database);
            break;
        case 6:
            sort_circles_by_field(database);
            break;
        case 7:
            print_circle_database(database);
            break;
        case 0:
            printf("�����...\n");
            break;
        default:
            printf("�������� �����\n");
            break;
        }

        clear_input_buffer(); // ������� ����� ����� ����� ������ ��������

    } while (choice != 0);

    free_circle_database(database);

    return 0;
}
