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
void init()
{
    int x, y;

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    empty = 15;
    srand(time(0));
    x = rand() % 4;
    y = rand() % 4;
    a[y][x] = 2;
    draw();
}
void play(){

}
void cnt_value(int *new_y, int *new_x){

}
int game_over(){
    return 0;
}
int cnt_one(int y, int x){
    return 0;
}
void draw()
{
    int n, m, x, y;
    char c[4] = {'0', '0', '0', '0'};
    clear();

    for(n = 0; n < 9; n += 2)   //绘制横线，n代表行，m代表列
    {
        for(m = 0; m < 21; m++)
        {
            move(n, m);
            addch('-');
            refresh();
        }
    }
    for(m = 0; m < 22; m += 5)  //绘制竖线
    {
        for(n = 1; n < 8; n++)
        {
            move(n, m);
            addch('|');
            refresh();
        }
    }
    for(y = 0; y < 4; y++)     //绘制数字
    {
        for(x = 0; x < 4; x++)
        {
            draw_one(y, x);
        }
    }
}
void draw_one(int y, int x)
{
    int i, m, k, j;
    char c[5] = {0x00};
    i = a[y][x];
    m = 0;
    while(i > 0)
    {
        j = i % 10;
        c[m++] = j + '0';
        i = i / 10;
    }
    m = 0;
    k = (x + 1) * 5 - 1;
    while(c[m] != 0x00)
    {
        move(2*y+1, k);
        addch(c[m++]);
        k--;
    }
}