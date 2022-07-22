#include <stdio.h>
#include <argp.h>
#include <stdlib.h> // 不加这个引用，atoi 会报警
static int parse_opt (int key, char *arg, struct argp_state *state){
  switch (key){
        case 'd': {
            unsigned int i;
            for (i = 0; i < atoi (arg); i++)
                printf ("."); 
            printf ("\n");
            break;
        }
        case 777:
            return parse_opt ('d', "3", state);
        }
  return 0;
}

int main (int argc, char **argv){
    // 声明了结构体数组, argp_option 是结构体的名称
    struct argp_option options[] = {
      // 第一个选项 ，操作符是d， Show a dot on the screen是提示, 输入-- help的时候
      // 0 就表示对应的选项还没有开始使用。
      //它表示此 -d 选项有一个参数，并且该参数在 --help 和 --usage 显示中应称为“NUM”。 如果我们将此值改回 0(或者 NULL)，-d 选项将停止接受强制参数。
        // 这个短选项的参数NUM，是一个强制参数，也就是我们在运行-d这个参数的时候，必须带一个数字，否则会报错
        // argp中第一个字符表示长选项,在选项名中不要添加特殊字符
        // 第四个参数是 表示该参数是可选的。  可以通过使用--usage，来查看选项的使用方法，长选项使用可选参数需要使用 等于号
        /*
        donglijie@code-server-deployment-8556bddcd5-dkpdz:~/personal-work/cstudy-code$ ./step4.o --usage
        Usage: step4.o [-?] [-d[NUM]] [--dot[=NUM]] [--help] [--usage]
        */

        { "dot", 'd', "NUM", 0, "Show a dot on the screen"},
        // 这是一个等效选项，等效于 -d 3 
        { "ellipsis", 777, 0, 0, "Show an ellipsis on the screen"},
      // 一个空的终止记录
        { 0 }
    };

    struct argp argp = { options, parse_opt };
    return argp_parse (&argp, argc, argv, 0, 0, 0);
}
