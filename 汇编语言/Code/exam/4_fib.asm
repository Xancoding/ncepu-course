; 求斐波那契数列前 20 项
assume cs:code, ds:data
data segment
    array dw 20 dup(0)
data ends

code segment
start:
    mov ax, data
    mov ds, ax

    call func

    mov ax, 4c00h
    int 21h

; 功能：求斐波那契数列前 20 项
; 输出：array
func proc
    mov cx, 18
    mov si, 0

    ; fib[1]=1 && fib[2]=1
    mov word ptr array[si], 1
    add si, 2
    mov word ptr array[si], 1
    add si, 2

s:
    mov ax, array[si-2]
    add ax, array[si-4]

    mov array[si], ax
    add si, 2
    loop s

    ret
func endp
code ends
end start
