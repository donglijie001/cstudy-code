# movzxtest.s - An example of MOVZX instruction
.section .text
.global _start
_start:
    nop
    movl $279, %ecx
    movzx %cl, %ebx
    movl $1,%eax
    int $0x80