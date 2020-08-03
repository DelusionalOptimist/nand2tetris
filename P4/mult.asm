// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
  @R0
  D=M
  @n1
  M=D
  @R1
  D=M
  @n2
  M=D
  @i
  M=1
  @sum
  M=0
  @R2
  M=0
(LOOP)
  @i
  D=M
  @n2
  D=D-M
  @STOP
  D;JGT
  @i
  M=M+1
  @n1
  D=M
  @sum
  M=M+D
  @LOOP
  0;JMP
(STOP)
  @sum
  D=M
  @R2
  M=D
(END)
  @END
  0;JMP
