; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11

billions EQU 0
hundredmillions EQU 8
tenmillions EQU 16
millions EQU 24
hundredthousands EQU 32
tenthousands EQU 40
thousands EQU 48
Hundreds EQU 56
Tens 	 EQU 64
Ones 	 EQU 72
LR_Register EQU 80

LCD_OutDec
	 SUB SP, #80
	 STR LR, [SP, #LR_Register]
	 
	 LDR R3,= 1000000000
	 UDIV R1, R0, R3
	 STR R1,[SP,#billions]
	 MUL R1, R1, R3
	 SUB R1, R0, R1
	 
	 LDR R3,= 100000000
	 UDIV R2, R1, R3
	 STR R2,[SP, #hundredmillions]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 10000000
	 UDIV R2, R1, R3
	 STR R2,[SP, #tenmillions]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 1000000
	 UDIV R2, R1, R3
	 STR R2,[SP, #millions]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 100000
	 UDIV R2, R1, R3
	 STR R2,[SP, #hundredthousands]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 10000
	 UDIV R2, R1, R3
	 STR R2,[SP, #tenthousands]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 1000
	 UDIV R2, R1, R3
	 STR R2,[SP, #thousands]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 100
	 UDIV R2, R1, R3
	 STR R2,[SP, #Hundreds]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 
	 LDR R3,= 10
	 UDIV R2, R1, R3
	 STR R2,[SP, #Tens]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 MOV R1, R2
	 STR R2,[SP, #Ones]

	 MOV R1, SP
	 MOV R3, SP
Check_loop
	 LDR R0, [R1]
	 CMP R0, #0
	 BNE Done_check
	 ADD R1, #8
	 SUBS R2, R1, R3
	 CMP R2, #72
	 BEQ Done_check
	 B Check_loop
	 
Done_check
	 LDR R0, [R1]
	 ADD R0, #0x30
	 PUSH {R1, R2, R3, R4}
	 BL ST7735_OutChar
	 POP {R1, R2, R3, R4}
	 ADD R1, #8
	 SUBS R2, R1, R3
	 CMP R2, #72
	 BHI Done_print
	 B Done_check
	 
Done_print
	 
	 LDR LR, [R3, #LR_Register]
	 ADD SP, #80
	 BX LR

;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.01, range 0.00 to 9.99
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.00 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.89 "
;       R0=123,  then output "1.23 "
;       R0=999,  then output "9.99 "
;       R0>999,  then output "*.** "
; Invariables: This function must not permanently modify registers R4 to R11
hundreds EQU 0
tens    EQU 4
ones 	EQU	8
LR_register EQU 16

LCD_OutFix
	 SUB SP, #16
	 STR LR, [SP, #LR_register]
	 MOV R3, #999
	 CMP R0, R3
	 BHI outOfRange
	 
	 MOV R3, #100
	 UDIV R1, R0, R3
	 STR R1,[SP,#hundreds]
	 MUL R1, R1, R3
	 SUB R1, R0, R1
	 
	 MOV R3, #10
	 UDIV R2, R1, R3
	 STR R2,[SP, #tens]
	 MUL R2, R2, R3
	 SUB R2, R1, R2
	 STR R2,[SP, #ones]
	 
	 LDR R0,[SP,#hundreds]
	 ADD R0, R0, #0x30
	 BL ST7735_OutChar
	 MOV R0, #0x2E
	 BL ST7735_OutChar
	 LDR R0,[SP,#tens]
	 ADD R0, R0, #0x30
	 BL ST7735_OutChar
	 LDR R0,[SP,#ones]
	 ADD R0, R0, #0x30
	 BL ST7735_OutChar
	 B Done
	 
outOfRange
	 MOV R0, #0x2A
	 BL ST7735_OutChar
	 MOV R0, #0x2E
	 BL ST7735_OutChar
	 MOV R0, #0x2A
	 BL ST7735_OutChar
	 MOV R0, #0x2A
	 BL ST7735_OutChar

Done
	 LDR LR, [SP, #LR_register]
	 ADD SP, #16
     BX   LR
     
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
