CC = gcc
CFLAGS = -Wall -Wextra

TASK_1_PROGRAM = task_1_program
TASK_2_CLIENT = task_2_client
TASK_2_SERVER = task_2_server
TASK_3_PROGRAM = task_3_program

SRC_DIR = ./src
OBJ_DIR = ./obj

TASK_1_SRC = $(wildcard $(SRC_DIR)/task-1/*.c)
TASK_2_SRC = $(wildcard $(SRC_DIR)/task-2/*.c)
TASK_3_SRC = $(wildcard $(SRC_DIR)/task-3/*.c)

OBJ_FOR_1_TASK = $(patsubst $(SRC_DIR)/task-1/%.c, $(OBJ_DIR)/task-1/%.o, $(TASK_1_SRC))
OBJ_FOR_2_TASK = $(patsubst $(SRC_DIR)/task-2/%.c, $(OBJ_DIR)/task-2/%.o, $(TASK_2_SRC))
OBJ_FOR_3_TASK = $(patsubst $(SRC_DIR)/task-3/%.c, $(OBJ_DIR)/task-3/%.o, $(TASK_3_SRC))

OBJ_CLIENT = $(OBJ_DIR)/task-2/client.o
OBJ_SERVER = $(OBJ_DIR)/task-2/server.o

all: $(TASK_1_PROGRAM) $(TASK_2_CLIENT) $(TASK_2_SERVER) $(TASK_3_PROGRAM)

$(TASK_1_PROGRAM): $(OBJ_FOR_1_TASK)
	$(CC) $^ -o $@

$(TASK_2_CLIENT): $(OBJ_CLIENT)
	$(CC) $^ -o $@

$(TASK_2_SERVER): $(OBJ_SERVER)
	$(CC) $^ -o $@

$(TASK_3_PROGRAM): $(OBJ_FOR_3_TASK)
	$(CC) $^ -o $@

$(OBJ_DIR)/task-1/%.o: $(SRC_DIR)/task-1/%.c | $(OBJ_DIR)/task-1
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/task-2/%.o: $(SRC_DIR)/task-2/%.c | $(OBJ_DIR)/task-2
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/task-3/%.o: $(SRC_DIR)/task-3/%.c | $(OBJ_DIR)/task-3
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/task-1 $(OBJ_DIR)/task-2 $(OBJ_DIR)/task-3:
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(TASK_1_PROGRAM) $(TASK_2_CLIENT) $(TASK_2_SERVER) $(TASK_3_PROGRAM)
	@echo "Очистка завершена"