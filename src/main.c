#include <stdio.h>
#include <stdlib.h>
#include "../include/database.h"
#include "../include/sorts.h"
#include "../include/parents.h"
#include "../include/mystring.h"

void handleStudents(int argc, char *argv[]);
void handleParents (int argc, char *argv[]);
void handleLinked   (int argc, char *argv[]);
void handleSearchByParent(int argc, char *argv[]);
void showHelp();

int main(int argc, char *argv[])
{
    if (argc == 1) {
        showHelp();
        return 0;
    }

    if (myStrcmp(argv[1], "--parent") == 0) {
        handleParents(argc - 1, argv + 1);
    }
    else if (myStrcmp(argv[1], "--show-linked") == 0) {
        handleLinked(argc, argv);
    }
    else if (myStrcmp(argv[1], "--search-parent") == 0) {
        handleSearchByParent(argc, argv);
    }
    else {
        handleStudents(argc, argv);
    }
    return 0;
}

void showHelp()
{
    printf("Usage:\n");
    printf("./program                     # Show help (this message)\n");
    printf("./program --add               # Add new student\n");
    printf("./program --delete            # Delete student by PID\n");
    printf("./program --sort              # Sort students (menu)\n");
    printf("./program --filter <GROUP>    # Filter students by group\n");
    printf("./program --filter <GROUP> --sort  # Filter and sort\n");
    printf("./program --show-linked <PID> # Show student + parents\n");
    printf("./program --search-parent <NAME> # Search students by parent name\n");
    printf("./program --help              # Show help\n");
    printf("\nParent commands (prefix with --parent):\n");
    printf("./program --parent --add      # Add parent\n");
    printf("./program --parent --delete   # Delete parent by PID\n");
    printf("./program --parent --sort     # Sort parents\n");
    printf("./program --parent --filter <STUDENT_PID> # Filter parents by student PID\n");
}


void handleStudents(int argc, char *argv[])
{
    struct Student *students = NULL;
    int count = loadStudentsFromText(&students);

    if (argc == 1) {
        displayStudents(students, count);
    }
    else if (argc > 1) {
        if (myStrcmp(argv[1], "--add") == 0) {
            addStudent(&students, &count);
        }
        else if (myStrcmp(argv[1], "--delete") == 0) {
            char pid[256];
            printf("Enter PID to delete: ");
            scanf("%255s", pid);
            deleteStudentByPID(&students, &count, pid);
        }
        else if (myStrcmp(argv[1], "--sort") == 0) {
            struct Student *copy = malloc(sizeof(struct Student) * count);
            if (copy) {
                for (int i = 0; i < count; i++) copy[i] = students[i];
                int choice;
                printf("Sort by: 1-Name, 2-Age, 3-Group, 4-GPA: ");
                scanf("%d", &choice);
                if (choice == 1) sortByName(copy, count);
                else if (choice == 2) sortByAge(copy, count);
                else if (choice == 3) sortByGroup(copy, count);
                else if (choice == 4) sortByGPA(copy, count);
                displayStudents(copy, count);
                free(copy);
            }
        }
        else if (myStrcmp(argv[1], "--filter") == 0 && argc > 2) {
            char group[256];
            myStrcpy(group, argv[2]);

            int filter_count = 0;
            struct Student *filtered = malloc(sizeof(struct Student) * count);
            for (int i = 0; i < count; i++) {
                if (myStrcmp(students[i].group, group) == 0)
                    filtered[filter_count++] = students[i];
            }

            if (argc > 3 && myStrcmp(argv[3], "--sort") == 0) {
                int choice;
                printf("Sort by: 1-Name, 2-Age, 3-Group, 4-GPA: ");
                scanf("%d", &choice);
                if (choice == 1) sortByName(filtered, filter_count);
                else if (choice == 2) sortByAge(filtered, filter_count);
                else if (choice == 3) sortByGroup(filtered, filter_count);
                else if (choice == 4) sortByGPA(filtered, filter_count);
            }
            displayStudents(filtered, filter_count);
            free(filtered);
        }
        else if (myStrcmp(argv[1], "--help") == 0) {
            showHelp();
        }
    }

    saveStudentsToText(students, count);

    for (int i = 0; i < count; i++) freeStudent(&students[i]);
    free(students);
}

