#ifndef HYBRID_SORT_H
#define HYBRID_SORT_H

#include <stddef.h>

/**
 * @brief Ordina un array generico scegliendo tra QuickSort e SelectionSort.
 * 
 * L'algoritmo utilizza QuickSort per dividere l'array. Quando la dimensione
 * di una porzione diventa strettamente minore della soglia k, passa a
 * SelectionSort per ottimizzare i tempi di esecuzione sui piccoli insiemi.
 * 
 * @param base Puntatore al primo elemento dell'array da ordinare.
 * @param n Numero di elementi presenti nell'array.
 * @param size Dimensione di un singolo elemento.
 * @param k Soglia sotto la quale viene utilizzato SelectionSort.
 * @param cmp Puntatore alla funzione di comparazione.
 */
void hybridsort(void *base, size_t n, size_t size, size_t k, 
                int (*cmp)(const void*, const void*));

#endif
