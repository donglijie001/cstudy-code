#include <stdio.h>
/* count lines in input */
main()
{
int c;
while ((c = getchar()) != EOF){
    if(c=='\t'){
       printf("\\t");
    }else if(c=='\b'){
       printf("\\b");

    }else{
        putchar(c);
    }
    
}

}