#include <stdio.h>
/* 当 fahr=0，20，… ，300 时，分别
打印华氏温度与摄氏温度对照表 以逆序 */
main()
{
int fahr;
for (fahr = 300; fahr >= 0; fahr = fahr - 20)
printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}