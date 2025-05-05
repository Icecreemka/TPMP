#include "menu.h"
#include "database.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_main_menu() {
    int choice = 0;
    
    while (1) {
        clear_screen();
        printf("\n===== СИСТЕМА УПРАВЛЕНИЯ БАЗОЙ ДАННЫХ ПАЦИЕНТОВ =====\n");
        printf("1. Поиск и просмотр данных\n");
        printf("2. Добавление данных\n");
        printf("3. Удаление данных\n");
        printf("4. Обновление данных\n");
        printf("5. Создать отчет\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            wait_for_key();
            continue;
        }
        
        switch (choice) {
            case 1:
                show_select_menu();
                break;
            case 2:
                show_insert_menu();
                break;
            case 3:
                handle_delete();
                break;
            case 4:
                handle_update();
                break;
            case 5:
                create_patient_report("data/patient_report.txt");
                wait_for_key();
                break;
            case 0:
                printf("Выход из программы...\n");
                return;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
                wait_for_key();
        }
    }
}

void show_select_menu() {
    int choice = 0;
    
    while (1) {
        printf("\n===== ПОИСК И ПРОСМОТР ДАННЫХ =====\n");
        printf("1. Поиск пациента по ID\n");
        printf("2. Поиск пациентов по фамилии\n");
        printf("3. Поиск пациентов по отделению\n");
        printf("0. Вернуться в главное меню\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            wait_for_key();
            continue;
        }
        
        switch (choice) {
            case 1: {
                int id;
                printf("Введите ID пациента: ");
                scanf("%d", &id);
                
                Patient patient;
                if (select_patient_by_id(id, &patient)) {
                    print_patient(&patient);
                } else {
                    printf("Пациент с ID %d не найден.\n", id);
                }
                wait_for_key();
                break;
            }
            case 2: {
                char surname[50];
                printf("Введите фрагмент фамилии: ");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                read_line(surname, sizeof(surname));
                
                select_patients_by_surname(surname);
                wait_for_key();
                break;
            }
            case 3: {
                int department;
                printf("Введите номер отделения: ");
                scanf("%d", &department);
                
                select_patients_by_department(department);
                wait_for_key();
                break;
            }
            case 0:
                return;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
                wait_for_key();
        }
    }
}

void show_insert_menu() {
    int choice = 0;
    
    while (1) {
        clear_screen();
        printf("\n===== ДОБАВЛЕНИЕ ДАННЫХ =====\n");
        printf("1. Добавить одного пациента (режим autocommit)\n");
        printf("2. Добавить нескольких пациентов (транзакция)\n");
        printf("0. Вернуться в главное меню\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Пожалуйста, введите число.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            wait_for_key();
            continue;
        }
        
        switch (choice) {
            case 1: {
                Patient patient;
                memset(&patient, 0, sizeof(Patient));
                fill_patient_from_input(&patient);
                
                if (insert_patient_autocommit(&patient)) {
                    printf("Пациент успешно добавлен (режим autocommit).\n");
                } else {
                    printf("Ошибка при добавлении пациента.\n");
                }
                wait_for_key();
                break;
            }
            case 2: {
                int count;
                printf("Сколько пациентов вы хотите добавить? ");
                scanf("%d", &count);
                
                if (count <= 0 || count > 10) {
                    printf("Пожалуйста, введите число от 1 до 10.\n");
                    wait_for_key();
                    break;
                }
                
                Patient *patients = (Patient*) malloc(count * sizeof(Patient));
                if (!patients) {
                    printf("Ошибка выделения памяти.\n");
                    wait_for_key();
                    break;
                }
                
                for (int i = 0; i < count; i++) {
                    printf("\n=== Пациент %d из %d ===\n", i+1, count);
                    memset(&patients[i], 0, sizeof(Patient));
                    fill_patient_from_input(&patients[i]);
                }
                
                if (insert_patients_transaction(patients, count)) {
                    printf("Все пациенты успешно добавлены (транзакция).\n");
                } else {
                    printf("Ошибка при добавлении пациентов.\n");
                }
                
                free(patients);
                wait_for_key();
                break;
            }
            case 0:
                return;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
                wait_for_key();
        }
    }
}

