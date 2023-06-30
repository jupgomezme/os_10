#include "tlb.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
/*
    Implementation of a TLB using the FIFO replacement policy To this end the implementation will use a linked list
    Implementación de un TLB (buffer de memoria asociativa) utilizando la política de sustitución FIFO donde se utilizará una lista encadenada (lista enlazada)
*/
//define cabeza y cola de la lista simplemente encadenada 
struct tlbEntry *tlbHead;
struct tlbEntry *tlbTail;
//al inicio el TLB no esta incializado
bool initialized = false;
//Al inicio el tlb esta vacio
int TLBSize = 0;

//Inicializa TLB, retorna true si es exitoso
bool initTlb()
{
    /*
        Protección contra la inicialización múltiple
    */
    if (initialized)
    {
        return false;
    }
    //flag para saber si esta inicializado
    initialized = true;

    // Crea una lista encadenada de bloques del buffer TLB
    tlbHead = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));   //reserva espacio para la cabeza
    tlbTail = tlbHead;

    for (int i = 0; i < TLB_SIZE - 1; i++)
    {
        tlbTail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tlbTail = tlbTail->next;
        tlbTail->frameNumber = SENTINEL;
        tlbTail->pageNumber = SENTINEL;
    }
    tlbTail->next = NULL;
    return true;
}

//revisa si existe pagina en tlb
unsigned int getFrameFromTLB(unsigned int pageNumber)
{
    //se inicia con la cabeza de la lista
    struct tlbEntry *temp = tlbHead;
    //mientras haya entrada siguiente, se examina las paginas para revisar si coinciden
    do
    {
        //si el pageNumber es el buscado se retorna el numero de frame del tlbEntry actual
        if (temp->pageNumber == pageNumber)
        {
            return temp->frameNumber;
        }
        //examina siguiente
        temp = temp->next;
    } while (temp);
    // TLB miss
    return SENTINEL;
}

//Insertar un valor en el buffer TLB utilizando el algoritmo de sustitución FIFO
void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber)
{
    //Si TLB no supera tamaño maximo
    if (TLBSize < TLB_SIZE)
    {
        // Aún hay espacios vacíos en el buffer TLB, se debe encontrar un lugar para insertar el valor
        //recorre Tlb hasta encontrar un lugar vacio
        struct tlbEntry *temp = tlbHead;
        do
        {
            //si esta disponible el espacio para entrada de tlb, se asigna
            if (temp->pageNumber == SENTINEL)
            {
                temp->pageNumber = pageNumber;
                temp->frameNumber = frameNumber;
                break;
            }
            //si no, examinar siguiente
            temp = temp->next;
        } while (temp);
        //actualiza tamaño tlb
        TLBSize++;
    }
    else
    {
        // El buffer TLB está lleno, se saca de la cola y se crea un nuevo buffer TLB en tlbHead
        //quita la cabeza de la cola
        struct tlbEntry *temp = tlbHead;
        tlbHead = tlbHead->next;
        free(temp);
        //añade espacio al final de la lista
        tlbTail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tlbTail = tlbTail->next;
        tlbTail->frameNumber = frameNumber;
        tlbTail->pageNumber = pageNumber;
        tlbTail->next = NULL;
    }
}

//Quitar una página del buffer TLB
void invalidatePageTLB(unsigned int p)
{
    struct tlbEntry *temp = tlbHead;
    //recorre la lista
    while (temp)
    {
        //si el numero de pagina es igual al parametro, se elimina la asignacion pageNumber-frameNumber
        if (temp->pageNumber == p)
        {
            temp->pageNumber = SENTINEL;
            temp->frameNumber = SENTINEL;
            TLBSize--; // Decrementa el tamaño para que se pueda insertar un nuevo valor en este lugar
            return;
        }
        temp = temp->next;
    }
}

//imprime el buffer TLB
void printTLB()
{
    struct tlbEntry *temp = tlbHead;
    //recorre tlb
    while (temp)
    {
        //imprime el numero de pagina y el numero de frame correspondiente
        printf("%u %u\n", temp->pageNumber, temp->frameNumber);
        temp = temp->next;
    }
}

//Desasigna los recursos al buffer TLB
void freeTLB()
{
    struct tlbEntry *temp;
    //recorre tlb a excepcion de la cola
    while (tlbHead->next)
    {
        //quita la cabeza cada vez
        temp = tlbHead;
        tlbHead = tlbHead->next;
        free(temp);
    }
    //remueve la cabeza que queda
    free(tlbHead);
    //actualiza flag de inicializacion
    initialized = false;
}