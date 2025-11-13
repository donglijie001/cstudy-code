#include <stdio.h>
/* 当 fahr=0，20，… ，300 时，分别
打印摄氏温度与华式温度对照表 */
main()
{
float fahr, celsius;
float lower, upper, step;
lower = 0; /* lower limit of temperatuire scale */
upper = 300; /* upper limit */
step = 20; /* step size */
celsius = lower;
printf("%s\n", "this is title");
while (celsius <= upper) {
fahr = (9.0/5.0) * celsius + 32.0;
printf("%3.0f %6.1f\n", celsius, fahr);
celsius = celsius + step;
}
}