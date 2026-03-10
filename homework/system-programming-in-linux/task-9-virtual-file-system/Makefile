CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
LDFLAGS = -lcurses

TASK_1 = work_with_file
TASK_2 = custom_mc

SRCDIR_TASK_1 = ./src/task-1
SRCDIR_TASK_2 = ./src/task-2
OBJDIR = ./obj
INCDIR = ./include

SOURCES_1 = $(wildcard $(SRCDIR_TASK_1)/*.c)
SOURCES_2 = $(wildcard $(SRCDIR_TASK_2)/*.c)

OBJECTS_1 = $(patsubst $(SRCDIR_TASK_1)/%.c, $(OBJDIR)/task1_%.o, $(SOURCES_1))
OBJECTS_2 = $(patsubst $(SRCDIR_TASK_2)/%.c, $(OBJDIR)/task2_%.o, $(SOURCES_2))

HEADERS = $(wildcard $(INCDIR)/*.h)

all: $(TASK_1) $(TASK_2)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TASK_1): $(OBJECTS_1)
	$(CC) $(OBJECTS_1) -o $(TASK_1)

$(TASK_2): $(OBJECTS_2)
	$(CC) $(OBJECTS_2) $(LDFLAGS) -o $(TASK_2)

$(OBJDIR)/task1_%.o: $(SRCDIR_TASK_1)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/task2_%.o: $(SRCDIR_TASK_2)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TASK_1) $(TASK_2)

run1: $(TASK_1)
	./$(TASK_1)

run2: $(TASK_2)
	./$(TASK_2)