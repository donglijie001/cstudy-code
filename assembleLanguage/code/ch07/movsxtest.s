# movsxtest.s - An example of MOVZX instruction
.section .text
.global _start
_start:
    nop
    movl $-79, %ecx
    movl $0, %ebx
    movw %cx, %bx
    movsx %cx, %eax
    movl $1,%eax
    movl $0, %ebx
    int $0x80