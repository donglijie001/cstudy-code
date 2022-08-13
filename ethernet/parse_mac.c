#include <stdio.h>
#define IS_HEX(c) ( \
    (c) >= '0' && (c) <= '9' || \
    (c) >= 'a' && (c) <= 'f' || \
    (c) >= 'A' && (c) <= 'F' \
)
#define HEX(c) ( \
    ((c) >= 'a') ? ((c) - 'a' + 10) : ( \
        ((c) >= 'A') ? ((c) - 'A' + 10) : ((c) - '0') \
    ) \
)

/**
* 将可读的mac地址转换成二进制地址， a，是可读的mac地址类似：08:00:27:c8:04:83
*/
int mac_aton(const char *a, unsigned char *n) {
    printf("%s\n",a);
    for (int i=0; i<6; i++) {
        // skip the leading ':'
        if (i > 0) {
            // unexpected char, expect ':'
            if (':' != *a) {
                return -1;
            }

            a++;
        }

        // unexpected char, expect 0-9 a-f A-f
        if (!IS_HEX(a[0]) || !IS_HEX(a[1])) {
            return -2;
        }

        *n = ((HEX(a[0]) << 4) | HEX(a[1]));

        // move to next place
        a += 2;
        n++;
    }

    return 0;
}
// 将十六进制mac地址字符串转成数字
int parse_mac_to_num(const char * a,unsigned char *n){
    printf("%s\n",a);
    int matches =  sscanf(a, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", n, n+1, n+2,
                         n+3, n+4, n+5);

    return (6 == matches ? 0 : -1);
}
// 将十进制到mac地址转成十六进制的字符串，中间用冒号分割。
void mac_ntoa(unsigned char *n, char *a) {
    // traverse 6 bytes one by one
    for (int i=0; i<6; i++) {
        // format string
        char *format = ":%02x";

        // first byte without leading `:`
        if(0 == i) {
            format = "%02x";
        }

        // format current byte
        a += sprintf(a, format, n[i]);
    }
}
// n 是一个数组，长度是6，里面存储的是mac地址
void mac_to_binary(unsigned char *n, char *a){
    sprintf(a,"%02x:%02x:%02x:%02x:%02x:%02x",n[0],n[1],n[2],n[3],n[4],n[5]);
}
int main(){
    char * mac_binary_str= "";
    char* mac_arr="08:00:27:c8:04:83";
    //printf("%s\n",mac_arr);
    unsigned char to[6];
    //mac_aton(mac_arr,to);
    parse_mac_to_num(mac_arr,to);
    printf("%d\n",to[0]);
    printf("%d\n",to[1]);
    printf("%d\n",to[2]);
   // mac_parse(mac_arr,to);
   char* mac_arr1="";
   mac_to_binary(to, mac_arr1);
   printf("%s",mac_arr1);
}