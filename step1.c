#include <stdio.h>
#include <argp.h>

static int parse_opt (int key, char *arg, struct argp_state *state){
  switch (key){
        case 'd': printf (".\n"); break;
    }
  return 0;
}

int main (int argc, char **argv){
    // 声明了结构体数组, argp_option 是结构体的名称
    struct argp_option options[] = {
      // 第一个选项 ，操作符是d， Show a dot on the screen是提示, 输入-- help的时候
      // 0 就表示对应的选项还没有开始使用。
        { 0, 'd', 0, 0, "Show a dot on the screen"},
      // 一个空的终止记录
        { 0 }
    };

    struct argp argp = { options, parse_opt };
    return argp_parse (&argp, argc, argv, 0, 0, 0);
}
