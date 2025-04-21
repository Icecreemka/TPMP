#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void wait_for_key() {
  printf("\nНажмите Enter для продолжения...");
  getchar();
}

void read_line(char* buffer, int size) {
  if (fgets(buffer, size, stdin) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    } else {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
    }
  }
}

void print_patient(Patient* patient) {
  printf("\nИнформация о пациенте (ID: %d):\n", patient->id);
  printf("------------------------------------------------\n");
  printf("ФИО: %s %s %s\n", patient->surname, patient->name,
         patient->patronymic);
  printf("Пол: %s\n", patient->gender);
  printf("Национальность: %s\n", patient->nationality);
  printf("Рост: %d см\n", patient->height);
  printf("Вес: %d кг\n", patient->weight);
  printf("Дата рождения: %02d.%02d.%04d\n", patient->birth_day,
         patient->birth_month, patient->birth_year);
  printf("Телефон: %s\n", patient->phone);
  printf("Адрес: %s\n", patient->address);
  printf("Номер мед. карты: %s\n", patient->med_card_number);
  printf("Диагноз: %s\n", patient->diagnosis);
  printf("Группа крови: %s\n", patient->blood_group);
  printf("Отделение: %d\n", patient->department);
  printf("------------------------------------------------\n");
}

void fill_patient_from_input(Patient* patient) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);

  printf("Введите данные пациента:\n");

  printf("Фамилия: ");
  read_line(patient->surname, sizeof(patient->surname));

  printf("Имя: ");
  read_line(patient->name, sizeof(patient->name));

  printf("Отчество: ");
  read_line(patient->patronymic, sizeof(patient->patronymic));

  printf("Пол (М/Ж): ");
  read_line(patient->gender, sizeof(patient->gender));

  printf("Национальность: ");
  read_line(patient->nationality, sizeof(patient->nationality));

  printf("Рост (см): ");
  scanf("%d", &patient->height);

  printf("Вес (кг): ");
  scanf("%d", &patient->weight);

  printf("Год рождения: ");
  scanf("%d", &patient->birth_year);

  printf("Месяц рождения (1-12): ");
  scanf("%d", &patient->birth_month);

  printf("День рождения (1-31): ");
  scanf("%d", &patient->birth_day);

  while ((c = getchar()) != '\n' && c != EOF);

  printf("Телефон: ");
  read_line(patient->phone, sizeof(patient->phone));

  printf("Адрес: ");
    read_line(patient->address, sizeof(patient->address));
    
    printf("Номер мед. карты: ");
    read_line(patient->med_card_number, sizeof(patient->med_card_number));
    
    printf("Диагноз: ");
    read_line(patient->diagnosis, sizeof(patient->diagnosis));
    
    printf("Группа крови (например, A+, B-, O+): ");
    read_line(patient->blood_group, sizeof(patient->blood_group));
    
    printf("Отделение (номер): ");
    scanf("%d", &patient->department);
    
    while ((c = getchar()) != '\n' && c != EOF);
}

void create_patient_report(const char* filename) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    fprintf(stderr, "Ошибка при создании файла отчета %s\n", filename);
    return;
  }

  fprintf(file, "# Отчет по пациентам\n\n");
  fprintf(file, "Дата формирования отчета: [текущая дата]\n\n");
  fprintf(file, "## Список пациентов\n\n");

  fprintf(file, "\n\n## Конец отчета\n");

  fclose(file);
  printf("Отчет успешно создан в файле %s\n", filename);
}