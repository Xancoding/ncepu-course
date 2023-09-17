; 字符串长度、连接、复制、比较
assume cs:code, ds:data, ss:stack
data segment
    str1 db 'abcdef', 0  ; 字符串通常被定义为一系列连续的字符，以0结尾
    str2 db 'abc', 0
    str3 db 10 dup(0)  ; 连接：str1+str2(6+3+1)
    str4 db 4 dup(0)  ; 复制：str2(3+1)
    len1 db 0  ; 字符串1长度
    len2 db 0  ; 字符串2长度
    result db 0  ; 比较结果：相同为 1，不同为 0
data ends

stack segment
    db 8 dup(0)
stack ends

code segment
start:
    mov ax, data
    mov ds, ax

    mov ax, stack ; 栈初始化
    mov ss, ax
    mov sp, 8

    mov bp, offset str1
    mov bx, offset len1
    call far ptr func1

    mov bp, offset str2
    mov bx, offset len2
    call far ptr func1

    mov bp, offset str1
    mov bx, offset str2
    call far ptr func2

    mov bx, offset str2
    call far ptr func3

    ; 比较结果为相同，result==1
    mov bp, offset str2
    mov bx, offset str4
    call far ptr func4

    mov ax, 4c00h
    int 21h

code ends

; 子程序段
func segment
; 功能：求字符串长度
; 参数：bp -- str所在偏移地址; bx -- len所在偏移地址
; 输出：len
func1 proc far
    mov si, 0  ; 源地址
    mov di, 0  ; 目的地址

    mov ch, 0
s1:
    mov cl, ds:[bp+si]  ; 字符
    jcxz next1
    inc si
    jmp s1

next1:
    mov [bx+di], si

    retf
func1 endp

; 功能：连接
; 参数：bp -- str1所在偏移地址; bx -- str2所在偏移地址; str3 -- str1+str3; len1、len2
; 输出：str3
func2 proc far
    mov si, 0
    mov di, 0

    mov ch, 0
    mov cl, len1[di]
s2_1:
    mov al, ds:[bp+si]  ; 取字符
    mov str3[di], al

    inc si
    inc di
    loop s2_1

    mov si, 0
    mov ch, 0
    push di
    mov di, 0
    mov cl, len2[di]
    pop di
s2_2:
    mov al, [bx+si]  ; 取字符
    mov str3[di], al

    inc si
    inc di
    loop s2_2

    mov byte ptr str3[di], 0  ; 字符串末尾加 0
    retf
func2 endp

; 功能：复制字符串
; 参数：bx -- str; str4 == str
; 输出：str4
func3 proc far
    mov si, 0
    mov di, 0

s3:
    mov cl, [bx+si]  ; 字符串末尾为 0
    jcxz next3

    mov al, [bx+si]  ; 复制
    mov str4[di], al ; 粘贴
  
    inc si
    inc di
    loop s3

next3:
    mov byte ptr str4[di], 0
    retf

func3 endp

; 功能：比较
; 参数：bp--str1; bx--str2
; 输出: result
func4 proc far
    mov si, 0  ; str1 偏移地址
    mov di, 0  ; str2 偏移地址

s4:
    mov al, ds:[bp+si]
    cmp al, [bx+di]
    jz true  ; 对应字符串相同
    jmp nonsame

true:
    cmp byte ptr [bx+di], 0
    jz same  ; 当前位为0，字符串结束
    
    inc si   ; 当前位不为0，继续
    inc di
    jmp s4

same:
    mov di, 0
    mov byte ptr result[di], 1  ; 两字符串相同
    retf

nonsame:
    mov di, 0
    mov byte ptr result[di], 0  ; 两字符串不相同
    retf

func4 endp


func ends

end start
