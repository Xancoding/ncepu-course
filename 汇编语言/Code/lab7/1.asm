assume cs: codesg 
data segment 
    db '1975','1976','1977','1978','1979','1980','1981','1982','1983','1984' 
    db '1985','1986','1987','1988','1989','1990','1991','1992','1993','1994' 
    db '1995' 
    ; 以上是表示 21 年的 21 个字符串 
    
    dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479
    dd 140417, 197514, 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000
    dd 5937000 
    ; 以上是表示 21 年公司总收入的 21 dword 型数据
    
    dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778
    dw 1001, 1442, 2258, 2793, 4037, 5635, 8226, 1542, 14430, 15257 
    dw 17800 
    ;以上是表示 21 年公司雇员人数的 21 word 型数据
    
data ends 
table segment 
    db 21 dup ('year summ ne ?? ')     ; 用字符表示对应格式及其字节数
table ends  

codesg segment 
start:
    mov ax, data    ; data 数据段基址
    mov es, ax

    mov ax, table   ; table 数据段基址
    mov ds, ax
    mov bx, 0       ; 雇员偏移量
    mov si, 0       ; 源地址
    mov di, 0       ; 目的地址

    mov cx, 21      ; 21 年的 21 个字符串 

s:
    mov ax, es:[si]           ; 年份
    mov [di], ax
    mov ax, es:[si+2]
    mov [di+2], ax
    mov byte ptr [di+4], 20h  ; 空格

    mov ax, es:[si+84]           ; 收入
    mov [di+5], ax
    mov ax, es:[si+84+2]
    mov [di+5+2], ax
    mov byte ptr [di+9], 20h     ; 空格 

    sub si, bx                   ; 雇员偏移量
    mov ax, es:[si+168]          ; 收入
    mov [di+10], ax
    mov byte ptr [di+12], 20h    ; 空格 
    add si, bx

    mov ax, es:[si+84]           ; 低 16 位
    mov dx, es:[si+84+2]         ; 高 16 位
    div word ptr [di+10]
    mov [di+13], ax              ; 人均收入
    mov byte ptr [di+15], 20h    ; 空格

    add bx, 2
    add di, 16
    add si, 4
    loop s

    mov ax, 4c00H
    int 21H

codesg ends 
end start