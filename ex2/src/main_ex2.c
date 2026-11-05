#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

// --- Funzioni Helper per la HashTable (per stringhe) ---

unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int compare_string(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// --- Programma Principale ---

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <input_file> <min_length>\n", argv[0]);
        return 1;
    }

    char* input_filename = argv[1];
    int min_length = atoi(argv[2]);

    if (min_length <= 0) {
        fprintf(stderr, "Errore: min_length deve essere un intero positivo.\n");
        return 1;
    }

    FILE* file = fopen(input_filename, "r");
    if (!file) {
        perror("Errore apertura file");
        return 1;
    }

    HashTable* word_counts = hash_table_create(compare_string, hash_string);
    if (!word_counts) {
        fprintf(stderr, "Errore: impossibile creare la hash table.\n");
        fclose(file);
        return 1;
    }

    char buffer[1024];
    int idx = 0;
    int c;

    // Legge il file carattere per carattere
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            // Se è una lettera, la aggiunge al buffer in minuscolo
            if (idx < 1023) { // Evita il buffer overflow
                buffer[idx++] = tolower(c);
            }
        } else {
            // Se non è una lettera (spazio, punteggiatura, trattino), chiude la parola
            if (idx > 0) {
                buffer[idx] = '\0'; // Termina la stringa
                
                if (idx >= min_length) {
                    int* count_ptr = (int*)hash_table_get(word_counts, buffer);

                    if (count_ptr == NULL) {
                        char* key_copy = (char*)malloc(idx + 1);
                        if (key_copy) {
                            strcpy(key_copy, buffer);
                            int* new_count = (int*)malloc(sizeof(int));
                            if (new_count) {
                                *new_count = 1;
                                hash_table_put(word_counts, key_copy, new_count);
                            } else {
                                free(key_copy);
                            }
                        }
                    } else {
                        (*count_ptr)++;
                    }
                }
                idx = 0; // Resetta l'indice per la prossima parola
            }
        }
    }
    
    // Controlla se c'è un'ultima parola rimasta nel buffer a fine file
    if (idx > 0) {
        buffer[idx] = '\0';
        if (idx >= min_length) {
            int* count_ptr = (int*)hash_table_get(word_counts, buffer);
            if (count_ptr == NULL) {
                char* key_copy = (char*)malloc(idx + 1);
                if (key_copy) {
                    strcpy(key_copy, buffer);
                    int* new_count = (int*)malloc(sizeof(int));
                    if (new_count) {
                        *new_count = 1;
                        hash_table_put(word_counts, key_copy, new_count);
                    } else {
                        free(key_copy);
                    }
                }
            } else {
                (*count_ptr)++;
            }
        }
    }
    
    fclose(file);

    int size = hash_table_size(word_counts);
    if (size == 0) {
        printf("Nessuna parola trovata con lunghezza >= %d.\n", min_length);
        hash_table_free(word_counts);
        return 0;
    }

    void** keys = hash_table_keyset(word_counts);
    if (!keys) {
        fprintf(stderr, "Errore nel recuperare le chiavi dalla tabella.\n");
        hash_table_free(word_counts);
        return 1;
    }

    char* most_frequent_word = NULL;
    int max_frequency = 0;

    for (int i = 0; i < size; i++) {
        char* current_key = (char*)keys[i];
        int* current_count = (int*)hash_table_get(word_counts, current_key);

        if (current_count && *current_count > max_frequency) {
            max_frequency = *current_count;
            most_frequent_word = current_key;
        }
    }

    if (most_frequent_word) {
        printf("La parola piu' frequente (lunghezza >= %d) e' '%s' con %d occorrenze.\n",
               min_length, most_frequent_word, max_frequency);
    } else {
        printf("Nessuna parola trovata con i criteri specificati.\n");
    }

    for (int i = 0; i < size; i++) {
        void* key = keys[i];
        void* value = hash_table_get(word_counts, key);
        free(key);
        free(value);
    }
    
    free(keys);
    hash_table_free(word_counts);

    return 0;
}