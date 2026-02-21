TARGET = program
CC = gcc

SRC_DIR = src
INCLUDE_DIR = include

SRCs = $(wildcard $(SRC_DIR)/*.c)
		
OBJs = $(patsubst %.c, %.o, $(SRCs))

$(TARGET) : $(OBJs)
	$(CC) $(OBJs) -o $(TARGET)

%.o : %.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@ -g

clean : 
	rm -f $(TARGET) $(OBJs)