void handleParents(int argc, char *argv[])
{
    struct Parent *parents = NULL;
    int count = loadParentsFromText(&parents);

    if (argc == 1) {
        displayParents(parents, count);
    }
    else if (argc > 1) {
        if (myStrcmp(argv[1], "--add") == 0) {
            addParent(&parents, &count);
        }
        else if (myStrcmp(argv[1], "--delete") == 0) {
            char pid[256];
            printf("Enter PID to delete: ");
            scanf("%255s", pid);
            deleteParentByPID(&parents, &count, pid);
        }
        else if (myStrcmp(argv[1], "--sort") == 0) {
            struct Parent *copy = malloc(sizeof(struct Parent) * count);
            if (copy) {
                for (int i = 0; i < count; i++) copy[i] = parents[i];
                int choice;
                printf("Sort by: 1-Name, 2-Age, 3-Student PID: ");
                scanf("%d", &choice);
                if (choice == 1) sortByNameParent(copy, count);
                else if (choice == 2) sortByAgeParent(copy, count);
                else if (choice == 3) sortByStudentPID(copy, count);
                displayParents(copy, count);
                free(copy);
            }
        }
        else if (myStrcmp(argv[1], "--filter") == 0 && argc > 2) {
            char student_pid[256];
            myStrcpy(student_pid, argv[2]);

            int filter_count = 0;
            struct Parent *filtered = malloc(sizeof(struct Parent) * count);
            for (int i = 0; i < count; i++) {
                if (myStrcmp(parents[i].student_pid, student_pid) == 0)
                    filtered[filter_count++] = parents[i];
            }

            if (argc > 3 && myStrcmp(argv[3], "--sort") == 0) {
                int choice;
                printf("Sort by: 1-Name, 2-Age, 3-Student PID: ");
                scanf("%d", &choice);
                if (choice == 1) sortByNameParent(filtered, filter_count);
                else if (choice == 2) sortByAgeParent(filtered, filter_count);
                else if (choice == 3) sortByStudentPID(filtered, filter_count);
            }
            displayParents(filtered, filter_count);
            free(filtered);
        }
        else if (myStrcmp(argv[1], "--help") == 0) {
            showHelp();
        }
    }

    saveParentsToText(parents, count);

    for (int i = 0; i < count; i++) freeParent(&parents[i]);
    free(parents);
}

void handleLinked(int argc, char *argv[])
{
    if (argc < 3) { printf("Usage: --show-linked <PID>\n"); return; }

    char *pid = argv[2];

    struct Student *students = NULL;
    int sc = loadStudentsFromText(&students);
    struct Parent  *parents  = NULL;
    int pc = loadParentsFromText(&parents);

    struct Student *found = NULL;
    for (int i = 0; i < sc; ++i)
        if (myStrcmp(students[i].pid, pid) == 0) { found = &students[i]; break; }

    if (found) {
        printf("=== Student ===\n");
        displaySingleStudent(found);
        printf("\n=== Parents ===\n");
        int fc = 0;
        struct Parent *filtered = malloc(sizeof(struct Parent) * pc);
        for (int i = 0; i < pc; ++i)
            if (myStrcmp(parents[i].student_pid, pid) == 0)
                filtered[fc++] = parents[i];
        if (fc) displayParents(filtered, fc);
        else    printf("No parents found for this student.\n");
        free(filtered);
    } else {
        printf("Student with PID '%s' not found.\n", pid);
    }

    for (int i = 0; i < sc; ++i) freeStudent(&students[i]); free(students);
    for (int i = 0; i < pc; ++i) freeParent(&parents[i]);   free(parents);
}

void handleSearchByParent(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: --search-parent <PARENT_NAME>\n"
               "Example: ./program --search-parent Sabina\n");
        return;
    }
    char *search = argv[2];

    struct Parent  *parents = NULL;
    int pc = loadParentsFromText(&parents);
    struct Student *students = NULL;
    int sc = loadStudentsFromText(&students);

    int found = 0;
    for (int i = 0; i < pc; ++i) {
        if (myStrcmp(parents[i].name, search) != 0) continue;
        found = 1;
        char *spid = parents[i].student_pid;
        struct Student *s = NULL;
        for (int j = 0; j < sc; ++j)
            if (myStrcmp(students[j].pid, spid) == 0) { s = &students[j]; break; }

        printf("=== Parent: %s %s ===\n", parents[i].name, parents[i].surname);
        if (s) { printf("Student:\n"); displaySingleStudent(s); }
        else   { printf("Student with PID '%s' not found.\n", spid); }
        printf("\n");
    }
    if (!found) printf("No parent named '%s' found.\n", search);

    for (int i = 0; i < sc; ++i) freeStudent(&students[i]); free(students);
    for (int i = 0; i < pc; ++i) freeParent(&parents[i]);   free(parents);
}