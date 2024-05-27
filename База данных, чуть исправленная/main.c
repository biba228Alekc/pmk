//main.c


#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "CircleDatabase.h"
#include "HelperFunctions.h"
#include <locale.h>


void print_menu() {
    printf("\n����:\n");
    printf("1. �������� ����\n");
    printf("2. �������� ����\n");
    printf("3. ������� ����(�����) �� �����\n");
    printf("4. ������� ����(�����) �� �������\n");
    printf("5. ������� ����(�����) �� ���������� x\n");
    printf("6. ������� ����(�����) �� ���������� y\n");
    printf("7. ����� ���� �� �����\n");
    printf("8. ����� ���� �� �������\n");
    printf("9. ����������� ����� �� ������� ��� �����\n");
    printf("10. ����������� ����� �� ���������� x\n");
    printf("11. ����������� ����� �� ���������� y\n");
    printf("12. ������� ��� �����\n");
    printf("0. �����\n");
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    CircleDatabase* database = create_circle_database(10);
    int choice;
    do {
        print_menu();
        printf("�������� �����: ");
        scanf_s("%d", &choice);
        clear_input_buffer();
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
            delete_circle_by_radius(database);
            break;
        case 5:
            delete_circle_by_x(database);
            break;
        case 6:
            delete_circle_by_y(database);
            break;
        case 7:
            find_circle_from_console(database);
            break;
        case 8:
            find_circle_by_radius(database);
            break;
        case 9:
            sort_circles_by_field(database);
            break;
        case 10:
            shell_sort_by_x(database);
            break;
        case 11:
            shell_sort_by_y(database);
            break;
        case 12:
            print_circle_database(database);
            break;
        case 0:
            printf("����� �� ���������\n");
            break;
        default:
            printf("�������� �����. ���������� �����.\n");
        }
    } while (choice != 0);

    free_circle_database(database);
    return 0;
}


