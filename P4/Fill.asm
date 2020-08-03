// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
  @SCREEN
	D=A
	@addr
	M=D-1
(LOOP)
	@addr
	MD=M+1
	@24576
	D=D-A
	@RESET
	D;JEQ
	@KBD
	D=M
	@WHITE
	D;JEQ
	@addr
	D=M
	@i
	A=D
	M=-1
	@LOOP
	0;JMP
(WHITE)
	@addr
	D=M
	@i
	A=D
	M=0
	@LOOP
	0;JMP
(RESET)
	@SCREEN
	D=A
	@addr
	M=D-1
	@LOOP
	0;JMP
