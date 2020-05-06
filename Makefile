EXE := filebrowser

SRC_DIR := src
OBJ_DIR := obj

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC := gcc

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = -lm `pkg-config --libs gtk+-3.0`

CPPFLAGS := -Iinclude
CFLAGS   := -g -Wall -std=c99 $(GTK_CFLAGS)
LDFLAGS  := -Llib
LDLIBS   := $(GTK_LIBS)


.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean:
	$(RM) $(OBJ)
