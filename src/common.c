#include "common.h"
#include "constants.h"
//extrae el numero de pagina desde el archivo de prueba
unsigned int getPageNumber(unsigned int virtualAddress)
{
    //se utiliza la mascara para extraer los bits relevantes y se desplazan 8 bits a la derecha para no tener bits extras
    return (virtualAddress & PAGE_MASK) >> 8;
}
//extrae el desplazamiento desde el archivo de prueba
unsigned int getPageOffset(unsigned int virtualAddress)
{
    //se utiliza la mascara para extraer los bits relevantes
    return virtualAddress & OFFSET_MASK;
}