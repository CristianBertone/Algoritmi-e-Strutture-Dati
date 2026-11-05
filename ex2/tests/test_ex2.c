#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "unity.h"

// --- VARIABILI GLOBALI ---
HashTable* ht = NULL;

// --- FUNZIONI DI SUPPORTO ---
unsigned long hash_str(const void* key) {
    unsigned long hash = 5381;
    int c;
    const char* str = (const char*)key;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

int cmp_str(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

unsigned long hash_int(const void* key) {
    return (unsigned long)(*(const int*)key);
}

int cmp_int(const void* a, const void* b) {
    return (*(const int*)a - *(const int*)b);
}

// --- SETUP E TEARDOWN ---
void setUp(void) {
    // Non creo la tabella qui perché alcuni test usano stringhe e altri interi.
    // Mi assicuro solo che il puntatore sia pulito.
    ht = NULL;
}

void tearDown(void) {
    // Se la tabella è stata allocata durante il test, la libero in automatico.
    if (ht != NULL) {
        hash_table_free(ht);
        ht = NULL;
    }
}

// --- TEST 1: Inserimento e recupero stringhe (Casi Comuni) ---
void test_string_insertion(void) {
    ht = hash_table_create(cmp_str, hash_str);
    TEST_ASSERT_NOT_NULL(ht);

    int val1 = 10, val2 = 20;
    
    hash_table_put(ht, "Achilles", &val1);
    hash_table_put(ht, "Hector", &val2);
    
    // Verifica dimensione
    TEST_ASSERT_EQUAL_INT(2, hash_table_size(ht));
    
    // Verifica recupero corretto
    int* res = (int*)hash_table_get(ht, "Achilles");
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(10, *res);

    // Caso Limite: Recupero di una chiave inesistente
    TEST_ASSERT_NULL(hash_table_get(ht, "Agamemnon"));
}

// --- TEST 2: Inserimento chiavi intere (Casi Comuni) ---
void test_integer_keys(void) {
    ht = hash_table_create(cmp_int, hash_int);
    
    int k1 = 1, v1 = 100;
    int k2 = 2, v2 = 200;
    
    hash_table_put(ht, &k1, &v1);
    hash_table_put(ht, &k2, &v2);
    
    int* res = (int*)hash_table_get(ht, &k2);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(200, *res);
}

// --- TEST 3: Rehashing e Stress Test (Caso Limite) ---
void test_resize_trigger(void) {
    ht = hash_table_create(cmp_int, hash_int);
    
    // Array statici per mantenere in memoria gli indirizzi durante il test
    static int keys[2000];
    static int vals[2000];
    
    for(int i = 0; i < 2000; i++) {
        keys[i] = i; 
        vals[i] = i * 10;
        hash_table_put(ht, &keys[i], &vals[i]);
    }
    
    // Verifica che nessuna chiave sia andata persa durante eventuali ridimensionamenti
    TEST_ASSERT_EQUAL_INT(2000, hash_table_size(ht));
    
    // Verifica a campione un elemento centrale e uno finale
    int* res = (int*)hash_table_get(ht, &keys[1500]);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(15000, *res);

    res = (int*)hash_table_get(ht, &keys[1999]);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(19990, *res);
}

// --- TEST 4: Contains e Remove (Casi Comuni e Limite) ---
void test_contains_and_remove(void) {
    ht = hash_table_create(cmp_str, hash_str);
    int v1 = 100;
    char* key = "Odysseus";

    // Prima dell'inserimento
    TEST_ASSERT_EQUAL_INT(0, hash_table_contains_key(ht, key));

    // Inserisco
    hash_table_put(ht, key, &v1);
    TEST_ASSERT_EQUAL_INT(1, hash_table_contains_key(ht, key));
    TEST_ASSERT_EQUAL_INT(1, hash_table_size(ht));

    // Rimuovo
    hash_table_remove(ht, key);
    
    // Dopo la rimozione
    TEST_ASSERT_EQUAL_INT(0, hash_table_contains_key(ht, key));
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(ht));
    TEST_ASSERT_NULL(hash_table_get(ht, key));

    // Caso Limite: Rimuovere un elemento che non esiste (non deve crashare)
    hash_table_remove(ht, "Ajax");
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(ht));
}

// --- TEST 5: Estrazione del Keyset ---
void test_keyset_generation(void) {
    ht = hash_table_create(cmp_str, hash_str);
    int v = 1;
    
    hash_table_put(ht, "Apple", &v);
    hash_table_put(ht, "Banana", &v);
    hash_table_put(ht, "Cherry", &v);

    void** keys = hash_table_keyset(ht);
    TEST_ASSERT_NOT_NULL(keys);

    // Verifico che ci siano esattamente 3 elementi e siano quelli corretti.
    // L'ordine in una hash table non è garantito, quindi conto i match.
    int match_count = 0;
    for (int i = 0; i < 3; i++) {
        char* k = (char*)keys[i];
        if (strcmp(k, "Apple") == 0 || strcmp(k, "Banana") == 0 || strcmp(k, "Cherry") == 0) {
            match_count++;
        }
    }
    
    TEST_ASSERT_EQUAL_INT(3, match_count);

    // Libero l'array allocato da hash_table_keyset
    free(keys);
}

// --- RUNNER ---
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_string_insertion);
    RUN_TEST(test_integer_keys);
    RUN_TEST(test_resize_trigger);
    RUN_TEST(test_contains_and_remove);
    RUN_TEST(test_keyset_generation);

    return UNITY_END();
}