#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

union test_un{
    struct{
        uint16_t i;
        uint16_t j;
    }x;
    uint32_t y;
}a;

union{
    struct{
        char a:1;
        char b:2;
        char c:1;
    }x;
    char y;
} w;
int main(){
    a.y = 0x11223344;
    printf("%x\n", a.x.i+ a.x.j);
    exit(0);
}