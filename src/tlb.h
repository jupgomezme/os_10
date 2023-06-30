#ifndef TLB_H
#define TLB_H
#include "common.h"
//Variables tipo booleanas
#include <stdbool.h>
/*TLB (Translation Lookaside Buffer) is a hardware cache used to speed up virtual memory translation. 
It stores recently accessed virtual-to-physical address mappings, reducing the need to perform full 
memory translations and improving memory access performance.
*/

//Estructura que define una entrada en el tlb (contiene parte de la tabla de paginacion para acceso rapido)
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