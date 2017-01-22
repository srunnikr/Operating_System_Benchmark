CC=gcc
FLAGS=-Wall -Wno-unknown-pragmas
CPU_OUT=run

PROCEDURE_SRC=procedure_call.c procedure_call.h
SYSCALL_SRC=syscall.h syscall.c
MAIN_SRC=main.c

all: run

run: syscall.o procedure_call.o main.o
	$(CC) $(FLAGS) -o $(CPU_OUT) syscall.o procedure_call.o main.o
	
syscall.o: $(SYSCALL_SRC)
	$(CC) -c $(SYSCALL_SRC)
	
procedure_call.o: $(PROCEDURE_SRC)
	$(CC) -c $(PROCEDURE_SRC)
	
main.o: $(MAIN_SRC)
	$(CC) -c $(MAIN_SRC)

clean:
	rm -rf $(CPU_OUT) *.o
