CC = gcc
STATIC_PROGRAM = static_program
DYNAMIC_PROGRAM = dynamic_program

SRC_DIR = src
CALC_OPERATIONS_DIR = calc-operations
INCLUDE_DIR = include
LIB_DIR = lib

SRCs = $(wildcard $(SRC_DIR)/*.c)
SRCs_FOR_LIB = $(wildcard $(SRC_DIR)/$(CALC_OPERATIONS_DIR)/*.c)
		
OBJs = $(patsubst %.c, %.o, $(SRCs))
OBJs_FOR_STATIC_LIB = $(patsubst %.c, %_static.o, $(SRCs_FOR_LIB))
OBJs_FOR_DYNAMIC_LIB = $(patsubst %.c, %_dynamic.o, $(SRCs_FOR_LIB))

ALL_OBJS = $(OBJs) $(OBJs_FOR_STATIC_LIB) $(OBJs_FOR_DYNAMIC_LIB)

%.o : %.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@ -g

%_static.o : %.c
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@ -g

%_dynamic.o : %.c
	$(CC) -I$(INCLUDE_DIR) -fPIC -c $< -o $@ -g

all-obj-modules : $(ALL_OBJS)
	@echo "Объектные файлы для статической и динамической библиотек созданы!"

program-with-static-lib : $(OBJs) $(OBJs_FOR_STATIC_LIB)
	@mkdir -p $(LIB_DIR)

	ar rc $(LIB_DIR)/libcalc.a $(OBJs_FOR_STATIC_LIB)
	@echo "Статическая библиотека создана!"

	$(CC) $(OBJs) -o $(STATIC_PROGRAM) -L./lib -lcalc -static
	@echo "Программа, использующая статическую библиотеку, создана!"

program-with-dynamic-lib : $(OBJs) $(OBJs_FOR_STATIC_LIB)
	@mkdir -p $(LIB_DIR)

	$(CC) -shared $(OBJs_FOR_STATIC_LIB) -o $(LIB_DIR)/libcalc.so
	@echo "Динамическая библиотека создана!"

	$(CC) $(OBJs) -o $(DYNAMIC_PROGRAM) -L./lib -lcalc
	@echo "Программа, использующая динамическую библиотеку, создана!"

	@echo "Запуск программы, использующей динамическую библиотеку..."
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(DYNAMIC_PROGRAM)

clean : 
	rm -f $(ALL_OBJS) $(LIB_DIR)/libcalc.a $(STATIC_PROGRAM) $(DYNAMIC_PROGRAM) $(LIB_DIR)/libcalc.so
	@echo "Bce файлы, созданые утилитой make, были удалены!"