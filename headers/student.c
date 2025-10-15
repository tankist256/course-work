#include <stdio.h>
#include <stdlib.h>
#include "student.h"

/* my string compare */
int myStrCmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

/* print students */
void printStudents(Student students[], int n) {
    int i;
    printf("\n%-10s %-10s %-10s %-5s\n", "Name", "Surname", "Group", "Age");
    printf("---------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-10s %-10s %-10s %-5d\n",
               students[i].name,
               students[i].surname,
               students[i].group,
               students[i].age);
    }
    printf("\n");
}

/* sorted by age */
void sortByAge(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (students[i].age > students[j].age) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

/* sorted by name */
void sortByName(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (myStrCmp(students[i].name, students[j].name) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

/* sorted by group */
void sortBySurname(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (myStrCmp(students[i].surname, students[j].surname) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

/* sorted by group */
void sortByGroup(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (myStrCmp(students[i].group, students[j].group) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}
