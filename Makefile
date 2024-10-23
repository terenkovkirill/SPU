CC=g++
CFLAGS=-c -Wall 

.PHONY: build
build: main.exe ASM.exe


ASM.exe: ASM.o 
	$(CC) ASM.o -o ASM.exe

ASM.o: ASM.cpp Makefile
	$(CC) $(CFLAGS) ASM.cpp

.PHONY: runASM
runASM: ASM.exe
	./ASM.exe PROGRAM_ASM.TXT PROGRAM_CODE.TXT



main.exe: main.o Stack.o Checkout.o
	$(CC) main.o Stack.o Checkout.o -o main.exe

main.o: main.cpp Makefile
	$(CC) $(CFLAGS) main.cpp

Stack.o: Stack.cpp Makefile
	$(CC) $(CFLAGS) Stack.cpp

Checkout.o: Checkout.cpp Makefile
	$(CC) $(CFLAGS) Checkout.cpp

.PHONY: runMain
runMain: main.exe
	./main.exe PROGRAM_CODE.TXT Log.txt
