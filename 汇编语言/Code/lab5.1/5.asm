; 将 a 段和 b 段中的数据依次相加，将结果存到c段中。
assume cs:code
a segment
    db 1,2,3,4,5,6,7,8
a ends
b segment
    db 1,2,3,4,5,6,7,8
b ends
d segment
    db 0,0,0,0,0,0,0,0
d ends
code segment
start:  
    mov ax,a
    mov ds,ax

    mov ax,b
    mov es,ax

    mov dx,0
    mov bx,0
    mov cx,8

s: 
    mov dl, ds:[bx]
    add dl, es:[bx]
    mov ds:[bx+32], dl
    
    inc bx
    loop s
    
    mov ax,4c00h
    int 21h
code ends
end start