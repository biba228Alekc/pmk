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
    CircleDatabase* database = create_circle_database(10); // Начальная емкость 10
    int choice;

    do {
        printf("\n=== Управление базой данных кругов ===\n");
        printf("1. Добавить круг\n");
        printf("2. Изменить круг\n");
        printf("3. Удалить круг\n");
        printf("4. Найти круг по цвету\n");
        printf("5. Найти круг по радиусу\n");
        printf("6. Сортировать круги\n");
        printf("7. Вывести базу данных\n");
        printf("0. Выход\n");
        printf("Введите ваш выбор: ");
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
            printf("Выход...\n");
            break;
        default:
            printf("Неверный выбор\n");
            break;
        }

        clear_input_buffer(); // Очищаем буфер ввода после каждой операции

    } while (choice != 0);

    free_circle_database(database);

    return 0;
}
