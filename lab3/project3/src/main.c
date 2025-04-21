#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "menu.h"
#include "utils.h"

int main() {
  const char* db_path = "data/patients.db";

  if (!init_database(db_path)) {
    fprintf(stderr, "Не удалось инициализировать базу данных.\n");
    return 1;
  }

  printf("База данных пациентов успешно инициализирована.\n");

  const char* check_empty_sql = "SELECT COUNT(*) FROM patient_info";
  sqlite3* db = NULL;
  sqlite3_open(db_path, &db);

  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, check_empty_sql, -1, &stmt, NULL);

  if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (count == 0) {
      printf("База данных пуста. Добавление тестовых данных...\n");

      const char* init_data_sql =
          "BEGIN TRANSACTION;"
          "INSERT INTO patient_info VALUES(1, 'Иванов', 'Иван', 'Иванович', "
          "'М', 'Русский', 170, 70, 1990, 5, 20, '+79001234567', '123456, "
          "Россия, Московская обл, г. Москва, ул. Ленина, д.10, кв.5', "
          "'MC123', 'ОРВИ', 'A+', 18);"
          "INSERT INTO patient_info VALUES(2, 'Петрова', 'Анна', 'Сергеевна', "
          "'Ж', 'Русская', 165, 55, 1985, 10, 3, '+79007654321', '123456, "
          "Россия, Московская обл, г. Москва, ул. Пушкина, д.15, кв.10', "
          "'MC124', 'Грипп', 'B-', 17);"
          "INSERT INTO patient_info "
          "VALUES(3,'Сидоров','Алексей','Петрович','М','Русский',180,82,1978,3,"
          "12,'+79005551234','620000, Россия, Свердловская обл, г. "
          "Екатеринбург, ул. Мира, д.22, кв.18','MC125','Диабет','O+',17);"
          "INSERT INTO patient_info "
          "VALUES(4,'Кузнецова','Мария','Алексеевна','Ж','Русская',160,50,1995,"
          "6,9,'+79002223344','400000, Россия, Волгоградская обл, г. "
          "Волгоград, ул. Гагарина, д.7, кв.3','MC126','Астма','AB-',16);"
          "INSERT INTO patient_info "
          "VALUES(5,'Фёдоров','Дмитрий','Ильич','М','Русский',172,75,1992,11,"
          "27,'+79003334455','350000, Россия, Краснодарский край, г. "
          "Краснодар, ул. Кирова, д.5, кв.1','MC127','ОРВИ','B+',18);"
          "INSERT INTO patient_info "
          "VALUES(6,'Андреева','Наталья','Викторовна','Ж','Русская',158,48,"
          "1988,9,17,'+79006667788','630000, Россия, Новосибирская обл, г. "
          "Новосибирск, ул. Советская, д.12, "
          "кв.14','MC128','Гипертония','A-',19);"
          "INSERT INTO patient_info "
          "VALUES(7,'Зайцев','Олег','Романович','М','Русский',190,90,1980,12,5,"
          "'+79009998877','660000, Россия, Красноярский край, г. Красноярск, "
          "ул. Лесная, д.3, кв.2','MC129','Пневмония','O-',17);"
          "INSERT INTO patient_info "
          "VALUES(8,'Морозова','Екатерина','Андреевна','Ж','Русская',168,60,"
          "1993,7,21,'+79004445566','119019, Россия, г. Москва, ул. Арбат, "
          "д.1, кв.6','MC130','Мигрень','A+',18);"
          "COMMIT;";

      execute_query(init_data_sql);
    }
  } else {
    sqlite3_finalize(stmt);
    sqlite3_close(db);
  }

  show_main_menu();

  close_database();

  return 0;
}