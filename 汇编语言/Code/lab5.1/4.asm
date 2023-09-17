; (1) CPU执行程序返回前(MOV AX,4C00H执行前)，data段中前两个字分别为 0123H 和 0456H 。
; (2) CPU执行程序，程序返回前，CS=076E，SS=076D，DS=076C
; (3) 设程序加载后，code段的段地址为X，则data段的段地址为X-2H，stack段的段地址为X-1H。


ASSUME CS:CODE,DS:DATA,SS:STACK
DATA SEGMENT
    DW 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H  
DATA ENDS
STACK SEGMENT
    DW 8 DUP(0)                                         
STACK ENDS
CODE SEGMENT
START:
    MOV AX,STACK
    MOV SS,AX
    MOV SP,16
    
    MOV AX,DATA
    MOV DS,AX
    
    PUSH DS:[0]
    PUSH DS:[2]
    POP DS:[2]
    POP DS:[0]
    
    MOV AX,4C00H
    INT 21H
CODE ENDS
END START