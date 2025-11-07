#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "mystring.h"

int loadStudentsFromText(struct Student **students) {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) return 0;

    int capacity = 10;
    *students = (struct Student *)malloc(sizeof(struct Student) * capacity);
    if (!*students) return 0;

    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (count == capacity) {
            capacity *= 2;
            *students = (struct Student *)realloc(*students, sizeof(struct Student) * capacity);
            if (!*students) {
                fclose(fp);
                return 0;
            }
        }

        char tname[256], tsurname[256], tpid[256], temail[256], tphone[256], tbirth[256], tgroup[256];
        int age;
        float gpa;

        sscanf(line, "%255[^,],%255[^,],%d,%255[^,],%255[^,],%255[^,],%255[^,],%255[^,],%f",
               tname, tsurname, &age, tpid, temail, tphone, tbirth, tgroup, &gpa);

        (*students)[count].name      = myStrdup(tname);
        (*students)[count].surname   = myStrdup(tsurname);
        (*students)[count].age       = age;
        (*students)[count].pid       = myStrdup(tpid);
        (*students)[count].email     = myStrdup(temail);
        (*students)[count].phone     = myStrdup(tphone);
        (*students)[count].birthdate = myStrdup(tbirth);
        (*students)[count].group     = myStrdup(tgroup);
        (*students)[count].gpa       = gpa;
        count++;
    }
    fclose(fp);
    return count;
}

void saveStudentsToText(const struct Student *students, int count) {
    FILE *fp = fopen("students.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%d,%s,%s,%s,%s,%s,%.2f\n",
                students[i].name, students[i].surname, students[i].age, students[i].pid,
                students[i].email, students[i].phone, students[i].birthdate, students[i].group, students[i].gpa);
    }
    fclose(fp);
}

void addStudent(struct Student **students, int *count) {
    *students = (struct Student *)realloc(*students, sizeof(struct Student) * (*count + 1));
    if (!*students) return;

    char temp[256];
    printf("Enter name: ");     scanf("%255s", temp); (*students)[*count].name      = myStrdup(temp);
    printf("Enter surname: ");  scanf("%255s", temp); (*students)[*count].surname   = myStrdup(temp);
    printf("Enter age: ");      scanf("%d", &(*students)[*count].age);
    printf("Enter PID: ");      scanf("%255s", temp); (*students)[*count].pid       = myStrdup(temp);
    printf("Enter email: ");    scanf("%255s", temp); (*students)[*count].email     = myStrdup(temp);
    printf("Enter phone: ");    scanf("%255s", temp); (*students)[*count].phone     = myStrdup(temp);
    printf("Enter birthdate (YYYY-MM-DD): "); scanf("%255s", temp); (*students)[*count].birthdate = myStrdup(temp);
    printf("Enter group: ");    scanf("%255s", temp); (*students)[*count].group     = myStrdup(temp);
    printf("Enter GPA: ");      scanf("%f", &(*students)[*count].gpa);
    (*count)++;
}

void deleteStudentByPID(struct Student **students, int *count, const char *pid) {
    for (int i = 0; i < *count; i++) {
        if (myStrcmp((*students)[i].pid, pid) == 0) {
            freeStudent(&(*students)[i]);
            for (int j = i; j < *count - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            (*count)--;
            *students = (struct Student *)realloc(*students, sizeof(struct Student) * (*count));
            return;
        }
    }
}

void displayStudents(const struct Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %s, Age: %d, PID: %s, Email: %s, Phone: %s, Birth: %s, Group: %s, GPA: %.2f\n",
               students[i].name, students[i].surname, students[i].age, students[i].pid,
               students[i].email, students[i].phone, students[i].birthdate, students[i].group, students[i].gpa);
    }
}

void displaySingleStudent(const struct Student *student) {
    printf("%s %s, Age: %d, PID: %s, Email: %s, Phone: %s, Birth: %s, Group: %s, GPA: %.2f\n",
           student->name, student->surname, student->age, student->pid,
           student->email, student->phone, student->birthdate, student->group, student->gpa);
}

void freeStudent(struct Student *student) {
    free(student->name);
    free(student->surname);
    free(student->pid);
    free(student->email);
    free(student->phone);
    free(student->birthdate);
    free(student->group);
}