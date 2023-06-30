#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
/*
    Inicializa la tabla de paginamiento con valores "centinela"
    Debe invocarse antes que cualquier método de la tabla de paginamiento
*/
void initPageTable();
/*
    Buscar el número del frame en la tabla de paginamiento
    Retorna el frame si este es encontrado
*/
int getFramePageTable(unsigned int pageNumber);
/*
    Coloca una pareja: pageNumber, frameNumber en la tabla de paginamiento
*/
void insertIntoPageTable(unsigned int pageNumber, unsigned int frameNumber);
/*
    Saca la primera página de la cola FIFO e invalida el valor de la tabla de paginamiento
    Retorna el número de página que se ha sacado o SENTINEL si no se ha podido sacar ninguna página
*/
unsigned int popPageQueue();
/*
    Imprime la cola de páginas, se utiliza para depurar el código
*/
void printPageQueue();
/*
    Liberar todos los recursos asignados d la tabla de paginamiento
*/
void freePageTable();
#endif