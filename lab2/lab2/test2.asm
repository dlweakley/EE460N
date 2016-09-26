.ORIG 	X3000
	LEA	R0,VAL1
	LDW	R1,R0,#0 ;XFF01
	LDB	R2,R0,#1 ;#-1
	LDB	R0,R0,#0 ;#1
	LEA	R4,NOVR
	JSRR	R4
POVR	LEA 	R3,MAX
	LDW	R3,R3,#0
	ADD	R3,R3,R0
	BRn	HERE;CHECK OVERFLOW
NOVR	LEA     R3,MIN
        LDW     R3,R3,#0
        ADD     R3,R3,R2
	BRnz    END;CHECKOVERFLOW
	RET
HERE	LEA	R4,A
	LEA	R5,B
	STB	R2,R4,#0
	STB	R0,R4,#1
	STW	R1,R5,#0				
END	HALT	

VAL1	.FILL	XFF01
MAX	.FILL	#32767
MIN	.FILL	#-32768
A	.FILL	X0;PUT X01FF
B	.FILL	X0;PUT XFF01
.END