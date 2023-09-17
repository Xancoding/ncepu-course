; 调用程序和过程在同一代码段中，则使用NEAR属性
; 调用程序和过程在不同代码段中，则使用FAR属性
; 缺省值为 NEAR
ASSUME CS:CODE, DS:DATA

DATA SEGMENT
  DB 1, 2, 3, 4
DATA ENDS

CODE SEGMENT

MAIN PROC FAR     ; 把主过程看作DOS调用的子进程，定义为FAR属性
    ...
    CALL SUB1     ; 调用子程序SUB1
    ...
    RET           ; 过程返回
MAIN ENDP

SUB1 PROC NEAR    ; 同一代码段调用使用NEAR属性
    ...
    RET           ; 过程返回
SUB1 ENDP         ; 过程结束

CODE ENDS
END MAIN