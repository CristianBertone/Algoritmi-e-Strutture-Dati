#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "records.h"
#include "hybrid_sort.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <infile> <outfile> <field> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];
    int field = atoi(argv[3]);
    size_t k = (size_t)atol(argv[4]);

    Record *records = NULL;
    size_t n = 0;
    
    FILE *f_in = fopen(infile, "rb");
    if (!f_in) {
        perror("Error opening input");
        return EXIT_FAILURE;
    }
    
    if (load_records_from_file(f_in, &records, &n) < 0) {
        fprintf(stderr, "Error reading data\n");
        fclose(f_in);
        return EXIT_FAILURE;
    }
    fclose(f_in);

    clock_t start = clock();
    switch (field) {
        case 1: hybridsort(records, n, sizeof(Record), k, cmp_id); break;
        case 2: hybridsort(records, n, sizeof(Record), k, cmp_field1); break;
        case 3: hybridsort(records, n, sizeof(Record), k, cmp_field2); break;
        case 4: hybridsort(records, n, sizeof(Record), k, cmp_field3); break;
        default:
            fprintf(stderr, "Invalid field\n");
            free(records);
            return EXIT_FAILURE;
    }
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.3f sec\n", time_spent);

    FILE *f_out = fopen(outfile, "wb");
    if (!f_out) {
        perror("Error opening output");
        free(records);
        return EXIT_FAILURE;
    }
    
    if (save_records_to_file(f_out, records, n) < 0) {
        fprintf(stderr, "Error writing data\n");
        fclose(f_out);
        free(records);
        return EXIT_FAILURE;
    }
    fclose(f_out);

    free(records);
    return EXIT_SUCCESS;
}
