#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMESIZE 32
struct student_st{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};
void stu_set(struct student_st *p){
    p ->id = 10011;
    strncpy(p->name, "Alan", NAMESIZE);
    p->math =90;
    p->chinese =98;

}
void stu_show(struct student_st *p){
    printf("%d %s %d %d\n", p->id,p->name,p->math,p->chinese);
}
int main(){
    struct student_st stu;
    stu_set(&stu);
    stu_show(&stu);
   // stu_changename();
    exit(0);
}