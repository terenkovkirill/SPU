CC=g++
CFLAGS=-c -Wall -DDEBUG

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
	./Asm.exe PROGRAM_ASM.TXT PROGRAM_CODE.BIN



Proc.exe: Proc.o Stack.o Checkout.o Read.o
	$(CC) Proc.o Stack.o Checkout.o Read.o -o Proc.exe

Proc.o: Proc.cpp Makefile
	$(CC) $(CFLAGS) Proc.cpp

Stack.o: Stack.cpp Makefile
	$(CC) $(CFLAGS) Stack.cpp

Checkout.o: Checkout.cpp Makefile
	$(CC) $(CFLAGS) Checkout.cpp


.PHONY: runProc
runProc: Proc.exe
	./Proc.exe PROGRAM_CODE.BIN Log.txt
