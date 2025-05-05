#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

typedef struct {
  int id;
  char surname[50];
  char name[50];
  char patronymic[50];
  char gender[2];
  char nationality[50];
  int height;
  int weight;
  int birth_year;
  int birth_month;
  int birth_day;
  char phone[20];
  char address[200];
  char med_card_number[20];
  char diagnosis[100];
  char blood_group[5];
  int department;
} Patient;

int init_database(const char* db_path);

void close_database();

int select_patient_by_id(int id, Patient* patient);

int select_patients_by_surname(const char* surname_pattern);

int select_patients_by_department(int department);

int insert_patient_autocommit(Patient* patient);

int insert_patients_transaction(Patient* patients, int count);

int delete_patient_by_id(int id);

int update_patient(Patient* patient);

int execute_query(const char* query);

#endif  
