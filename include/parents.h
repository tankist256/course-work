#ifndef PARENTS_H
#define PARENTS_H

struct Parent {
    char *name;
    char *surname;
    int age;
    char *pid;
    char *email;
    char *phone;
    char *birthdate;
    char *student_pid;
};


int loadParentsFromText(struct Parent **parents);
void saveParentsToText(const struct Parent *parents, int count);
void addParent(struct Parent **parents, int *count);
void deleteParentByPID(struct Parent **parents, int *count, const char *pid);
void displayParents(const struct Parent *parents, int count);
void freeParent(struct Parent *parent);
void sortByNameParent(struct Parent *parents, int count);
void sortByAgeParent(struct Parent *parents, int count);
void sortByStudentPID(struct Parent *parents, int count);

#endif