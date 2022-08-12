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

int mac_to_binary(const char *a, unsigned char *n){
    return 0;
}

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
int mac_parse(const char * a,unsigned char *n){
    printf("%s\n",a);

    return 0;
}

int main(){
    char * mac_binary_str= "";
    char* mac_arr="08:00:27:c8:04:83";
    printf("%s\n",mac_arr);
    unsigned char to[6];
    mac_aton(mac_arr,to);
    printf("%d\n",to[0]);
    printf("%d\n",to[1]);
    printf("%d\n",to[2]);
   // mac_parse(mac_arr,to);
}