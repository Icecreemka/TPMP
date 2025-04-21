#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sqlite3 *db = NULL;

static void print_sqlite_error(const char *msg) {
  fprintf(stderr, "%s: %s\n", msg, sqlite3_errmsg(db));
}

int init_database(const char *db_path) {
  int rc = sqlite3_open(db_path, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Невозможно открыть базу данных: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 0;
  }

  const char *create_table_sql =
      "CREATE TABLE IF NOT EXISTS 'patient_info' ("
      "id INTEGER PRIMARY KEY,"
      "surname TEXT,"
      "name TEXT,"
      "patronymic TEXT,"
      "gender TEXT,"
      "nationality TEXT,"
      "height INTEGER,"
      "weight INTEGER,"
      "birth_year INTEGER,"
      "birth_month INTEGER,"
      "birth_day INTEGER,"
      "phone TEXT,"
      "address TEXT,"
      "med_card_number TEXT,"
      "diagnosis TEXT,"
      "blood_group TEXT,"
      "department INTEGER"
      ");";

  char *err_msg = NULL;
  rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 0;
  }

  return 1;
}

void close_database() {
  if (db) {
    sqlite3_close(db);
    db = NULL;
  }
}

static int callback_print_patient(void *NotUsed, int argc, char **argv,
                                  char **azColName) {
  (void)NotUsed;

  printf("\nИнформация о пациенте:\n");
  printf("--------------------------------\n");

  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("--------------------------------\n");
  return 0;
}

int select_patient_by_id(int id, Patient *patient) {
  if (!db) return 0;

  sqlite3_stmt *stmt;
  const char *sql = "SELECT * FROM patient_info WHERE id = ?";

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса");
    return 0;
  }

  sqlite3_bind_int(stmt, 1, id);

  int found = 0;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    patient->id = sqlite3_column_int(stmt, 0);
    strncpy(patient->surname, (const char *)sqlite3_column_text(stmt, 1),
            sizeof(patient->surname) - 1);
    strncpy(patient->name, (const char *)sqlite3_column_text(stmt, 2),
            sizeof(patient->name) - 1);
    strncpy(patient->patronymic, (const char *)sqlite3_column_text(stmt, 3),
            sizeof(patient->patronymic) - 1);
    strncpy(patient->gender, (const char *)sqlite3_column_text(stmt, 4),
            sizeof(patient->gender) - 1);
    strncpy(patient->nationality, (const char *)sqlite3_column_text(stmt, 5),
            sizeof(patient->nationality) - 1);
    patient->height = sqlite3_column_int(stmt, 6);
    patient->weight = sqlite3_column_int(stmt, 7);
    patient->birth_year = sqlite3_column_int(stmt, 8);
    patient->birth_month = sqlite3_column_int(stmt, 9);
    patient->birth_day = sqlite3_column_int(stmt, 10);
    strncpy(patient->phone, (const char *)sqlite3_column_text(stmt, 11),
            sizeof(patient->phone) - 1);
    strncpy(patient->address, (const char *)sqlite3_column_text(stmt, 12),
            sizeof(patient->address) - 1);
    strncpy(patient->med_card_number,
            (const char *)sqlite3_column_text(stmt, 13),
            sizeof(patient->med_card_number) - 1);
    strncpy(patient->diagnosis, (const char *)sqlite3_column_text(stmt, 14),
            sizeof(patient->diagnosis) - 1);
    strncpy(patient->blood_group, (const char *)sqlite3_column_text(stmt, 15),
            sizeof(patient->blood_group) - 1);
    patient->department = sqlite3_column_int(stmt, 16);
    found = 1;
  }

  sqlite3_finalize(stmt);
  return found;
}

int select_patients_by_surname(const char *surname_pattern) {
  if (!db) return 0;

  char *sql = "SELECT * FROM patient_info WHERE surname LIKE ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса");
    return 0;
  }

  char pattern[100];
  snprintf(pattern, sizeof(pattern), "%%%s%%", surname_pattern);
  sqlite3_bind_text(stmt, 1, pattern, -1, SQLITE_STATIC);

  int count = 0;
  printf("\nРезультаты поиска по фамилии '%s':\n", surname_pattern);
  printf("------------------------------------------------\n");

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    count++;
    printf("ID: %d, Фамилия: %s, Имя: %s, Отчество: %s, Диагноз: %s\n",
           sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1),
           sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3),
           sqlite3_column_text(stmt, 14));
  }

  printf("------------------------------------------------\n");
  printf("Найдено записей: %d\n", count);

  sqlite3_finalize(stmt);
  return count;
}

int select_patients_by_department(int department) {
  if (!db) return 0;

  char *sql = "SELECT * FROM patient_info WHERE department = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса");
    return 0;
  }

  sqlite3_bind_int(stmt, 1, department);

  int count = 0;
  printf("\nПациенты отделения №%d:\n", department);
  printf("------------------------------------------------\n");

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    count++;
    printf("ID: %d, Фамилия: %s, Имя: %s, Отчество: %s, Диагноз: %s\n",
           sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1),
           sqlite3_column_text(stmt, 2), sqlite3_column_text(stmt, 3),
           sqlite3_column_text(stmt, 14));
  }

  printf("------------------------------------------------\n");
  printf("Найдено записей: %d\n", count);

  sqlite3_finalize(stmt);
  return count;
}

