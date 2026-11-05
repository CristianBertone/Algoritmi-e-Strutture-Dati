#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stddef.h>

/**
 * @brief Ordina un array utilizzando l'algoritmo SelectionSort.
 * 
 * @param base Puntatore al primo elemento dell'array da ordinare.
 * @param n Numero di elementi presenti nell'array.
 * @param size Dimensione in byte di un singolo elemento.
 * @param cmp Puntatore alla funzione di comparazione.
 */
void selection_sort(void *base, size_t n, size_t size, 
                    int (*cmp)(const void*, const void*));

#endif
