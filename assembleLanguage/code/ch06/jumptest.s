# jumptest.s - An example of the jump instruction
.section .text
.globl _start
_start:
    nop
    movl $1, %eax # 把eax 寄存器赋值为1
    jmp overhere  # 进行跳转
    movl $10, %ebx
    int $0x80
overhere:
    movl $20, %ebx # 把ebx赋值为20
    int $0x80