int insert_patient_autocommit(Patient *patient) {
  if (!db) return 0;

  const char *sql =
      "INSERT INTO patient_info (surname, name, patronymic, gender, "
      "nationality, "
      "height, weight, birth_year, birth_month, birth_day, phone, address, "
      "med_card_number, diagnosis, blood_group, department) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса вставки");
    return 0;
  }

  sqlite3_bind_text(stmt, 1, patient->surname, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, patient->name, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, patient->patronymic, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, patient->gender, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, patient->nationality, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 6, patient->height);
  sqlite3_bind_int(stmt, 7, patient->weight);
  sqlite3_bind_int(stmt, 8, patient->birth_year);
  sqlite3_bind_int(stmt, 9, patient->birth_month);
  sqlite3_bind_int(stmt, 10, patient->birth_day);
  sqlite3_bind_text(stmt, 11, patient->phone, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 12, patient->address, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 13, patient->med_card_number, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 14, patient->diagnosis, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 15, patient->blood_group, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 16, patient->department);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    print_sqlite_error("Ошибка при вставке пациента");
    return 0;
  }

  printf("Пациент успешно добавлен в базу данных (ID: %lld).\n",
         sqlite3_last_insert_rowid(db));

  return 1;
}

int insert_patients_transaction(Patient *patients, int count) {
  if (!db || count <= 0) return 0;

  const char *sql =
      "INSERT INTO patient_info (surname, name, patronymic, gender, "
      "nationality, "
      "height, weight, birth_year, birth_month, birth_day, phone, address, "
      "med_card_number, diagnosis, blood_group, department) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при начале транзакции");
    return 0;
  }

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса вставки");
    sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
    return 0;
  }

  int success = 1;
  for (int i = 0; i < count; i++) {
    Patient *p = &patients[i];

    sqlite3_bind_text(stmt, 1, p->surname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, p->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, p->patronymic, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, p->gender, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, p->nationality, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, p->height);
    sqlite3_bind_int(stmt, 7, p->weight);
    sqlite3_bind_int(stmt, 8, p->birth_year);
    sqlite3_bind_int(stmt, 9, p->birth_month);
    sqlite3_bind_int(stmt, 10, p->birth_day);
    sqlite3_bind_text(stmt, 11, p->phone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 12, p->address, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 13, p->med_card_number, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 14, p->diagnosis, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 15, p->blood_group, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 16, p->department);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
      print_sqlite_error("Ошибка при вставке пациента в транзакции");
      success = 0;
      break;
    }

    sqlite3_reset(stmt);
  }

  sqlite3_finalize(stmt);

  if (success) {
    rc = sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
      print_sqlite_error("Ошибка при завершении транзакции");
      success = 0;
    } else {
      printf("Транзакция успешно выполнена. Добавлено %d пациентов.\n", count);
    }
  } else {
    rc = sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
      print_sqlite_error("Ошибка при откате транзакции");
    } else {
      printf("Транзакция отменена из-за ошибки.\n");
    }
  }

  return success;
}

int delete_patient_by_id(int id) {
  if (!db) return 0;

  const char *sql = "DELETE FROM patient_info WHERE id = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса удаления");
    return 0;
  }

  sqlite3_bind_int(stmt, 1, id);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    print_sqlite_error("Ошибка при удалении пациента");
    return 0;
  }

  int changes = sqlite3_changes(db);
  if (changes == 0) {
    printf("Пациент с ID %d не найден.\n", id);
    return 0;
  }

  printf("Пациент с ID %d успешно удален.\n", id);
  return 1;
}

int update_patient(Patient *patient) {
  if (!db) return 0;

  const char *sql =
      "UPDATE patient_info SET "
      "surname = ?, name = ?, patronymic = ?, gender = ?, nationality = ?, "
      "height = ?, weight = ?, birth_year = ?, birth_month = ?, birth_day = ?, "
      "phone = ?, address = ?, med_card_number = ?, diagnosis = ?, "
      "blood_group = ?, department = ? "
      "WHERE id = ?";

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    print_sqlite_error("Ошибка при подготовке запроса обновления");
    return 0;
  }

  sqlite3_bind_text(stmt, 1, patient->surname, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, patient->name, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, patient->patronymic, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, patient->gender, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, patient->nationality, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 6, patient->height);
  sqlite3_bind_int(stmt, 7, patient->weight);
  sqlite3_bind_int(stmt, 8, patient->birth_year);
  sqlite3_bind_int(stmt, 9, patient->birth_month);
  sqlite3_bind_int(stmt, 10, patient->birth_day);
  sqlite3_bind_text(stmt, 11, patient->phone, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 12, patient->address, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 13, patient->med_card_number, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 14, patient->diagnosis, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 15, patient->blood_group, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 16, patient->department);
  sqlite3_bind_int(stmt, 17, patient->id);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    print_sqlite_error("Ошибка при обновлении данных пациента");
    return 0;
  }

  int changes = sqlite3_changes(db);
  if (changes == 0) {
    printf("Пациент с ID %d не найден или данные не изменились.\n",
           patient->id);
    return 0;
  }

  printf("Данные пациента с ID %d успешно обновлены.\n", patient->id);
  return 1;
}

int execute_query(const char *query) {
  if (!db) return 0;

  char *err_msg = NULL;
  int rc = sqlite3_exec(db, query, callback_print_patient, 0, &err_msg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
    sqlite3_free(err_msg);
    return 0;
  }

  printf("Запрос успешно выполнен.\n");
  return 1;
}