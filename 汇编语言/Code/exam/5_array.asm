; 数组排序、查找、插入、删除
; 为简化程序，该数组元素不重复
assume cs:code, ds:data, ss:stack
data segment
    array db 1, 5, -6, 8, 6, -5, -9, 2
    array_insert db 9 dup(0)  ; 在原数组中插入一个数
    array_delete db 7 dup(0)  ; 在原数组中删除一个数
    index dw 0                ; 所查询数在数组中的下标
data ends

stack segment
    dw 8 dup(0)
stack ends

code segment 
start:
    mov ax, data
    mov ds, ax

    mov ax, stack
    mov ss, ax
    mov sp, 16

    call far ptr func1 

    mov bl, -5
    call far ptr func2

    mov bp, 4  ; 下标
    mov bl, 6  ; 值
    call far ptr func3

    mov bp, 6  ; 下标
    call far ptr func4

    mov ax, 4c00h
    int 21h

code ends

func segment

; 功能：数组排序（升序）有符号数
; 参数：array
; 输出：array_sort
func1 proc far
    mov si, 0
    mov cx, 7  ; 外层循环 8 次

    mov ah, 0
outer:  
    mov al, array[si]  ; si-->外层循环i

    push cx
    mov cx, 7
    sub cx, si
    mov bp, si         ; bp=si+1-->内层循环j
    inc bp
inner:
    cmp al, ds:array[bp]
    jg true  ; al > ds:array[bp]
    jmp next
    
true:
    mov al, ds:array[bp]  ; 更新当前这个循环的最小值al
    mov di, bp            ; di最小值在数组中的下标

next:
    inc bp
    loop inner
    pop cx

    mov al, array[si]
    mov bl, array[di]
    mov byte ptr array[si], bl
    mov array[di], al
    
    inc si
    loop outer

    retf
func1 endp

; 功能：查找值k在数组中的下标
; 参数：bl--值k
; 输出：index(若未找到，下标为-1)
func2 proc far 
    mov cx, 8
    mov si, 0
    mov di, 0
s2:
    cmp bl, array[si]
    je true2  ; 相同，找到下标
    inc si
    loop s2

    mov byte ptr index[di], -1  ; 未找到
    retf

true2:
    mov index[di], si           ; 找到
    retf
func2 endp

; 功能：在下标x处插入值为k的元素
; 参数：bp--下标x；bl--值k；array
; 输出：array_insert
func3 proc far
    mov cx, bp
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    jcxz next3

; 先把前x个数放入新数组
s3:
    mov al, array[si]
    mov array_insert[di], al
    inc si
    inc di
    loop s3

next3:
    mov array_insert[di], bl
    inc di

s3_2:
    cmp si, 8
    je finish
    mov al, array[si]
    mov array_insert[di], al
    inc si
    inc di
    jmp s3_2

finish:
    retf
func3 endp

; 功能：删除下标为k的元素
; 参数：bp--下标k
; 输出：array_delete
func4 proc far
    mov cx, bp
    mov si, 0
    mov di, 0

    jcxz delete

s4:
    mov al, array[si]
    mov array_delete[di], al
    inc si
    inc di
    loop s4

delete:
    inc si

s4_2:
    cmp si, 8
    je finish4
    mov al, array[si]
    mov array_delete[di], al
    inc si
    inc di
    jmp s4_2

finish4:
    retf
func4 endp

func ends

end start
