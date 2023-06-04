#include <stdio.h>
#include <stdlib.h>

struct {
    int i;
    char ch;
    union {
        int a;
        char c;

    }un;
    float f;
};
