#include "hybrid_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"

/**
 * @brief Esegue la logica ricorsiva dell'ordinamento ibrido.
 * 
 * @param a Puntatore all'inizio dell'array.
 * @param i Indice di inizio del sotto-array.
 * @param j Indice di fine delsotto-array.
 * @param size Dimensione in byte di ciascun elemento.
 * @param k Soglia per passare l'esecuzione a SelectionSort.
 * @param cmp Puntatore alla funzione per comparare.
 */


static void hybrid_rec(char *a, size_t i, size_t j, size_t size, size_t k, 
                       int (*cmp)(const void*, const void*)) {
    size_t n_curr = j - i + 1;

    if (n_curr < k) {
        if (n_curr > 1) {
             selection_sort(a + i * size, n_curr, size, cmp);
        }
        return;
    }
    if (i < j) {
        size_t p = partition(a, i, j, size, cmp);
        if (p > 0) {
            hybrid_rec(a, i,p - 1, size, k, cmp);
        }
        hybrid_rec(a, p + 1, j, size,k, cmp);
    }
}

void hybridsort(void *base, size_t n,size_t size, size_t k, 
                int (*cmp)(const void*, const void*)) {
    if (n > 1) {
        hybrid_rec((char*)base, 0, n - 1, size, k, cmp);
    }
}
