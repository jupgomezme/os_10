#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
/*
    Implementación de una tabla de paginamiento utilizando la política de sustitución FIFO donde se utilizará una lista encadenada (lista enlazada)
*/
//crea arreglo con el tamaño de pagina maximo
unsigned int pageTable[PAGE_SIZE];

//estructura Nodo que contiene el numero de pagina y apunta al siguiente
struct pageNumberEntry
{
    unsigned int pageNumber;
    struct pageNumberEntry *next;
};

//crea cabeza y cola de la lista 
struct pageNumberEntry *pageHead;
struct pageNumberEntry *pageTail;

//incializacion
void initPageTable()
{
    //al principio todas las entradas tienen valor centinela (no tienen valor asociado)
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        pageTable[i] = SENTINEL;
    }
    //reservar espacio para cabeza y cola
    pageHead = (struct pageNumberEntry *)malloc(sizeof(struct pageNumberEntry));
    pageTail = pageHead;
}

//busca el numero de frame
unsigned int getFramePageTable(unsigned int pageNumber)
{
    //retorna valor en el arreglo. El indice provee el numero de pagina. El valor en el arreglo provee el numero de frame
    return pageTable[pageNumber];
}

//Extrae el primer elemento de la cola y retorna su valor
unsigned int popPageQueue()
{
    //si no esta vacia la cola
    if (pageHead)
    {
        //asigno cual es el numero de pagina de la pagina a invalidar
        unsigned int invalidPage = pageHead->pageNumber;
        //copia de cabeza de la cola
        struct pageNumberEntry *temp = pageHead;
        //quitar la cabeza
        pageHead = pageHead->next;
        free(temp);
        // Página inválida, cambia a valor por defecto
        pageTable[invalidPage] = SENTINEL;
        return invalidPage;
    }

    return SENTINEL;
}

//insercion en la tabla de paginamiento, responde a FIFO
void insertIntoPageTable(unsigned int pageNumber, unsigned int frameNumber)
{
    //asigna el numero de frame en el indice numero de pagina
    pageTable[pageNumber] = frameNumber;
    //asigna el numero de pagina a insertar al numero de pagina de la cola
    pageTail->pageNumber = pageNumber;
    //reserva espacio para la siguiente entrada
    pageTail->next = (struct pageNumberEntry *)malloc(sizeof(struct pageNumberEntry));
    //apunta a espacio reservado
    pageTail = pageTail->next;
    //A la nueva cola se le asigna el valor por defecto
    pageTail->pageNumber = SENTINEL;
}

//impresion
void printPageQueue()
{
    struct pageNumberEntry *temp = pageHead;
    while (temp)
    {
        printf("%u, ", temp->pageNumber);
        temp = temp->next;
    }
    printf("\n");
}

//elimina la tabla de paginamiento
void freePageTable()
{
    struct pageNumberEntry *temp;
    while (pageHead != pageTail)
    {
        temp = pageHead;
        pageHead = pageHead->next;
        free(temp);
    }
    free(pageTail);
}