#include <stdio.h>
#include <stdlib.h>
#define NAMESIZE 32

struct simp_st{
    int i;
    char ch;
    float f;
};

struct birthday_st{
    int year;
    int month;
    int day;
};
struct student_st{
    int id;
    char name[NAMESIZE];
    struct birthday_st birth;
    int math;
    int chinese;

};
void func(struct simp_st b){
    printf("%d \n", sizeof(b));
}
int main(){
    struct simp_st a;
    struct simp_st *p = &a;
    func(a);
    printf("sizeof(struct) = %d\n", sizeof(a));
#if 0
     struct simp_st a;
     struct simp_st *p = &a;
     printf("sizeof(point) = %d\n", sizeof(p));
     printf("sizeof(struct) = %d\n", sizeof(a));
#endif

    #if 0
    struct simp_st a = {123, 456.789, 'a'};
    a.i =112233;
    printf("%d %f %c\n", a.i,a.f,a.ch);
    #endif
    #if 0
    struct student_st stu = {100011,"Alan",{2011,11,11}, 98,97};
    struct student_st *p= &stu;

    //struct student_st stu = {.math =98}; // 在初始化时指定某个属性的值。
    printf("%d %s %d-%d-%d %d %d \n", stu.id, stu.name, stu.birth.year,
    stu.birth.month, stu.birth.day, stu.math, stu.chinese);
    printf("%d %s %d-%d-%d %d %d \n", p->id, p->name, p->birth.year,
    p->birth.month, p->birth.day, p->math, p->chinese);
    #endif
    exit(0);
}