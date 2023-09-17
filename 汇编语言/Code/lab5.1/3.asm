; 实现依次用内存 0:0~0:15 单元中的内容改写程序中的数据，数据的传送用栈来进行。
; 栈空间设置在程序内。
ASSUME CS:CODESG
CODESG SEGMENT
    DW 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H ;10个字单元用作栈空间
    DW 10 DUP (0)
START:
    MOV AX,CS
    MOV SS,AX
    MOV SP,0002H
    
    MOV AX,0
    MOV DS,AX
    MOV BX,0
    MOV CX,8
S:
    PUSH [BX]
    ADD SP, 0004H
    ADD BX,2
    LOOP S
    
    MOV AX, 4C00H
    INT 21H
    CODESG ENDS

END START