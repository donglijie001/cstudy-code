#include <stdio.h>
/* count lines in input */
main()
{
int c, lastc;
lastc='A';
while ((c = getchar()) != EOF){
    if(c!=' '){
        putchar(c);
    }
    if(c ==' '){
        if(lastc!=' '){
            putchar(c);
        }
    }
    lastc =c;
    
}

}