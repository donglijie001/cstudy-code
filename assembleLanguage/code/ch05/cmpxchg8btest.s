# cmpxchg8btest.s - An example of using the cmpxchg8b instruction
.section .data
data:   
    .byte 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
# 上面这行代码声明字节值类型的变量，相当于就是1122334455667788
.section .text
.globl _start
_start:
    nop
    movl $0x44332211, %eax #
    movl $0x88776655, %edx
    movl $0x11111111, %ebx
    movl $0x22222222, %ecx
    cmpxchg8b  data 
    movl $0, %ebx
    movl $1, %eax
    int $0x80