#include <stdio.h>
#include <stdlib.h>
#include "student.h"

/* === Ручные строковые функции === */
int myStrCmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int myStrLen(const char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}

void myStrCpy(char *dest, const char *src) {
    while (*src) *dest++ = *src++;
    *dest = 0;
}

/* === Вывод === */
void printStudents(Student students[], int n) {
    int i;
    printf("\n%-10s %-10s %-10s %-12s %-6s %-12s %-12s %-10s %-5s %-6s\n",
           "Name", "Surname", "Group", "ParentID", "Sex", "Phone", "Birth", "Anus", "Age", "ID");
    printf("____________________________________________________________________________________________\n");
    for (i = 0; i < n; i++) {
        printf("%-10s %-10s %-10s %-12d %-6s %-12d %-12d %-10d %-5d %-6d\n",
               students[i].name, students[i].surname, students[i].group,
               students[i].parentId, students[i].SEX,
               students[i].mobilephone, students[i].dateofbirth,
               students[i].anussize, students[i].age, students[i].id);
    }
    printf("\n");
}

void printParents(Parents parents[], int n) {
    int i;
    printf("\n%-12s %-12s %-6s %-12s %-12s %-5s %-6s\n",
           "PName", "PSurname", "Sex", "Phone", "Birth", "Age", "ID");
    printf("______________________________________________________________________\n");
    for (i = 0; i < n; i++) {
        printf("%-12s %-12s %-6s %-12d %-12d %-5d %-6d\n",
               parents[i].name, parents[i].surname, parents[i].Sex,
               parents[i].mobilephone, parents[i].dateofbith,
               parents[i].age, parents[i].id);
    }
    printf("\n");
}

/* === Сортировки студентов (пузырьком) === */
void sortByAge(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (students[i].age > students[j].age) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
}

void sortByName(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (myStrCmp(students[i].name, students[j].name) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
}

void sortBySurname(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (myStrCmp(students[i].surname, students[j].surname) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
}

void sortByGroup(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (myStrCmp(students[i].group, students[j].group) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
}

void sortByParentId(Student students[], int n) {
    int i, j;
    Student temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (students[i].parentId > students[j].parentId) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
}

void sortParentsByName(Parents parents[], int n) {
    int i, j;
    Parents tmp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (myStrCmp(parents[i].name, parents[j].name) > 0) {
                tmp = parents[i];
                parents[i] = parents[j];
                parents[j] = tmp;
            }
}

void sortParentsBySurname(Parents parents[], int n) {
    int i, j;
    Parents tmp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (myStrCmp(parents[i].surname, parents[j].surname) > 0) {
                tmp = parents[i];
                parents[i] = parents[j];
                parents[j] = tmp;
            }
}

void sortParentsByAge(Parents parents[], int n) {
    int i, j;
    Parents tmp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (parents[i].age > parents[j].age) {
                tmp = parents[i];
                parents[i] = parents[j];
                parents[j] = tmp;
            }
}

void sortParentsById(Parents parents[], int n) {
    int i, j;
    Parents tmp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (parents[i].id > parents[j].id) {
                tmp = parents[i];
                parents[i] = parents[j];
                parents[j] = tmp;
            }
}

void saveStudentsTofile(const c
void saveStudentsTofile(const char *filename, Student students[], int n) {
    FILE *f = fopen(filename, "w");
    if (!f) return;
    fprintf(f, "%-10s %-10s %-10s %-12s %-6s %-12s %-12s %-10s %-5s %-6s\n",
            "Name", "Surname", "Group", "ParentID", "Sex", "Phone", "Birth", "Anus", "Age", "ID");
    fprintf(f, "____________________________________________________________________________________________\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%-10s %-10s %-10s %-12d %-6s %-12d %-12d %-10d %-5d %-6d\n",
                students[i].name, students[i].surname, students[i].group,
                students[i].parentId, students[i].SEX,
                students[i].mobilephone, students[i].dateofbirth,
                students[i].anussize, students[i].age, students[i].id);
    }
    fclose(f);
}

void saveParentsTofile(const char *filename, Parents parents[], int n) {
    FILE *f = fopen(filename, "w");
    if (!f) return;
    fprintf(f, "%-12s %-12s %-6s %-12s %-12s %-5s %-6s\n",
            "PName", "PSurname", "Sex", "Phone", "Birth", "Age", "ID");
    fprintf(f, "______________________________________________________________________\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%-12s %-12s %-6s %-12d %-12d %-5d %-6d\n",
                parents[i].name, parents[i].surname, parents[i].Sex,
                parents[i].mobilephone, parents[i].dateofbith,
                parents[i].age, parents[i].id);
    }
    fclose(f);
}

int loadStudentsFromfile(const char *filename, Student **outStudents, int *outCount) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char buf[512];
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }

    int cap = 16, cnt = 0;
    Student *arr = (Student*)malloc(cap * sizeof(Student));
    if (!arr) { fclose(f); return -1; }

    while (fgets(buf, sizeof(buf), f)) {
        Student s;
        char tname[50], tsurname[50], tgroup[20], tsex[10];
        int pid, phone, birth, anus, age, id;
        int parsed = sscanf(buf, "%49s %49s %19s %d %9s %d %d %d %d %d",
                            tname, tsurname, tgroup, &pid, tsex, &phone, &birth, &anus, &age, &id);
        if (parsed != 10) continue;

        int len = myStrLen(tname);
        s.name = (char*)malloc(len + 1);
        myStrCpy(s.name, tname);
        len = myStrLen(tsurname);
        s.surname = (char*)malloc(len + 1);
        myStrCpy(s.surname, tsurname);
        myStrCpy(s.group, tgroup);
        myStrCpy(s.SEX, tsex);
        s.parentId = pid; s.mobilephone = phone; s.dateofbirth = birth;
        s.anussize = anus; s.age = age; s.id = id;

        if (cnt == cap) {
            cap *= 2;
            Student *tmp = (Student*)realloc(arr, cap * sizeof(Student));
            if (!tmp) { freeStudents(arr, cnt); fclose(f); return -1; }
            arr = tmp;
        }
        arr[cnt++] = s;
    }
    fclose(f);
    *outStudents = arr;
    *outCount = cnt;
    return 0;
}

