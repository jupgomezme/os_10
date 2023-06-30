CC = gcc
SRC_DIR = ./src

#Flags de Warnings extra
FLAGS = -Wall -Wextra

all: $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c $(SRC_DIR)/memory.c
#mkdir crea un directorio, -p crea directorios padres necesarios para cada argumento directorio
	@mkdir -p ./bin
#rm remover ese archivo o no hacer nada
	@rm ./bin/a.out || true
	$(CC) $(FLAGS) $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c $(SRC_DIR)/memory.c -o ./bin/a.out