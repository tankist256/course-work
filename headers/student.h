#ifndef STUDENT_H
#define STUDENT_H

#define MAX_GROUP_LEN 20
#define MAX_SEX_LEN 10

typedef struct {
    char *name;         // Dynamically allocated
    char *surname;      // Dynamically allocated
    char group[MAX_GROUP_LEN];
    int parentId;
    char SEX[MAX_SEX_LEN];
    int mobilephone;
    int dateofbirth;
    int anussize;
    int age;
    int id;
} Student;

typedef struct {
    char *name;         // Dynamically allocated
    char *surname;      // Dynamically allocated
    char Sex[MAX_SEX_LEN];
    int mobilephone;
    int dateofbirth;
    int age;
    int id;
} Parents;


/* Функции вывода */
void printStudents(Student students[], int n);
void printParents(Parents parents[], int n);

/* Сортировки студентов */
void sortByAge(Student students[], int n);
void sortByName(Student students[], int n);
void sortBySurname(Student students[], int n);
void sortByGroup(Student students[], int n);
void sortByParentId(Student students[], int n);

/* Сортировки родителей */
void sortParentsByName(Parents parents[], int n);
void sortParentsBySurname(Parents parents[], int n);
void sortParentsByAge(Parents parents[], int n);
void sortParentsById(Parents parents[], int n);

/* Работа с файлами */
void saveStudentsTofile(const char *filename, Student students[], int n);
void saveParentsTofile(const char *filename, Parents parents[], int n);
int loadStudentsFromfile(const char *filename, Student **outStudents, int *outCount);
int loadParentsFromfile(const char *filename, Parents **outParents, int *outCount);

/* Ручные строковые функции */
int myStrCmp(const char *a, const char *b);
int myStrLen(const char *str);
void myStrCpy(char *dest, const char *src);

/* Освобождение памяти */
void freeStudent(Student *s);
void freeStudents(Student *students, int count);
void freeParent(Parents *p);
void freeParents(Parents *parents, int count);
void freeStudent(Student *s);
void freeStudents(Student *students, int count);
void freeParent(Parents *p);
void freeParents(Parents *parents, int count);

/* Фильтры */
void filterStudentsByGroup(Student students[], int n, const char *group, Student **out, int *outN);
void filterStudentsByName(Student students[], int n, const char *name, Student **out, int *outN);
#endif