#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patient.h"

int readPatient(FILE *in, Patient *p) {
  return fscanf(in, "%s %s %s %s %s %d %d %d %d %d %s %[^\n] %d %d %s %s %s\n",
                p->lastName, p->firstName, p->patronymic, p->gender,
                p->nationality, &p->height, &p->weight, &p->birthYear,
                &p->birthMonth, &p->birthDay, p->phone, p->address,
                &p->hospitalNumber, &p->department, p->medicalCardNumber,
                p->diagnosis, p->bloodGroup);
}

void processPatients(const char *inputPath, const char *outputPath) {
  FILE *in = fopen(inputPath, "r");
  FILE *out = fopen(outputPath, "w");
  Patient p;
  int found = 0;

  if (!in || !out) {
    perror("Ошибка открытия файла");
    return;
  }

  while (readPatient(in, &p) == 17) {
    if (p.department == 18) {
      printPatient(&p, out);
      found = 1;
    }
  }

  if (!found) {
    fprintf(out, "Пациенты из 18 отделения не найдены.\n");
  }

  fclose(in);
  fclose(out);
}
