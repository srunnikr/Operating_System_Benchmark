CC=gcc
FLAGS=-g -Wall -Wno-unknown-pragmas
LIBS = -lm -pthread
CPU_OUT=run

SRC_DIR=src
INC_DIR=inc
BUILD_DIR=build

SYSCALL_SRC=syscall.c
PROCEDURE_SRC=procedure_call.c
THREADS_SRC=threads.c
PROCESS_SRC=process.c
MAIN_SRC=main.c
UTILS_SRC=utils.c

all: run
	mv run build
	rm -rf build/logs
	rm -rf logs
	mkdir build/logs
	mkdir logs

run: syscall.o procedure_call.o main.o utils.o threads.o process.o
	$(CC) $(FLAGS) -I$(INC_DIR) -o $(CPU_OUT) syscall.o procedure_call.o main.o utils.o threads.o process.o $(LIBS)
	mkdir -p $(BUILD_DIR)
	mv *.o $(BUILD_DIR)
	
syscall.o: $(addprefix $(SRC_DIR)/, $(SYSCALL_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR) $(addprefix $(SRC_DIR)/, $(SYSCALL_SRC)) $(LIBS)
	
procedure_call.o: $(addprefix $(SRC_DIR)/, $(PROCEDURE_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR) $(addprefix $(SRC_DIR)/, $(PROCEDURE_SRC)) $(LIBS)
	
threads.o: $(addprefix $(SRC_DIR)/, $(THREADS_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR) $(addprefix $(SRC_DIR)/, $(THREADS_SRC)) $(LIBS)
	
process.o: $(addprefix $(SRC_DIR)/, $(PROCESS_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR)  $(addprefix $(SRC_DIR)/, $(PROCESS_SRC)) $(LIBS)
	
main.o: $(addprefix $(SRC_DIR)/, $(MAIN_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR) $(addprefix $(SRC_DIR)/, $(MAIN_SRC)) $(LIBS)
	
utils.o: $(addprefix $(SRC_DIR)/, $(UTILS_SRC))
	$(CC) $(FLAGS) -c -I$(INC_DIR) $(addprefix $(SRC_DIR)/, $(UTILS_SRC)) $(LIBS)

clean:
	rm -rf $(CPU_OUT) *.o *.gch
	rm -rf $(BUILD_DIR)
	rm -rf logs
