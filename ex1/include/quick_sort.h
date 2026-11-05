#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>

/**
 * @brief Ordina un array utilizzando l'algoritmo QuickSort.
 * 
 * @param base Puntatore al primo elemento dell'array.
 * @param n Numero di elementi dell'array.
 * @param size Dimensione di un singolo elemento.
 * @param cmp Puntatore alla funzione di comparazione.
 */
void quick_sort(void *base, size_t n, size_t size, 
                int (*cmp)(const void*, const void*));

/**
 * @brief divide un array attorno a un pivot centrale.
 * 
 * @param a Puntatore all'inizio dell'array.
 * @param p Indice iniziale della porzione dadividere.
 * @param r Indice finale della porzione da dividere.
 * @param size Dimensione in byte di ciascun elemento.
 * @param cmp Puntatore alla funzione di comparazione.
 * @return Indice del Pivot.
 */
size_t partition(char *a, size_t p, size_t r, size_t size, 
                 int (*cmp)(const void*, const void*));

#endif
