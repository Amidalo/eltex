CC = gcc
PROCESS_PROGRAM_1 = first_task
PROCESS_PROGRAM_2 = second_task
PROCESS_PROGRAM_3 = command_interpreter

SRC_DIR = src

SRC_1 = $(SRC_DIR)/task-1.c
SRC_2 = $(SRC_DIR)/task-2.c
SRC_3 = $(SRC_DIR)/command_interpreter.c

OBJ_1 = $(patsubst %.c, %.o, $(SRC_1))
OBJ_2 = $(patsubst %.c, %.o, $(SRC_2))
OBJ_3 = $(patsubst %.c, %.o, $(SRC_3))

OBJs = $(OBJ_1) $(OBJ_2) $(OBJ_3)

%.o : %.c
	$(CC) -c $< -o $@ -g

$(PROCESS_PROGRAM_1): $(OBJ_1)
	$(CC) $(OBJ_1) -o $@

$(PROCESS_PROGRAM_2): $(OBJ_2)
	$(CC) $(OBJ_2) -o $@

$(PROCESS_PROGRAM_3): $(OBJ_3)
	$(CC) $(OBJ_3) -o $@

all : $(PROCESS_PROGRAM_1) $(PROCESS_PROGRAM_2) $(PROCESS_PROGRAM_3)
	@echo "Программы созданы!"

clean : 
	rm -f $(OBJs) $(PROCESS_PROGRAM_1) $(PROCESS_PROGRAM_2) $(PROCESS_PROGRAM_3)
	@echo "Bce файлы, созданые утилитой make, были удалены!"