int loadParentsFromfile(const char *filename, Parents **outParents, int *outCount) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char buf[512];
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }

    int cap = 16, cnt = 0;
    Parents *arr = (Parents*)malloc(cap * sizeof(Parents));
    if (!arr) { fclose(f); return -1; }

    while (fgets(buf, sizeof(buf), f)) {
        Parents p;
        char tname[50], tsurname[50], tsex[10];
        int phone, birth, age, id;
        int parsed = sscanf(buf, "%49s %49s %9s %d %d %d %d",
                            tname, tsurname, tsex, &phone, &birth, &age, &id);
        if (parsed != 7) continue;

        int len = myStrLen(tname);
        p.name = (char*)malloc(len + 1);
        myStrCpy(p.name, tname);
        len = myStrLen(tsurname);
        p.surname = (char*)malloc(len + 1);
        myStrCpy(p.surname, tsurname);
        myStrCpy(p.Sex, tsex);
        p.mobilephone = phone; p.dateofbith = birth;
        p.age = age; p.id = id;

        if (cnt == cap) {
            cap *= 2;
            Parents *tmp = (Parents*)realloc(arr, cap * sizeof(Parents));
            if (!tmp) { freeParents(arr, cnt); fclose(f); return -1; }
            arr = tmp;
        }
        arr[cnt++] = p;
    }
    fclose(f);
    *outParents = arr;
    *outCount = cnt;
    return 0;
}

void freeStudent(Student *s) {
    free(s->name);
    free(s->surname);
}

void freeStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) freeStudent(&students[i]);
    free(students);
}

void freeParent(Parents *p) {
    free(p->name);
    free(p->surname);
}

void freeParents(Parents *parents, int count) {
    for (int i = 0; i < count; i++) freeParent(&parents[i]);
    free(parents);
}

void filterStudentsByGroup(Student students[], int n, const char *group, Student **out, int *outN) {
    int count = 0, i;
    for (i = 0; i < n; i++)
        if (myStrCmp(students[i].group, group) == 0) count++;

    *out = (Student*)malloc(count * sizeof(Student));
    int idx = 0;
    for (i = 0; i < n; i++) {
        if (myStrCmp(students[i].group, group) == 0) {
            (*out)[idx] = students[i];
            int len = myStrLen(students[i].name);
            (*out)[idx].name = (char*)malloc(len + 1);
            myStrCpy((*out)[idx].name, students[i].name);
            len = myStrLen(students[i].surname);
            (*out)[idx].surname = (char*)malloc(len + 1);
            myStrCpy((*out)[idx].surname, students[i].surname);
            idx++;
        }
    }
    *outN = count;
}

void filterStudentsByName(Student students[], int n, const char *name, Student **out, int *outN) {
    int count = 0, i;
    for (i = 0; i < n; i++)
        if (myStrCmp(students[i].name, name) == 0) count++;

    *out = (Student*)malloc(count * sizeof(Student));
    int i dx = 0;
    for (i = 0; i < n; i++) {
        if (myStrCmp(students[i].name, name) == 0) {
            (*out)[idx] = students[i];
            int len = myStrLen(students[i].name);
            (*out)[idx].name = (char*)malloc(len + 1);
            myStrCpy((*out)[idx].name, students[i].name);
            len = myStrLen(students[i].surname);
            (*out)[idx].surname = (char*)malloc(len + 1);
            myStrCpy((*out)[idx].surname, students[i].surname);
            idx++;
        }
    }
    *outN = count;
}