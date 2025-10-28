DATA SEGMENT
    MSG1 DB "hello$"       ; Define a string ending with '$' (required by INT 21h/09h)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA           ; Load address of DATA segment into AX
    MOV DS, AX             ; Set DS to point to DATA segment

    MOV DX, OFFSET MSG1    ; Load address of MSG1 into DX
    MOV AH, 09H            ; DOS function: display string at DS:DX
    INT 21H                ; Call DOS interrupt to print "hello"

    MOV AH, 4CH            ; DOS function: terminate program
    MOV AL, 004            ; Return code 4 (optional)
    INT 21H                ; Exit program

CODE ENDS
END START
