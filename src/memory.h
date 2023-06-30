#ifndef MEMORY_H
#define MEMORY_H
#include "constants.h"
#include <stdbool.h>
/*
    Obtiene el valor en la dirección especificada
*/
char getValueAtPhysicalAddress(unsigned int address);
/*
    Inicializa la memoria
    Debe invocarse antes de llamar cualquier otro método
    Retorna true si la inicialización fue exitosa
*/
bool initMemory();
/*
    Liberar todos los recursos asignados a la memoria principal
*/
void freeMem();
/*
    Si el frame no está actualmente en la memoria, lo carga desde el almacenamiento de respaldo [disco duro]
    Retorna el número del frame en el que se colocó
*/
unsigned int loadValueFromBackingStore(unsigned int frameNumber);
#endif