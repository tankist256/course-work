#ifndef DATABASE_H
#define DATABASE_H

struct Student {
    char *name;
    char *surname;
    int age;
    char *pid;
    char *email;
    char *phone;
    char *birthdate;
    char *group;
    float gpa;
};

int loadStudentsFromText(struct Student **students);
void saveStudentsToText(const struct Student *students, int count);
void addStudent(struct Student **students, int *count);
void deleteStudentByPID(struct Student **students, int *count, const char *pid);
void displayStudents(const struct Student *students, int count);
void displaySingleStudent(const struct Student *student);
void freeStudent(struct Student *student);

#endif