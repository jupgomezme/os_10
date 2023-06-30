#ifndef CONSTANTS_H
#define CONSTANTS_H
#define PAGE_MASK 0b00000000000000001111111100000000
#define OFFSET_MASK 0b00000000000000000000000011111111
#define PAGE_TABLE_SIZE 256
#define PAGE_SIZE 256
#define TLB_SIZE 16
#define SENTINEL (unsigned int)-1
// Utiliza 128 frames para que la memoria física sea la mitad del tamaño de la virtual
#define FRAMES 128
#endif