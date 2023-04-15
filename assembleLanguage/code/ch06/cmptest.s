# cmptest.s - An example of using the CMP and JGE instruction
.section .text
.globl _start
_start:
    nop 
    movl $15, %eax
    movl $10, %ebx
    cmp %eax, %ebx
    jge greator
    movl $1, %eax
    int $0x80
greator:
    movl $20, %ebx
    movl $1, %eax
    int $0x80