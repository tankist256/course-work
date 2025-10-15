#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    Student staticArr[] = {
        {"kristina", "merinsh", "PX24", 20},
        {"Artjom", "bezubijkristjanin", "PX23", 22},
        {"marja", "vanova", "PX69", 19},
        {"maksym", "Durikhin", "PX24", 21}
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

    int n, i;
    printf("___USER_ARRAY__\n");
    printf("Enter number of students: ");
    scanf("%d", &n);

    Student *dynamicArr = (Student*)malloc(n * sizeof(Student));
    
    for (i = 0; i < n; i++) {
        printf("\nEnter data for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", dynamicArr[i].name);
        printf("Surname: ");
        scanf("%s", dynamicArr[i].surname);
        printf("Group: ");
        scanf("%s", dynamicArr[i].group);
        printf("Age: ");
        scanf("%d", &dynamicArr[i].age);
    }

    printf("\nDynamic array (unsorted):\n");
    printStudents(dynamicArr, n);

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

    free(dynamicArr);
    return 0;
}
