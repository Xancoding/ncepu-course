; 将“mov ax,4c00h”之前的指令复制到内存0:200处
assume cs: code
code segment
start:
    mov ax, cs         ; 注意在EMU8086中写mov ax, cs执行，但是写mov ax, code则不执行；在VSCode 中两个都执行，课件P13
    mov ds, ax
    mov ax, 0020H           
    mov es, ax
    mov bx, 0
    mov cx, 0017H        
s:
    mov al, [bx]
    mov es:[bx], al
    inc bx
    loop s  
    
    mov ax, 4c00h
    int 21h
code ends     
    end start