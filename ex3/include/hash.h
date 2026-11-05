#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h> // Per size_t

// --- Strutture Dati ---

// Struttura interna per un nodo della lista di concatenamento.
// Questa non è esposta direttamente all'utente.
typedef struct HashEntry {
    void* key;
    void* value;
    struct HashEntry* next;
} HashEntry;

// La struttura principale della HashTable
typedef struct HashTable {
    HashEntry** buckets; // Array di puntatori a HashEntry
    int capacity;        // Dimensione dell'array 'buckets'
    int count;           // Numero di elementi (coppie K,V) inseriti
    
    // Puntatori alle funzioni fornite dall'utente
    int (*compare_function)(const void*, const void*);
    unsigned long (*hash_function)(const void*);
} HashTable;


// --- Prototipi di Funzione (come da specifica) ---

/**
 * Crea e inizializza una nuova HashTable.
 * f1: Puntatore a funzione per confrontare due chiavi (deve restituire 0 se uguali).
 * f2: Puntatore a funzione per calcolare l'hash di una chiave.
 * Restituisce un puntatore alla nuova HashTable.
 */
HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*)); 

/**
 * Inserisce una coppia (chiave, valore) nella tabella.
 * Se la chiave esiste già, il valore precedente viene sovrascritto.
 */
void hash_table_put(HashTable* ht, const void* key, const void* value); 

/**
 * Recupera il valore associato a una chiave.
 * Restituisce il valore, o NULL se la chiave non è presente.
 */
void* hash_table_get(const HashTable* ht, const void* key); 

/**
 * Controlla se una chiave è presente nella tabella.
 * Restituisce 1 (vero) se la chiave esiste, 0 (falso) altrimenti.
 */
int hash_table_contains_key(const HashTable* ht, const void* key); 

/**
 * Rimuove la coppia (chiave, valore) dalla tabella.
 * ATTENZIONE: non libera la memoria della chiave o del valore.
 */
void hash_table_remove(HashTable* ht, const void* key);

/**
 * Restituisce il numero di coppie (chiave, valore) presenti nella tabella.
 */
int hash_table_size(const HashTable* ht); 

/**
 * Restituisce un array contenente tutte le chiavi presenti nella tabella.
 * L'ordine non è garantito.
 * Il chiamante è responsabile per deallocare l'array restituito (con free()).
 */
void** hash_table_keyset(const HashTable* ht); 

/**
 * Libera tutta la memoria associata alla HashTable (ma non alle chiavi/valori).
 */
void hash_table_free(HashTable* ht); 

#endif // HASH_TABLE_H