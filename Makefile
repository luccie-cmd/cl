CC=gcc
CFLAGS=-Wall -Wextra -Wswitch-enum -pedantic -std=c11 -Iinclude
SRC_DIR=./src
ALL_FILES=$(SRC_DIR)/*.c
CASM_FILES=$(SRC_DIR)/casm.c $(SRC_DIR)/compiler.c $(SRC_DIR)/common.c
CLE_FILES=$(SRC_DIR)/cle.c $(SRC_DIR)/emulator.c $(SRC_DIR)/common.c

all: casm cle

casm: $(CASM_FILES)
	$(CC) $(CFLAGS) -o $@ $^

cle: $(CLE_FILES)
	$(CC) $(CFLAGS) -o $@ $^