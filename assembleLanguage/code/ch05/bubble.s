# bubble.s - An example of the XCHG instruction
.section .data
values:
    .int 105, 235, 61, 315, 134, 221, 53, 145, 117, 5
.section .text
.globl _start
_start:
    movl $values, %esi 
    movl $9, %ecx
    movl $9, %ebx
loop:
    movl (%esi), %eax #把esi寄存器中存储的内存位置传送给eax寄存器，
                      #这里就是把values数组的地址给传送到eax寄存器
    cmp %eax, 4(%esi) 
    jge skip
    xchg %eax, 4(%esi)
    movl %eax, (%esi)
    skip:
        add $4, %esi
        dec %ebx
        jnz loop
        dec %ecx
        jz end
    movl $values, %esi
    movl %ecx, %ebx
    jmp loop
end:
    movl $1, %eax
    movl $0, %ebx
    int $0x80
