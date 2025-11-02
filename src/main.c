#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    Student staticArr[] = {
        {"kristina", "merinsh", "PX24", 1, "F", 12345678, 20040201, 3, 20, 1},
        {"Artjom", "bezubijkristjanin", "PX23", 2, "M", 12345679, 20040215, 4, 22, 2},
        {"marja", "vanova", "PX69", 3, "F", 12345680, 20040230, 2, 19, 3},
        {"maksym", "Durikhin", "PX24", 4, "M", 12345681, 20040210, 5, 21, 4}
    };
    int staticCount = sizeof(staticArr) / sizeof(staticArr[0]);

    printf("___STATIC_ARRAY___\n");
    printf("Original list:\n");
    printStudents(staticArr, staticCount);

    sortByAge(staticArr, staticCount);
    printf("Sorted by age:\n");
    printStudents(staticArr, staticCount);

    sortByName(staticArr, staticCount);
    printf("Sorted by name:\n");
    printStudents(staticArr, staticCount);

    sortBySurname(staticArr, staticCount);
    printf("Sorted by surname:\n");
    printStudents(staticArr, staticCount);

    sortByGroup(staticArr, staticCount);
    printf("Sorted by group:\n");
    printStudents(staticArr, staticCount);

    sortByParentId(staticArr, staticCount);
    printf("Sorted by parentId:\n");
    printStudents(staticArr, staticCount);

    Parents staticParents[] = {
        {"anna", "merinsh", "F", 12345678, 19800101, 45, 1},
        {"boris", "bezubijkristjanin", "M", 12345679, 19801212, 46, 2},
        {"carla", "vanova", "F", 12345680, 19800630, 50, 3},
        {"dmitry", "Durikhin", "M", 12345681, 19800210, 51, 4}
    };
    int parentsStaticCount = sizeof(staticParents) / sizeof(staticParents[0]);

    printf("\n___STATIC_PARENTS___\n");
    printf("Original parents list:\n");
    printParents(staticParents, parentsStaticCount);

    sortParentsBySurname(staticParents, parentsStaticCount);
    printf("Sorted parents by surname:\n");
    printParents(staticParents, parentsStaticCount);

    sortParentsById(staticParents, parentsStaticCount);
    printf("Sorted parents by id:\n");
    printParents(staticParents, parentsStaticCount);

    int p, n, i, k, mode;
    Parents *dynamicParents = NULL;
    Student *dynamicArr = NULL;
    printf("___USER_ARRAY__\n");
    printf("Load from .txt files? (1=yes, 0=no): ");
    scanf("%d", &mode);

    if (mode == 1) {
        if (loadParentsFromfile("parents.txt", &dynamicParents, &p) != 0) {
            printf("Failed to load parents.txt, switching to manual input.\n");
            mode = 0;
        }
    }
    if (mode == 1) {
        if (loadStudentsFromfile("students.txt", &dynamicArr, &n) != 0) {
            printf("Failed to load students.txt, switching to manual input.\n");
            free(dynamicParents);
            dynamicParents = NULL;
            mode = 0;
        }
    }

    if (mode == 0) {
        printf("Enter number of parents: ");
        scanf("%d", &p);

        dynamicParents = (Parents*)malloc(p * sizeof(Parents));
        for (i = 0; i < p; i++) {
            printf("\nEnter data for parent %d:\n", i + 1);
            char tempName[1024];  // Temporary buffer for input
            char tempSurname[1024];
            
            printf("Parent Name: ");
            if (scanf("%1023s", tempName) != 1) {
                printf("Error reading name.\n");
                free(dynamicParents);
                return 1;
            }
            dynamicParents[i].name = strdup(tempName);
            if (!dynamicParents[i].name) {
                printf("Memory allocation failed for name.\n");
                free(dynamicParents);
                return 1;
            }
            
            printf("Parent Surname: ");
            if (scanf("%1023s", tempSurname) != 1) {
                printf("Error reading surname.\n");
                free(dynamicParents[i].name);
                free(dynamicParents);
                return 1;
            }
            dynamicParents[i].surname = strdup(tempSurname);
            if (!dynamicParents[i].surname) {
                printf("Memory allocation failed for surname.\n");
                free(dynamicParents[i].name);
                free(dynamicParents);
                return 1;
            }
            printf("Parent Sex: ");
            scanf("%9s", dynamicParents[i].Sex);
            printf("Parent Mobile phone (int): ");
            scanf("%d", &dynamicParents[i].mobilephone);
            printf("Parent Date of birth (YYYYMMDD): ");
            scanf("%d", &dynamicParents[i].dateofbith);
            printf("Parent Age: ");
            scanf("%d", &dynamicParents[i].age);
            printf("Parent ID: ");
            scanf("%d", &dynamicParents[i].id);
        }

        printf("\nEnter number of students: ");
        scanf("%d", &n);

        dynamicArr = (Student*)malloc(n * sizeof(Student));
        for (i = 0; i < n; i++) {
            printf("\nEnter data for student %d:\n", i + 1);
            char tempName[1024];
            char tempSurname[1024];
            
            printf("Name: ");
            if (scanf("%1023s", tempName) != 1) {
                printf("Error reading name.\n");
                // Free any previously allocated memory in this student
                if (i > 0) {
                    for (int j = 0; j < i; j++) {
                        free(dynamicArr[j].name);
                        free(dynamicArr[j].surname);
                    }
                }
                free(dynamicArr);
                freeParents(dynamicParents, p);
                return 1;
            }
            dynamicArr[i].name = strdup(tempName);
            if (!dynamicArr[i].name) {
                printf("Memory allocation failed for name.\n");
                if (i > 0) {
                    for (int j = 0; j < i; j++) {
                        free(dynamicArr[j].name);
                        free(dynamicArr[j].surname);
                    }
                }
                free(dynamicArr);
                freeParents(dynamicParents, p);
                return 1;
            }
            
            printf("Surname: ");
            if (scanf("%1023s", tempSurname) != 1) {
                printf("Error reading surname.\n");
                free(dynamicArr[i].name);
                if (i > 0) {
                    for (int j = 0; j < i; j++) {
                        free(dynamicArr[j].name);
                        free(dynamicArr[j].surname);
                    }
                }
                free(dynamicArr);
                freeParents(dynamicParents, p);
                return 1;
            }
            dynamicArr[i].surname = strdup(tempSurname);
            if (!dynamicArr[i].surname) {
                printf("Memory allocation failed for surname.\n");
                free(dynamicArr[i].name);
                if (i > 0) {
                    for (int j = 0; j < i; j++) {
                        free(dynamicArr[j].name);
                        free(dynamicArr[j].surname);
                    }
                }
                free(dynamicArr);
                freeParents(dynamicParents, p);
                return 1;
            }
            
            printf("Group: ");
            scanf("%19s", dynamicArr[i].group);
            while (1) {
                int enteredId;
                int found = 0;
                printf("Parent ID (must exist): ");
                scanf("%d", &enteredId);
                for (k = 0; k < p; k++) {
                    if (dynamicParents[k].id == enteredId) { found = 1; break; }
                }
                if (found) { dynamicArr[i].parentId = enteredId; break; }
                printf("Parent ID not found. Try again.\n");
            }
            printf("Sex: ");
            scanf("%9s", dynamicArr[i].SEX);
            printf("Mobile phone (int): ");
            scanf("%d", &dynamicArr[i].mobilephone);
            printf("Date of birth (YYYYMMDD): ");
            scanf("%d", &dynamicArr[i].dateofbirth);
            printf("Anus size (int): ");
            scanf("%d", &dynamicArr[i].anussize);
            printf("Age: ");
            scanf("%d", &dynamicArr[i].age);
            printf("ID: ");
            scanf("%d", &dynamicArr[i].id);
        }
    }

    printf("\nDynamic students (unsorted):\n");
    printStudents(dynamicArr, n);

    printf("\nDynamic parents (unsorted):\n");
    printParents(dynamicParents, p);

    sortByAge(dynamicArr, n);
    printf("Sorted by age:\n");
    printStudents(dynamicArr, n);

    sortByName(dynamicArr, n);
    printf("Sorted by name:\n");
    printStudents(dynamicArr, n);

    sortBySurname(dynamicArr, n);
    printf("Sorted by surname:\n");
    printStudents(dynamicArr, n);

    sortByGroup(dynamicArr, n);
    printf("Sorted by group:\n");
    printStudents(dynamicArr, n);

    sortByParentId(dynamicArr, n);
    printf("Sorted by parentId:\n");
    printStudents(dynamicArr, n);

    sortParentsBySurname(dynamicParents, p);
    printf("Sorted parents by surname:\n");
    printParents(dynamicParents, p);

    sortParentsById(dynamicParents, p);
    printf("Sorted parents by id:\n");
    printParents(dynamicParents, p);

    saveStudentsTofile("students.txt", dynamicArr, n);
    saveParentsTofile("parents.txt", dynamicParents, p);

    free(dynamicArr);
    free(dynamicParents);
    return 0;
}


