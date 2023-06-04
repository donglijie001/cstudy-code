#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    // 指针数组
    char * name[5] ={"Floww me", "Basic", "Great","Fortran", "Computer"};
    #if 0
    for (int i=0; i<5; i++) {
        puts(name[i]);
    }
    #endif
    int i,j,k;
    for (i =0; i < 5-1;  i++) {
        k = i;
        for (j = i +1; j <5; j++) {
            if (strcmp(name[k], name[j])> 0) {
                k = j;
            }
        }
        if (k !=i) {
            char * tmp = name[i];
            name[i] = name[k];
            name[k] = tmp;
        }
        for (int i=0; i<5; i++) {
        puts(name[i]);
    }
        printf("\n");
    }

    for (int i=0; i<5; i++) {
        puts(name[i]);
    }

    printf("%d", strcmp("Basic", "Computer"));

    exit(0);
}