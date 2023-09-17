; 数组累加
assume cs:code, ds:data
data segment
    array db 16, 16, 36, 46, 56, 66, 76, 86
    result dw 0  ; 398--018EH
data ends

code segment
start:
    mov ax, data
    mov ds, ax

    call sum

    mov ax, 4c00h
    int 21h

; 功能：array 数组求和
; 参数：array
; 返回：result 
sum proc 
    mov cx, 8  ; 循环 8 次
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    mov bh, 0
s:
    mov bl, array[si]
    add result[di], bx
    inc si

    loop s

    ret
sum endp

code ends
end start
