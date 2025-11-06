#include <stdio.h>
#include <stdlib.h>
#include "parents.h"
#include "mystring.h"

int loadParentsFromText(struct Parent **parents) {
    FILE *fp = fopen("parents.txt", "r");
    if (!fp) return 0;
    int capacity = 10;
    *parents = (struct Parent *)malloc(sizeof(struct Parent) * capacity);
    if (!*parents) return 0;
    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (count == capacity) {
            capacity *= 2;
            *parents = (struct Parent *)realloc(*parents, sizeof(struct Parent) * capacity);
            if (!*parents) {
                fclose(fp);
                return 0;
            }
        }
        char tname[256], tsurname[256], tpid[256], temail[256], tphone[256], tbirth[256], tspid[256];
        int age;
        sscanf(line, "%255[^,],%255[^,],%d,%255[^,],%255[^,],%255[^,],%255[^,],%255[^,]",
               tname, tsurname, &age, tpid, temail, tphone, tbirth, tspid);
        (*parents)[count].name        = myStrdup(tname);
        (*parents)[count].surname     = myStrdup(tsurname);
        (*parents)[count].age         = age;
        (*parents)[count].pid         = myStrdup(tpid);
        (*parents)[count].email       = myStrdup(temail);
        (*parents)[count].phone       = myStrdup(tphone);
        (*parents)[count].birthdate   = myStrdup(tbirth);
        (*parents)[count].student_pid = myStrdup(tspid);
        count++;
    }
    fclose(fp);
    return count;
}

void saveParentsToText(const struct Parent *parents, int count) {
    FILE *fp = fopen("parents.txt", "w");
    if (!fp) return;
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%d,%s,%s,%s,%s,%s\n",
                parents[i].name, parents[i].surname, parents[i].age, parents[i].pid,
                parents[i].email, parents[i].phone, parents[i].birthdate, parents[i].student_pid);
    }
    fclose(fp);
}

void addParent(struct Parent **parents, int *count) {
    *parents = (struct Parent *)realloc(*parents, sizeof(struct Parent) * (*count + 1));
    if (!*parents) return;
    char temp[256];
    printf("Enter name: ");
    scanf("%255s", temp);
    (*parents)[*count].name = myStrdup(temp);
    printf("Enter surname: ");
    scanf("%255s", temp);
    (*parents)[*count].surname = myStrdup(temp);
    printf("Enter age: ");
    scanf("%d", &(*parents)[*count].age);
    printf("Enter PID: ");
    scanf("%255s", temp);
    (*parents)[*count].pid = myStrdup(temp);
    printf("Enter email: ");
    scanf("%255s", temp);
    (*parents)[*count].email = myStrdup(temp);
    printf("Enter phone: ");
    scanf("%255s", temp);
    (*parents)[*count].phone = myStrdup(temp);
    printf("Enter birthdate (YYYY-MM-DD): ");
    scanf("%255s", temp);
    (*parents)[*count].birthdate = myStrdup(temp);
    printf("Enter student PID: ");
    scanf("%255s", temp);
    (*parents)[*count].student_pid = myStrdup(temp);
    (*count)++;
}

void deleteParentByPID(struct Parent **parents, int *count, const char *pid) {
    for (int i = 0; i < *count; i++) {
        if (myStrcmp((*parents)[i].pid, pid) == 0) {
            freeParent(&(*parents)[i]);
            for (int j = i; j < *count - 1; j++) {
                (*parents)[j] = (*parents)[j + 1];
            }
            (*count)--;
            *parents = (struct Parent *)realloc(*parents, sizeof(struct Parent) * (*count));
            return;
        }
    }
}

void displayParents(const struct Parent *parents, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %s, Age: %d, PID: %s, Email: %s, Phone: %s, Birth: %s, Student PID: %s\n",
               parents[i].name, parents[i].surname, parents[i].age, parents[i].pid,
               parents[i].email, parents[i].phone, parents[i].birthdate, parents[i].student_pid);
    }
}

void freeParent(struct Parent *parent) {
    free(parent->name);
    free(parent->surname);
    free(parent->pid);
    free(parent->email);
    free(parent->phone);
    free(parent->birthdate);
    free(parent->student_pid);
}

void sortByNameParent(struct Parent *parents, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (myStrcmp(parents[j].name, parents[j + 1].name) > 0) {
                struct Parent temp = parents[j];
                parents[j] = parents[j + 1];
                parents[j + 1] = temp;
            }
        }
    }
}

void sortByAgeParent(struct Parent *parents, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (parents[j].age > parents[j + 1].age) {
                struct Parent temp = parents[j];
                parents[j] = parents[j + 1];
                parents[j + 1] = temp;
            }
        }
    }
}

void sortByStudentPID(struct Parent *parents, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (myStrcmp(parents[j].student_pid, parents[j + 1].student_pid) > 0) {
                struct Parent temp = parents[j];
                parents[j] = parents[j + 1];
                parents[j + 1] = temp;
            }
        }
    }
}