#subtest1.s -An example of the SUB instruction
.section .data
data:
    .int 40
.section .text
.globl _start
_start:
    nop 
    movl $0, %eax
    movl $0, %ebx
    movl $0, %ecx
    movb $20, %al
    subb $10, %al # 此时寄存器的值就是10
    movsx %al, %eax # 把al寄存器的值放到eax寄存器
    movw $100, %cx # 把100给放到cx寄存器中
    subw  %cx,%bx  # bx原来是0， 减去100，就是-100
    movsx %bx, %ebx
    movl $100,%edx
    subl %eax,%edx
    subl data, %eax
    subl %eax,data
    movl $1,%eax
    movl $0,%ebx
    int $0x80