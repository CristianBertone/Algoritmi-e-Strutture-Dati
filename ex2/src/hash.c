#include "../include/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define INITIAL_CAPACITY 1024
#define LOAD_FACTOR_THRESHOLD 0.75


// La struttura principale della HashTable
// Scegliamo una capacità di default. Una tabella hash reale
// dovrebbe avere un meccanismo di "resizing", ma la specifica
// non lo chiede e non vogliamo complicare troppo.
// Scegliamo un numero primo per buone performance.


// --- Implementazione delle Funzioni ---
// Funzione interna per raddoppiare la tabella quando si riempie
static void resize_table(HashTable* ht) {
    int old_capacity = ht->capacity;
    HashEntry** old_buckets = ht->buckets;

    ht->capacity = old_capacity * 2;
    ht->buckets = (HashEntry**)calloc(ht->capacity, sizeof(HashEntry*));
    if (!ht->buckets) {
        ht->capacity = old_capacity;
        ht->buckets = old_buckets;
        return;
    }

    for (int i = 0; i < old_capacity; i++) {
        HashEntry* entry = old_buckets[i];
        while (entry != NULL) {
            HashEntry* next = entry->next;
            unsigned long hash = ht->hash_function(entry->key);
            int index = hash % ht->capacity;

            entry->next = ht->buckets[index];
            ht->buckets[index] = entry;

            entry = next;
        }
    }
    free(old_buckets);
}

HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*)) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->capacity = INITIAL_CAPACITY;
    ht->count = 0;
    ht->compare_function = f1;
    ht->hash_function = f2;

    ht->buckets = (HashEntry**)calloc(ht->capacity, sizeof(HashEntry*));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    return ht;
}

void hash_table_put(HashTable* ht, const void* key, const void* value) {
    if (!ht || !key) return;

    // Controlla se superiamo la soglia del fattore di carico (es. 75%)
    if ((float)ht->count / ht->capacity >= LOAD_FACTOR_THRESHOLD) {
        resize_table(ht);
    }

    // 1. Calcola l'indice del bucket
    unsigned long hash = ht->hash_function(key);
    int index = hash % ht->capacity;

    // 2. Cerca la chiave nel bucket (lista)
    HashEntry* entry = ht->buckets[index];
    while (entry != NULL) {
        if (ht->compare_function(entry->key, key) == 0) {
            // Chiave trovata! Sovrascrivi il valore e esci.
            entry->value = (void*)value;
            return;
        }
        entry = entry->next;
    }

    // 3. Chiave non trovata: crea un nuovo nodo
    HashEntry* new_entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (!new_entry) return;

    new_entry->key = (void*)key;
    new_entry->value = (void*)value;
    
    // 4. Inseriscilo in testa alla lista del bucket
    new_entry->next = ht->buckets[index];
    ht->buckets[index] = new_entry;
    
    ht->count++;
}

void* hash_table_get(const HashTable* ht, const void* key) {
    if (!ht || !key) return NULL;

    unsigned long hash = ht->hash_function(key);
    int index = hash % ht->capacity;

    HashEntry* entry = ht->buckets[index];
    while (entry != NULL) {
        if (ht->compare_function(entry->key, key) == 0) {
            return entry->value; // Trovato!
        }
        entry = entry->next;
    }

    return NULL; // Non trovato
}

int hash_table_contains_key(const HashTable* ht, const void* key) {
    // Semplice: riutilizziamo hash_table_get
    return (hash_table_get(ht, key) != NULL);
}

void hash_table_remove(HashTable* ht, const void* key) {
    if (!ht || !key) return;

    unsigned long hash = ht->hash_function(key);
    int index = hash % ht->capacity;

    HashEntry* entry = ht->buckets[index];
    HashEntry* prev = NULL; // Ci serve il puntatore precedente

    while (entry != NULL) {
        if (ht->compare_function(entry->key, key) == 0) {
            // Trovato! Ora dobbiamo rimuoverlo dalla lista
            if (prev == NULL) {
                // È il primo nodo della lista
                ht->buckets[index] = entry->next;
            } else {
                // È un nodo in mezzo o in fondo
                prev->next = entry->next;
            }
            
            // Libera la memoria del *nodo*, ma non di key e value
            free(entry);
            ht->count--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

int hash_table_size(const HashTable* ht) {
    if (!ht) return 0;
    return ht->count;
}

void** hash_table_keyset(const HashTable* ht) {
    if (!ht || ht->count == 0) return NULL;

    // 1. Alloca l'array per contenere 'count' puntatori a chiavi
    void** keys = (void**)malloc(ht->count * sizeof(void*));
    if (!keys) return NULL;

    int k_idx = 0; // Indice per l'array 'keys'

    // 2. Itera su tutti i bucket
    for (int i = 0; i < ht->capacity; i++) {
        HashEntry* entry = ht->buckets[i];
        // 3. Itera su tutta la lista di quel bucket
        while (entry != NULL) {
            keys[k_idx] = entry->key;
            k_idx++;
            entry = entry->next;
        }
    }

    return keys;
}

void hash_table_free(HashTable* ht) {
    if (!ht) return;

    // 1. Itera su tutti i bucket
    for (int i = 0; i < ht->capacity; i++) {
        HashEntry* entry = ht->buckets[i];
        // 2. Libera tutti i nodi in ogni lista
        while (entry != NULL) {
            HashEntry* next = entry->next; // Salva il prossimo
            free(entry);                   // Libera il nodo corrente
            entry = next;                  // Passa al prossimo
        }
    }

    // 3. Libera l'array dei bucket
    free(ht->buckets);
    // 4. Libera la struttura manager
    free(ht);
}

