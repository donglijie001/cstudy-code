# cmovtest.s an example of the CMOV instructions
.section .data
output:
    .asciz "The largest value is %d\n"
values:
    .int 105, 235, 61, 315, 134, 221, 53, 145, 117, 5
.section .text
.globl _start
_start:
  nop
  # 把数组的第一个元素赋值给ebx寄存器
  movl values, %ebx
  # edi寄存器存储遍历values数组的索引
  movl $1, %edi
loop:
    movl values(, %edi, 4) , %eax # 依次把 values数组的元素给放到eax寄存器里
    cmp %ebx, %eax # 把eax中的值和ebx中的值进行比较
    cmova %eax, %ebx # 如果eax中的值大于ebx中的值，就把eax的值赋值给ebx寄存器
    inc %edi # 增加edi寄存器中索引的值
    cmp $10, %edi # 比较edi 和10
    jne loop # 跳出循环
pushl %ebx # 下面的这些是打印和退出语句。
pushl $output
call printf
addl $8, %esp
pushl $0
call exit