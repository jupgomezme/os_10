/* Adaptado de https://github.com/MitchelPaulin/VirtualMemoryManager*/
#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include "common.h"
char physicalMemory[FRAMES * PAGE_SIZE] = {};
/* Señala hacia el frame libre actual, una vez que éste sea mayor que el número de frames, necesitamos utilizar un algoritmo de reeamplzo de frame */
unsigned int freeFramePointer = 0;
FILE *backingStore;
bool initMemory()
{
    backingStore = fopen("../backingStore/BACKING_STORE.bin", "rb");
    if (backingStore == NULL)
    {
        printf("No se pudo abrir el almacenamiento de respaldo [disco duro]\n");
        exit(0);
    }
    return true;
}
char getValueAtPhysicalAddress(unsigned int address)
{
    return physicalMemory[address];
}
unsigned int loadValueFromBackingStore(unsigned int frameNumber)
{
    /*
        Aquí se utiliza una política simple para decidir qué frame debe ser sobrescrito. Solo hay que hacer un ciclo y empezar desde el frame cero
        En un sistema multiproceso se requiere una tabla para llevar la cuenta de los frames libres
    */
    unsigned int circularFreeFramePointer = freeFramePointer;
    if (freeFramePointer >= FRAMES)
    {
        frameOverwritten = 1;
        circularFreeFramePointer = freeFramePointer % FRAMES;
    }
    else
    {
        frameOverwritten = 0;
    }
    // Leyendo desde el almacenamiento de respaldo [Disco duro]
    fseek(backingStore, frameNumber * PAGE_SIZE, SEEK_SET);
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        fread(&physicalMemory[circularFreeFramePointer * PAGE_SIZE + i], sizeof(char), 1, backingStore);
    }
    freeFramePointer++;
    return circularFreeFramePointer;
}
void freeMem()
{
    fclose(backingStore);
}