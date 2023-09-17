; 在数据段存储斐波那契数列的前20项

DATA SEGMENT
    DW 1, 1, 18 DUP (0)   ; 提示: 18 DUP (0) 表示后面18个单元全部为0的意思
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    MOV BX, 4

    MOV CX, 18        ; 循环 18 次

S:
    MOV AX, [BX-2]
    ADD AX, [BX-4]
    MOV [BX], AX
    ADD BX, 2
    LOOP S

    MOV AX, 4C00H
    INT 21

CODE ENDS

    END START