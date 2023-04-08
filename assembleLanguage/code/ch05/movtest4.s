#movtest3.s An example of indirect addressing
.section .data
output:
    .asciz "The vlaue is%d\n"
values:
	.int 10,15,20,25,30,35,40,45,50,55,60
.section .text
.globl _start
_start:
    nop
# 把vlaues 数组的第一个元素赋值给eax寄存器中
movl values, %eax
# 把values在内存中的地址给放到edi寄存器中
movl $values, %edi
movl $100, 4(%edi)
movl $1, %edi
movl values(,%edi, 4), %ebx
movl $1, %eax
int $0x80
    
        