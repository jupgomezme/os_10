CC = gcc
SRC_DIR = ./src
FLAGS = -Wall -Wextra
FLAG_PARA_EVITAR_ERROR = -Wl,--allow-multiple-definition

all: $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c $(SRC_DIR)/memory.c
	@mkdir -p ./bin
	@rm ./bin/a.out || true
	$(CC) $(FLAGS) $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c $(SRC_DIR)/memory.c -o ./bin/a.out $(FLAG_PARA_EVITAR_ERROR)
