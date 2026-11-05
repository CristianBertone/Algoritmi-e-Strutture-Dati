#include <stdlib.h>
#include <stdint.h>
#include "priority_queue.h"


static void pq_swap(PriorityQueue* pq, int i, int j) {
    void* temp = pq->array[i];
    pq->array[i] = pq->array[j];
    pq->array[j] = temp;

    hash_table_put(pq->index_map, pq->array[i], (void*)(intptr_t)(i + 1));
    hash_table_put(pq->index_map, pq->array[j], (void*)(intptr_t)(j + 1));
}

static void heapify_up(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 3; 
        if (pq->compare(pq->array[index], pq->array[parent]) > 0) {
            pq_swap(pq, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(PriorityQueue* pq, int index) {
    while (1) {
        int max_index = index;
        

        for (int i = 1; i <= 3; i++) {
            int child = 3 * index + i;
            if (child < pq->size && pq->compare(pq->array[child], pq->array[max_index]) > 0) {
                max_index = child;
            }
        }
        
        if (max_index != index) {
            pq_swap(pq, index, max_index);
            index = max_index;
        } else {
            break;
        }
    }
}

PriorityQueue* priority_queue_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*)) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) return NULL;

    pq->capacity = 16;
    pq->size = 0;
    pq->compare = f1;
    pq->array = (void**)malloc(pq->capacity * sizeof(void*));
    pq->index_map = hash_table_create(f1, f2);

    if (!pq->array || !pq->index_map) {
        if (pq->array) free(pq->array);
        if (pq->index_map) hash_table_free(pq->index_map);
        free(pq);
        return NULL;
    }
    return pq;
}

int priority_queue_push(PriorityQueue* pq, void* element) {
    if (!pq || !element) return 0;


    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        void** new_array = (void**)realloc(pq->array, pq->capacity * sizeof(void*));
        if (!new_array) return 0;
        pq->array = new_array;
    }

    pq->array[pq->size] = element;
    hash_table_put(pq->index_map, element, (void*)(intptr_t)(pq->size + 1));
    pq->size++;
    
    heapify_up(pq, pq->size - 1);
    return 1;
}

int priority_queue_contains(const PriorityQueue* pq, const void* element) {
    if (!pq || !element) return 0;
    return hash_table_get(pq->index_map, element) != NULL;
}

void* priority_queue_top(const PriorityQueue* pq) {
    if (!pq || pq->size == 0) return NULL;
    return pq->array[0];
}

void priority_queue_pop(PriorityQueue* pq) {
    if (!pq || pq->size == 0) return;
    
    hash_table_remove(pq->index_map, pq->array[0]);
    pq->size--;
    
    if (pq->size > 0) {
        pq->array[0] = pq->array[pq->size];
        hash_table_put(pq->index_map, pq->array[0], (void*)(intptr_t)1);
        heapify_down(pq, 0);
    }
}

int priority_queue_remove(PriorityQueue* pq, const void* element) {
    if (!pq || !element) return 0;
    
    void* val = hash_table_get(pq->index_map, element);
    if (!val) return 0;
    
    int index = (int)(intptr_t)val - 1;
    hash_table_remove(pq->index_map, element);
    

    if (index == pq->size - 1) {
        pq->size--;
        return 1;
    }


    pq->array[index] = pq->array[pq->size - 1];
    hash_table_put(pq->index_map, pq->array[index], (void*)(intptr_t)(index + 1));
    pq->size--;

    int parent = (index - 1) / 3;
    if (index > 0 && pq->compare(pq->array[index], pq->array[parent]) > 0) {
        heapify_up(pq, index);
    } else {
        heapify_down(pq, index);
    }
    return 1;
}

int priority_queue_size(const PriorityQueue* pq) {
    return pq ? pq->size : 0;
}

void priority_queue_free(PriorityQueue* pq) {
    if (!pq) return;
    hash_table_free(pq->index_map); 
    free(pq->array);                
    free(pq);                       
}