#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char name[50];
    char surname[50];
    char group[20];
    int age;
} Student;

void printStudents(Student students[], int n);
void sortByAge(Student students[], int n);
void sortByName(Student students[], int n);
void sortBySurname(Student students[], int n);
void sortByGroup(Student students[], int n);
int myStrCmp(const char *a, const char *b);

#endif
