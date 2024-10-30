CC=g++
CFLAGS=-c -Wall 

.PHONY: build
build: Proc.exe Asm.exe


Asm.exe: Asm.o Read.o
	$(CC) Asm.o Read.o -o Asm.exe 

Asm.o: Asm.cpp Makefile
	$(CC) $(CFLAGS) Asm.cpp

Read.o: Read.cpp Makefile
	$(CC) $(CFLAGS) Read.cpp

.PHONY: runAsm
runASM: Asm.exe
	./Asm.exe PROGRAM_ASM.TXT PROGRAM_CODE.TXT



Proc.exe: Proc.o Stack.o Checkout.o Read.o
	$(CC) Proc.o Stack.o Checkout.o Read.o -o Proc.exe

Proc.o: Proc.cpp Makefile
	$(CC) $(CFLAGS) Proc.cpp

Stack.o: Stack.cpp Makefile
	$(CC) $(CFLAGS) Stack.cpp

Checkout.o: Checkout.cpp Makefile
	$(CC) $(CFLAGS) Checkout.cpp

Read.o: Read.cpp Makefile
	$(CC) $(CFLAGS) Read.cpp

.PHONY: runProc
runMain: Proc.exe
	./Proc.exe PROGRAM_CODE.TXT Log.txt
