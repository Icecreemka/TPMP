#include "patient.h"

#include <stdio.h>

void printPatient(const Patient *p, FILE *out) {
  fprintf(out, "%s %s %s, ���������: %d, �������: %s\n", p->lastName,
          p->firstName, p->patronymic, p->department, p->diagnosis);
}
