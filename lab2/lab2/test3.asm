.ORIG	 X3000
	LEA 	R0,VAL
	LDW 	R0,R0,#0
	RSHFL	R1,R0,#4
	AND	R5,R1,R0; 0
	XOR	R6,R1,R0;-1
	LEA 	R0,ZERO
	STW	R5,R0,#0
	LEA     R0,NEG1
        STW     R6,R0,#0
	HALT
VAL	.FILL XF0F0
ZERO	.FILL XF0F0
NEG1	.FILL XF0F0
.END
