; 找出符合条件数据并进行统计--以统计负数为例
assume cs:code, ds:data
data segment
    array db 2, -3, 5, -7, 6, -9, -5, 8
    count db 0  ; 统计负数个数
data ends

code segment
start:
    mov ax, data
    mov ds, ax

    call func

    mov ax, 4c00h
    int 21h

; 功能：统计数组中负数的个数
; 输入：array
; 输出：count
func proc
    mov cx, 8
    mov si, 0
    mov di, 0

    mov bl, 0  ; 统计个数
s:
    mov al, array[si]
    cmp al, 0
    jl true  ; array[si] < 0
    jmp next

true:
    inc bl

next:
    inc si
    loop s

    mov count[di], bl
    ret
func endp
code ends
end start