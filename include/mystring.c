#include "mystring.h"
#include <stdlib.h>

int myStrcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int myStrlen(const char *s) {
    int len = 0;
    while (*s) {
        len++;
        s++;
    }
    return len;
}

char *myStrcpy(char *dest, const char *src) {
    char *original = dest;
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original;
}

char *myStrdup(const char *s) {
    int len = myStrlen(s);
    char *dup = (char *)malloc(len + 1);
    if (dup) {
        myStrcpy(dup, s);
    }
    return dup;
}