DATA SEGMENT
    LIST DD 00010001H,00020002H ; Two double words (each 4 bytes = 2 words)
    N3 DW ?                     ; Result of lower word addition
    N4 DW ?                     ; Result of upper word addition
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA        ; Load address of DATA segment into AX
    MOV DS, AX          ; Set DS to point to DATA segment

    XOR AX, AX          ; Clear AX (AX = 0000)
    MOV CL, AL          ; Initialize CL = 0 (used as a carry counter)

    MOV AX, [SI]        ; Load lower word of LIST[0] into AX
    ADD AX, [SI+4]      ; Add lower word of LIST[1] to AX
    MOV BX, AX          ; Store result in BX
    MOV N3, BX          ; Save result to N3

    MOV AX, [SI+2]      ; Load upper word of LIST[0] into AX
    ADD AX, [SI+6]      ; Add upper word of LIST[1] to AX
    MOV DX, AX          ; Store result in DX
    MOV N4, DX          ; Save result to N4

    JNC STOP            ; Jump if no carry occurred during last ADD
    INC CL              ; If carry occurred, increment CL

STOP:
    MOV AX, 4CH       ; DOS function to terminate program (AH=4Ch, AL=00)
    INT 21H             ; Call DOS interrupt to exit

CODE ENDS
END START
