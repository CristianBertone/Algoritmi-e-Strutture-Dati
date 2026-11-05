#include <stdlib.h>
#include <string.h>
#include "records.h"

int read_record(FILE *file, Record *record) {
    unsigned char buf[36];
    if (fread(buf, 36, 1, file) != 1) return 0;
    
    memcpy(&record->id, &buf[0], 8);
    memcpy(&record->field1, &buf[8], 4);
    memcpy(&record->field2, &buf[12], 8);
    memcpy(record->field3, &buf[20], 16);
    return 1;
}

int write_record(FILE *file, const Record *record) {
    unsigned char buf[36];
    memcpy(&buf[0], &record->id, 8);
    memcpy(&buf[8], &record->field1, 4);
    memcpy(&buf[12], &record->field2, 8);
    memcpy(&buf[20], record->field3, 16);
    
    if (fwrite(buf, 36, 1, file) != 1) return 0;
    return 1;
}

int load_records_from_file(FILE *file, Record **records, size_t *count) {
    size_t cap = 100000, i = 0;
    *records = malloc(cap * sizeof(Record));
    if (!*records) return -1;
    
    while (read_record(file, &(*records)[i])) {
        if (++i >= cap) {
            cap *= 2;
            Record *tmp = realloc(*records, cap * sizeof(Record));
            if (!tmp) { free(*records); return -1; }
            *records = tmp;
        }
    }
    *count = i;
    return 0;
}

int save_records_to_file(FILE *file, const Record *records, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (!write_record(file, &records[i])) return -1;
    }
    return 0;
}

void print_record(const Record *record) {
    printf("ID: %llu, F1: %f, F2: %lld, F3: %s\n", 
           (unsigned long long)record->id, 
           record->field1, 
           (long long)record->field2, 
           record->field3);
}

int cmp_id(const void *a, const void *b) {
    uint64_t fa = ((const Record*)a)->id;
    uint64_t fb = ((const Record*)b)->id;
    return (fa > fb) - (fa < fb);
}

int cmp_field1(const void *a, const void *b) {
    float fa = ((const Record*)a)->field1;
    float fb = ((const Record*)b)->field1;
    return (fa > fb) - (fa < fb);
}

int cmp_field2(const void *a, const void *b) {
    int64_t fa = ((const Record*)a)->field2;
    int64_t fb = ((const Record*)b)->field2;
    return (fa > fb) - (fa < fb);
}

int cmp_field3(const void *a, const void *b) {
    return strcmp(((const Record*)a)->field3, ((const Record*)b)->field3);
}
