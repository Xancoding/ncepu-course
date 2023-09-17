; 求最大值、最小值、平均值
assume cs:code, ds:data
data segment
    array db 0, 9, 88, 6, 5, 4, 5, 6
    max db 0  ; 88--58H
    min db 0  ; 0 --00H
    ave db 0  ; 15--0FH
    rem db 0  ; 3--03H 余数
    sum dw 0  ; 123--007BH
data ends

code segment
start:
    mov ax, data
    mov ds, ax

    call func1
    call func2
    call func3

    mov ax, 4c00h
    int 21h

; 功能：求最大值(无符号数)
; 参数：array
; 输出：max
func1 proc
    mov cx, 8
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    ; max = array[0]
    mov al, array[si]
    mov max[di], al
s1:
    mov al, array[si]
    cmp al, max[di]
    ja true1  ; al > max
    jmp next1
true1:
    mov max[di], al
next1:
    inc si
    loop s1

    ret
func1 endp

; 功能：求最小值(无符号数)
; 参数：array
; 输出：max
func2 proc
    mov cx, 8
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    mov al, array[si]
    mov min[di], al
s2:
    mov al, array[si]
    cmp al, min[di]
    jb true2  ; al < min
    jmp next2

true2:
    mov min[di], al
next2:
    inc si
    loop s2

    ret
func2 endp

; 注意：div 是无符号除法指令
; 功能：求平均值(无符号数)
; 参数：array
; 输出：ave
func3 proc
    mov cx, 8
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    mov ah, 0
s3:
    mov al, array[si]
    add sum[di], ax
    inc si
    loop s3

    mov ax, sum[di]  ; 被除数
    mov bl, 8        ; 除数
    div bl

    mov ave[di], al  ; 商--平均数
    mov rem[di], ah  ; 余数

    ret
func3 endp

code ends
end start