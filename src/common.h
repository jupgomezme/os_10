#ifndef COMMON_H
#define COMMON_H
/*
	Retorna el número de página codificado en una dirección virtual
*/
unsigned int getPageNumber(unsigned int virtualAddress);
/*
	Retorna el desplazamiento (offset) de página codificado en una dirección virtual
*/
unsigned int getPageOffset(unsigned int virtualAddress);
/*
	Se coloca en 1 si se sobrescribe un frame en la tabla de paginamiento
	Se coloca a 0 en caso contrario
*/
char frameOverwritten;
#endif