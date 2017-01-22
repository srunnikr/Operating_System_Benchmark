CC=gcc
FLAGS=-Wall -Wno-unknown-pragmas
CPU_OUT=run

CPU_SRC=procedure_call.c procedure_call.h
SYSCALL_SRC=syscall.h syscall.c

all: run

run: syscall.o procedure_call.o main.o
	$(CC) $(FLAGS) -o $(CPU_OUT) syscall.o procedure_call.o main.o
	
syscall.o: syscall.h syscall.c
	$(CC) -c $(SYSCALL_SRC)
	
procedure_call.o: procedure_call.c procedure_call.h
	$(CC) -c $(CPU_SRC)
	
main.o: main.c
	$(CC) -c main.c

clean:
	rm -rf $(CPU_OUT) *.o
