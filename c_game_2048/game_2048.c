#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
// 游戏主界面是一个 4*4 的 16 宫格，使用二维数组进行表示，用 0 表示空格
int a[4][4] = {0};
// 16 宫格中空格的个数
int empty;
int old_y, old_x;
void draw();  // 用于绘制游戏界面
void play();  // 游戏运行的逻辑主体
void init();  // 初始化函数，用于完成一些必要的初始化操作
void draw_one(int y, int x);  // 绘制单个数字
void cnt_value(int *new_y, int *new_x);
int game_over();  // 结束游戏
int cnt_one(int y, int x);

int main(){
    init();
    play();
    endwin();
    return 0;
}
void init(){
    int x,y;
    initscr();
    cbreak();

}
void play(){

}
void draw_one(int y, int x){

} 
void cnt_value(int *new_y, int *new_x){

}
int game_over(){
    return 0;
}
int cnt_one(int y, int x){
    return 0;
}