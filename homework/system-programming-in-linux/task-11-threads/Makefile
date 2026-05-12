CC = gcc
CFLAGS = -Wall -Wextra -I./include
PTFLAGS = -pthread

TARGET = program

SRCDIR = ./src
MODELSDIR = $(SRCDIR)/models
OBJDIR = ./obj
INCDIR = ./include

MAIN_SOURCE = $(wildcard $(SRCDIR)/*.c)
MODELS_SOURCE = $(wildcard $(MODELSDIR)/*.c)
HEADERS = $(wildcard $(INCDIR)/*.h)

MAIN_OBJECT = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(MAIN_SOURCE))
MODELS_OBJECTS = $(patsubst $(MODELSDIR)/%.c, $(OBJDIR)/%.o, $(MODELS_SOURCE))
ALL_OBJECTS = $(MAIN_OBJECT) $(MODELS_OBJECTS)

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(ALL_OBJECTS)
	$(CC) $^ -o $@ $(PTFLAGS)
	@echo "Сборка завершена"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(MODELSDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Очистка завершена"