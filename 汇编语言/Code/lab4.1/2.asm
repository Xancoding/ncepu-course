; 将字数据，累加求和

DATA SEGMENT
    DW 1, 3, 5, 7, 9, 11, 13, 15, 17, 19
DATA ENDS

CODE SEGMENT 
    ASSUME CS: CODE, DS: DATA

START:
    MOV  AX, DATA
    MOV  DS, AX

    MOV  AX, 0
    MOV  BX, 0
    MOV  CX, 10

CALC:  
    ADD  AX,  [BX]
    ADD  BX,  2
    LOOP CALC

    MOV  AX, 4C00H
    INT  21H

CODE ENDS

    END START












