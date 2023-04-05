#cpuid.s Sample program to extract the processor Vendor ID
.section .data
output:
# x是占位符，从处理器获得厂商ID字符串时，会把它放到对应的内存中
    .ascii "The processor Vendor ID is 'xxxxxxxxxxxx'\n"
.section .text
.global _start
_start:
# 给eax寄存器加载零值
    movl $0, %eax
    cpuid
#创建一个指针，把output标签的内存位置加载到EDI寄存器里。
movl $output,%edi
movl %ebx,28(%edi)
movl %edx,32(%edi)
movl %ecx,36(%edi)
movl $4, %eax
movl $1, %ebx
movl $output,%ecx
movl $42,%edx 
int $0x80
movl $1, %eax 
movl $0, %ebx
int $0x80