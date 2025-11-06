#ifndef SORTS_H
#define SORTS_H

#include "database.h"

void sortByName(struct Student *students, int count);
void sortByAge(struct Student *students, int count);
void sortByGroup(struct Student *students, int count);
void sortByGPA(struct Student *students, int count);

#endif