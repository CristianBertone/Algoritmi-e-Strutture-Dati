#ifndef RECORDS_H
#define RECORDS_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Struttura di un singolo record.
 */
typedef struct {
    uint64_t id;
    float field1;
    int64_t field2;
    char field3[16];
} Record;

/**
 * @brief Legge un singolo record da un file binario.
 * @param file Puntatore al file in lettura.
 * @param record Puntatore alla struttura Record da riempire.
 * @return 1 in caso di successo; 0 altrimenti.
 */
int read_record(FILE *file, Record *record);

/**
 * @brief Scrive un singolo record su un file binario.
 * @param file Puntatore al file aperto in scrittura.
 * @param record Puntatore al record da scrivere.
 * @return 1 in caso di successo, 0 altrimenti.
 */
int write_record(FILE *file, const Record *record);

/**
 * @brief Carica tutti i record da un file all'interno di un array.
 * @param file Puntatore al file di input.
 * @param records Doppio puntatore per allocare l'array di record.
 * @param count Puntatore per salvare il numero totale di record letti.
 * @return 0 in caso di successo, -1 in caso di errore di memoria.
 */
int load_records_from_file(FILE *file, Record **records, size_t *count);

/**
 * @brief Salva un array di record su un file binario.
 * @param file Puntatore al file di output.
 * @param records Array di record da salvare.
 * @param count Numero totale di record presenti nell'array.
 * @return 0 in caso di successo, -1 in caso di errore.
 */
int save_records_to_file(FILE *file, const Record *records, size_t count);
/**
 * @brief Stampa i campi di un record.
 * @param record Puntatore al record da stampare.
 */
void print_record(const Record *record);


/**
 * @brief Compara due record in base all'ID.
 */
int cmp_id(const void *a, const void *b);

/**
 * @brief Compara due record in base a field1 (float).
 */
int cmp_field1(const void *a, const void *b);


/**
 * @brief Compara due record in base a field2 (int64_t).
 */
int cmp_field2(const void *a, const void *b);

/**
 * @brief Compara due record in base a field3 (stringa).
 */
int cmp_field3(const void *a, const void *b);

#endif
