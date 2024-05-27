//main.c


#include <stdio.h>
#include <stdlib.h>
#include "Circle.h"
#include "CircleDatabase.h"
#include "HelperFunctions.h"
#include <locale.h>


void print_menu() {
    printf("\nМеню:\n");
    printf("1. Добавить круг\n");
    printf("2. Изменить круг\n");
    printf("3. Удалить круг(круги) по цвету\n");
    printf("4. Удалить круг(круги) по радиусу\n");
    printf("5. Удалить круг(круги) по координате x\n");
    printf("6. Удалить круг(круги) по координате y\n");
    printf("7. Найти круг по цвету\n");
    printf("8. Найти круг по радиусу\n");
    printf("9. Сортировать круги по радиусу или цвету\n");
    printf("10. Сортировать круги по координате x\n");
    printf("11. Сортировать круги по координате y\n");
    printf("12. Вывести все круги\n");
    printf("0. Выход\n");
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    CircleDatabase* database = create_circle_database(10);
    int choice;
    do {
        print_menu();
        printf("Выберите опцию: ");
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
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    free_circle_database(database);
    return 0;
}


