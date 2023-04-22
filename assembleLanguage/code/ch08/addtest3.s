# addtest3.s - An example of detecting a carry condition
.section .text
.globl _start
_start:
    nop
    movl $0, %ebx
    movb $190, %bl
    # 下面这行会导致溢出
    # movb $100, %al
    movb $10, %al
    addb %al, %bl
    jc over
    movl $1, %eax
    int $0x80
over:
    movl $1, %eax
    movl $0, %ebx
    int $0x80