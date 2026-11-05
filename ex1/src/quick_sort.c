#include "quick_sort.h"

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

size_t partition(char *a, size_t p, size_t r, size_t size, 
                 int (*cmp)(const void*, const void*)) {
    size_t mid = p + (r - p) / 2;
    swap(a + p * size, a + mid * size, size);

    size_t left = p + 1;
    size_t right = r;
    char *pivot = a + p * size;

    while (left <= right) {
        while (left <= r && cmp(a + left * size, pivot) <= 0) left++;
        while (right > p && cmp(a + right * size, pivot) > 0) right--;
        
        if (left < right) {
            swap(a + left * size, a + right * size, size);
            left++;
            right--;
        }
    }
    swap(a + p * size, a + right * size, size);
    return right;
}

/**
 * @brief Funzione di supporto per QuickSort.
 * 
 * @param a Puntatore all'array.
 * @param i Indice di inizio del sottoarray.
 * @param j Indice di fine del sottoarray.
 * @param size Dimensione in byte di un singolo elemento.
 * @param cmp Puntatore alla funzione di comparazione.
 */
static void quick_sort_rec(char *a, size_t i, size_t j, size_t size, 
                           int (*cmp)(const void*, const void*)) {
    if (i < j) {
        size_t p = partition(a, i, j, size, cmp);
        if (p > 0) {
            quick_sort_rec(a, i, p - 1, size, cmp);
        }
        quick_sort_rec(a, p + 1, j, size, cmp);
    }
}

void quick_sort(void *base, size_t n, size_t size, 
                int (*cmp)(const void*, const void*)) {
    if (n > 1) {
        quick_sort_rec((char*)base, 0, n - 1, size, cmp);
    }
}
