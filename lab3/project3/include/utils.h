#ifndef UTILS_H
#define UTILS_H

#include "database.h"

void clear_screen();

void wait_for_key();

void read_line(char* buffer, int size);

void print_patient(Patient* patient);

void fill_patient_from_input(Patient* patient);
void create_patient_report(const char* filename);

#endif  