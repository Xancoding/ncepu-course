; 编写 code 段中的代码，用 push 指令将a段中 word 数据，逆序存储到b段中
assume cs:code
a segment
dw 1,2,3,4,5,6,7,8
a ends  

b segment
dw 0,0,0,0,0,0,0,0
b ends  

code segment
start:
    mov ax, b
    mov ss, ax
    mov sp, 10H   ; 栈指向 b 的最后

    mov ax, a
    mov ds, ax    ; 数据段指向 a 的开头

    mov bx, 0
    mov cx, 8

s:
    push [bx]
    add bx, 2
    loop s

    mov ax, 4c00H
    int 21H

code ends
end start