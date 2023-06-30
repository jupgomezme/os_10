/*
    Original elaborado por Mitchel Paulin
    Marzo 2020
*/
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tlb.h"
#include "pageTable.h"
#include "memory.h"
#include "constants.h"
unsigned int getAddress(unsigned int virtualAddress);
// Seguimiento de las métricas del modelo
int pageFaults = 0;
int addressesTranslated = 0;
int TLBHits = 0;
int frameCollisions = 0;
int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        exit(1);
    }
    const char *fileName = argv[1];
    FILE *fp = fopen(fileName, "r");
    // Asignación de recursos
    initTlb();
    initPageTable();
    initMemory();
    // Traduce cada dirección en el archivo
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        unsigned int mem = atoi(line);
        unsigned int addr = getAddress(mem);
        char result = getValueAtPhysicalAddress(addr);
        printf("Virtual address: %u Physical address: %u Value: %d\n", mem, addr, result);
        addressesTranslated++;
    }
    // Reporta algunas estadísticas
    printf("Number of Translated Addresses = %d\n", addressesTranslated);
    if (addressesTranslated > 0)
    {
        printf("Page Faults = %d\n", pageFaults);
        printf("Page Fault Rate = %lf\n", (double)pageFaults / (double)addressesTranslated);
        printf("TLB Hits = %d\n", TLBHits);
        printf("TLB Hit Rate = %lf\n", (double)TLBHits / (double)addressesTranslated);
        printf("Frame collision rate = %lf\n", (double)frameCollisions / (double)addressesTranslated);
    }
    // Libera los recursos
    fclose(fp);
    freeTLB();
    freePageTable();
    freeMem();
    return 0;
}
/*
    Intenta obtener la dirección física a partir de una dirección virtual mediante

    1. Consulta del buffer TLB
    2. Consulta de la tabla de paginamiento (PageTable)
    3. Si las dos fallan, solicita se lean datos en memoria

    Retorna la dirección de la dirección virtual solicitada en la memoria física
*/
unsigned int getAddress(unsigned int virtualAddress)
{
    const unsigned int pageNumber = getPageNumber(virtualAddress);
    const unsigned int pageOffset = getPageOffset(virtualAddress);
    // Primero consulta el buffer TLB
    unsigned int frame = getFrameFromTLB(pageNumber);
    if (frame == SENTINEL)
    {
        // En caso de fallo, consulta la tabla de paginamiento
        frame = getFramePageTable(pageNumber);
        if (frame == SENTINEL)
        {
            // En caso de fallo, carga desde el almacenamiento de respaldo [dicos duro]
            pageFaults++;
            frame = loadValueFromBackingStore(pageNumber);
            if (frameOverwritten == 1)
            {
                // La carga más reciente provocó la sobreescritura de un frame
                // Limpia la tabla de paginamiento y el buffer TLB
                unsigned int invalidPage = popPageQueue();
                invalidatePageTLB(invalidPage);
                frameCollisions++;
            }
            insertIntoPageTable(pageNumber, frame);
        }
        insertIntoTLB(pageNumber, frame);
    }
    else
    {
        TLBHits++;
    }
    return frame * PAGE_SIZE + pageOffset;
}