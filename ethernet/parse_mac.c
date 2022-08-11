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
int main(){
    char * mac_binary_str= "";
}
int mac_to_binary(const char *a, unsigned char *n){
    
}

/**
* 将可读的mac地址转换成二进制地址， a，是可读的mac地址类似：08:00:27:c8:04:83
*/
int mac_aton(const char *a, unsigned char *n) {
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