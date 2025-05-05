#ifndef PATIENT_H
#define PATIENT_H

#define MAX_LEN 256

typedef struct {
  char lastName[MAX_LEN];
  char firstName[MAX_LEN];
  char patronymic[MAX_LEN];
  char gender[MAX_LEN];
  char nationality[MAX_LEN];
  int height;
  int weight;
  int birthYear, birthMonth, birthDay;
  char phone[MAX_LEN];
  char address[MAX_LEN];
  int hospitalNumber;
  int department;
  char medicalCardNumber[MAX_LEN];
  char diagnosis[MAX_LEN];
  char bloodGroup[MAX_LEN];
} Patient;

void printPatient(const Patient *p, FILE *out);

#endif
