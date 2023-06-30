#ifndef TLB_H
#define TLB_H
#include "common.h"
#include <stdbool.h>
struct tlbEntry
{
    unsigned int pageNumber;
    unsigned int frameNumber;
    struct tlbEntry *next;
};
/*
    Inicializa el buffer TLB
    Debe invocarse antes de llamar a cualquier método accesorio
    Retorna true si la inicialización fue exitosa}
*/
bool initTlb();
/*
    Determina si existe una página en la tabla TLB
    Si existe, retorna el número del frame, si no, devuelve el valor SENTINEL
*/
unsigned int getFrameFromTLB(unsigned int pageNumber);
/*
    Insertar un valor en el buffer TLB utilizando el algoritmo de sustitución FIFO
*/
void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber);
/*
    Quitar una página del buffer TLB
*/
void invalidatePageTLB(unsigned int pageNumber);
/*
    Desasigna los recursos al buffer TLB
*/
void freeTLB();
/*
    Imprime el buffer TLB, utilizado para la depurar el código
*/
void printTLB();
#endif