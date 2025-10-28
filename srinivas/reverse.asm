DATA SEGMENT
    MSG1 DB "HELLO"
    LEN DW $ - MSG1
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX

    LEA SI, MSG1        ; Load address of MSG1 into SI
    MOV CX, LEN         ; Load length of string into CX
    ADD SI, CX          ; Point SI to end of string
    DEC SI              ; Adjust to last character

REVLOOP:
    MOV DL, [SI]        ; Load character into DL, Copy the byte at memory address pointed to by SI into DL
    MOV AH, 02H         ; DOS function to print character
    INT 21H             ; Call DOS interrupt
    DEC SI              ; Move to previous character
    LOOP REVLOOP        ; Repeat until CX = 0

    MOV AH, 4CH         ; Exit program
    INT 21H

CODE ENDS
END START