void handle_delete() {
    clear_screen();
    printf("\n===== УДАЛЕНИЕ ДАННЫХ =====\n");
    
    int id;
    printf("Введите ID пациента для удаления: ");
    
    if (scanf("%d", &id) != 1) {
        printf("Ошибка ввода. Пожалуйста, введите число.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        wait_for_key();
        return;
    }
    
    Patient patient;
    if (!select_patient_by_id(id, &patient)) {
        printf("Пациент с ID %d не найден.\n", id);
        wait_for_key();
        return;
    }
    
    print_patient(&patient);
    
    char confirm;
    printf("Вы уверены, что хотите удалить этого пациента? (y/n): ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        if (delete_patient_by_id(id)) {
            printf("Пациент успешно удален.\n");
        } else {
            printf("Ошибка при удалении пациента.\n");
        }
    } else {
        printf("Удаление отменено.\n");
    }
    
    wait_for_key();
}

void handle_update() {
    clear_screen();
    printf("\n===== ОБНОВЛЕНИЕ ДАННЫХ =====\n");
    
    int id;
    printf("Введите ID пациента для обновления: ");
    
    if (scanf("%d", &id) != 1) {
        printf("Ошибка ввода. Пожалуйста, введите число.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        wait_for_key();
        return;
    }
    
    Patient patient;
    if (!select_patient_by_id(id, &patient)) {
        printf("Пациент с ID %d не найден.\n", id);
        wait_for_key();
        return;
    }
    
    printf("\nТекущие данные пациента:\n");
    print_patient(&patient);
    
    printf("\nВведите новые данные (оставьте поле пустым, чтобы сохранить текущее значение):\n");
    
    char input[200];
    int temp_int;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Фамилия [%s]: ", patient.surname);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.surname, input, sizeof(patient.surname) - 1);
    
    printf("Имя [%s]: ", patient.name);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.name, input, sizeof(patient.name) - 1);
    
    printf("Отчество [%s]: ", patient.patronymic);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.patronymic, input, sizeof(patient.patronymic) - 1);
    
    printf("Пол [%s]: ", patient.gender);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.gender, input, sizeof(patient.gender) - 1);
    
    printf("Национальность [%s]: ", patient.nationality);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.nationality, input, sizeof(patient.nationality) - 1);
    
    printf("Рост (см) [%d]: ", patient.height);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.height = temp_int;
    
    printf("Вес (кг) [%d]: ", patient.weight);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.weight = temp_int;
    
    printf("Год рождения [%d]: ", patient.birth_year);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.birth_year = temp_int;
    
    printf("Месяц рождения [%d]: ", patient.birth_month);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.birth_month = temp_int;
    
    printf("День рождения [%d]: ", patient.birth_day);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.birth_day = temp_int;
    
    printf("Телефон [%s]: ", patient.phone);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.phone, input, sizeof(patient.phone) - 1);
    
    printf("Адрес [%s]: ", patient.address);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.address, input, sizeof(patient.address) - 1);
    
    printf("Номер мед. карты [%s]: ", patient.med_card_number);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.med_card_number, input, sizeof(patient.med_card_number) - 1);
    
    printf("Диагноз [%s]: ", patient.diagnosis);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.diagnosis, input, sizeof(patient.diagnosis) - 1);
    
    printf("Группа крови [%s]: ", patient.blood_group);
    read_line(input, sizeof(input));
    if (strlen(input) > 0) strncpy(patient.blood_group, input, sizeof(patient.blood_group) - 1);
    
    printf("Отделение [%d]: ", patient.department);
    read_line(input, sizeof(input));
    if (strlen(input) > 0 && sscanf(input, "%d", &temp_int) == 1) patient.department = temp_int;
    
    if (update_patient(&patient)) {
        printf("\nДанные пациента успешно обновлены.\n");
    } else {
        printf("\nОшибка при обновлении данных пациента.\n");
    }
    
    wait_for_key();
}