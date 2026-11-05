#include "selection_sort.h"

/**
 * @brief Scambia due elementi all'interno di un array.
 * 
 * @param a Puntatore al primo elemento.
 * @param b Puntatore al secondo elemento.
 * @param size Dimensione dell'elemento.
 */
static void swap(void *a, void *b, size_t size) {
    char *ptr_a = (char *)a;
    char *ptr_b = (char *)b;
    for (size_t k = 0; k < size; k++) {
        char tmp = ptr_a[k];
        ptr_a[k] = ptr_b[k];
        ptr_b[k] = tmp;
    }
}

/**
 * @brief Cerca l'indice dell'elemento minimo in una porzione di array.
 * 
 * @param array Puntatore all'inizio dell'array.
 * @param start Indice da cui far partire la ricerca.
 * @param n Dimensione totale dell'array.
 * @param size Dimensione in byte di un singolo elemento.
 * @param cmp Puntatore alla funzione di comparazione.
 * @return Indice in cui si trova l'elemento minimo.
 */
static size_t find_minimum(char *array, size_t start, size_t n, size_t size, 
                           int (*cmp)(const void*, const void*)) {
    size_t min = start;
    for (size_t k = start + 1; k < n; k++) {
        if (cmp(array + k * size, array + min * size) < 0) {
            min = k;
        }
    }
    return min;
}

void selection_sort(void *base, size_t n, size_t size, 
                    int (*cmp)(const void*, const void*)) {
    char *array = (char *)base;
    
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
            size_t min = find_minimum(array, i, n, size, cmp);
            if (min != i) {
                swap(array + min * size, array + i * size, size);
            }
        }
    }
}
