#include <stdio.h>
/* count lines in input */
main()
{
int c, nl, blank, tabs;
nl = 0;
blank=0;
tabs=0;
while ((c = getchar()) != EOF){
    if (c == '\n'){
        ++nl;
    }
    if(c==' '){
        blank++;
    }
    if(c=='\t'){
        tabs++;
    }
}

printf("enter:%d\n", nl);
printf("blank:%d\n", blank);
printf("tabs:%d\n", tabs);

}