/* Adaptado de https://github.com/MitchelPaulin/VirtualMemoryManager*/
#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include "common.h"
//simulacion tamaño memoria
char physicalMemory[FRAMES * PAGE_SIZE] = {};
/* Señala hacia el frame libre actual, una vez que éste sea mayor que el número de frames, necesitamos utilizar un algoritmo de reemplzo de frame */
unsigned int freeFramePointer = 0;
//archivo de filesystem
FILE *backingStore;

//inicializacion memoria
bool initMemory()
{
    //abre el archivo backingStore, rb es para abrir archivos no de texto en modo read
    backingStore = fopen("../backingStore/BACKING_STORE.bin", "rb");
    //si backingStore esta vacio, no se puede abrir y genera un error
    if (backingStore == NULL)
    {
        printf("No se pudo abrir el almacenamiento de respaldo [disco duro]\n");
        exit(0);
    }
    return true;
}

//Obtiene el valor de la memoria fisica en la dirección especificada
char getValueAtPhysicalAddress(unsigned int address)
{
    return physicalMemory[address];
}

//Caso en que frame no este en memoria, se utiliza memoria de respaldo (disco duro)
unsigned int loadValueFromBackingStore(unsigned int frameNumber)
{
    /*
        Aquí se utiliza una política simple para decidir qué frame debe ser sobrescrito. Solo hay que hacer un ciclo y empezar desde el frame cero
        En un sistema multiproceso se requiere una tabla para llevar la cuenta de los frames libres
    */
    unsigned int circularFreeFramePointer = freeFramePointer;
    //cola circular, si el pointer excede el numero de frames, todos los frames estan ocupados y se necesita sobreescribir uno de ellos
    if (freeFramePointer >= FRAMES)
    {
        frameOverwritten = 1;
        circularFreeFramePointer = freeFramePointer % FRAMES;
    }
    else
    {
        //no se sobreescribe
        frameOverwritten = 0;
    }

    // Leyendo desde el almacenamiento de respaldo [Disco duro]
    //Sitúa el puntero de lectura/escritura de un archivo en la posición indicada. void fseek(FILE * handle, int posición, int modo), modo indica desde donde se hace offset
    fseek(backingStore, frameNumber * PAGE_SIZE, SEEK_SET);
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        //fread(puntero a donde se guarda, tamaño de lo que se lee, numero de elementos a ser leido, archivo)
        //lee del archivo y guarda en la direccion correspondiente en el arreglo physicalMemory
        fread(&physicalMemory[circularFreeFramePointer * PAGE_SIZE + i], sizeof(char), 1, backingStore);
    }
    //apunta al siguiente frame libre
    freeFramePointer++;
    //Returns the circularFreeFramePointer, which represents the index of the loaded frame in the physical memory.
    return circularFreeFramePointer;
}

//libera memoria (cierra el lector)
void freeMem()
{
    fclose(backingStore);
}