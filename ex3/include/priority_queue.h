#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "hash.h"

typedef struct PriorityQueue {
    void** array;
    int capacity;
    int size;
    int (*compare)(const void*, const void*);
    HashTable* index_map; 
} PriorityQueue;

PriorityQueue* priority_queue_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*));
int priority_queue_push(PriorityQueue* pq, void* element);
int priority_queue_contains(const PriorityQueue* pq, const void* element);
void* priority_queue_top(const PriorityQueue* pq);
void priority_queue_pop(PriorityQueue* pq);
int priority_queue_remove(PriorityQueue* pq, const void* element);
int priority_queue_size(const PriorityQueue* pq);
void priority_queue_free(PriorityQueue* pq);

#endif