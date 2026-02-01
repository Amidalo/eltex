TARGET = program
CC = gcc

SRC_DIR = src
TASKS_DIR = src/tasks
LIB_DIR = ../_auxiliary-library/source

SRCs = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(TASKS_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
		
OBJs = $(patsubst %.c, %.o, $(SRCs))

$(TARGET) : $(OBJs)
	$(CC) $(OBJs) -o $(TARGET)

%.o : %.c
	$(CC) -c $< -o $@

clean : 
	rm -f $(TARGET) $(OBJs)