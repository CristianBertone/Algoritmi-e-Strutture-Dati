#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "hash.h"

int compare_strings(const void* a, const void* b) {
    const char* string_a = (const char*)a;
    const char* string_b = (const char*)b;
    int compare_result = strcmp(string_a, string_b);
    return compare_result;
}

unsigned long hash_string(const void* key) {
    const char* string = (const char*)key;
    unsigned long hash_value = 5381;
    int current_char = 0;
    
    while (*string != '\0') {
        current_char = *string;
        hash_value = ((hash_value << 5) + hash_value) + current_char;
        string = string + 1;
    }
    
    return hash_value;
}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <csv_file> <start_city> <output_file>\n", argv[0]);
        return 1;
    }
    
    char* csv_filename = argv[1];
    char* start_city_arg = argv[2];
    char* output_filename = argv[3];
    
    FILE* input_file = fopen(csv_filename, "r");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    
    int is_labelled = 1;
    int is_directed = 0;
    Graph city_graph = graph_create(is_labelled, is_directed, compare_strings, hash_string);
    HashTable* unique_cities_map = hash_table_create(compare_strings, hash_string);
    
    char line_buffer[1024];
    
    while (fgets(line_buffer, sizeof(line_buffer), input_file) != NULL) {
        char* newline_char = strchr(line_buffer, '\n');
        if (newline_char != NULL) {
            *newline_char = '\0';
        }
        
        char* token_city1 = strtok(line_buffer, ",");
        char* token_city2 = strtok(NULL, ",");
        char* token_distance = strtok(NULL, ",");
        
        if (token_city1 != NULL && token_city2 != NULL && token_distance != NULL) {
            char* city1_ptr = (char*)hash_table_get(unique_cities_map, token_city1);
            if (city1_ptr == NULL) {
                int length1 = strlen(token_city1);
                city1_ptr = (char*)malloc(length1 + 1);
                strcpy(city1_ptr, token_city1);
                hash_table_put(unique_cities_map, city1_ptr, city1_ptr);
                graph_add_node(city_graph, city1_ptr);
            }
            
            char* city2_ptr = (char*)hash_table_get(unique_cities_map, token_city2);
            if (city2_ptr == NULL) {
                int length2 = strlen(token_city2);
                city2_ptr = (char*)malloc(length2 + 1);
                strcpy(city2_ptr, token_city2);
                hash_table_put(unique_cities_map, city2_ptr, city2_ptr);
                graph_add_node(city_graph, city2_ptr);
            }
            
            float* distance_ptr = (float*)malloc(sizeof(float));
            *distance_ptr = atof(token_distance);
            
            graph_add_edge(city_graph, city1_ptr, city2_ptr, distance_ptr);
        }
    }
    
    fclose(input_file);
    
    char* actual_start_city = (char*)hash_table_get(unique_cities_map, start_city_arg);
    
    if (actual_start_city != NULL) {
        void** visited_path = breadth_first_visit(city_graph, actual_start_city, compare_strings, hash_string);
        
        if (visited_path != NULL) {
            FILE* output_file = fopen(output_filename, "w");
            if (output_file != NULL) {
                int i = 0;
                while (visited_path[i] != NULL) {
                    char* city_to_print = (char*)visited_path[i];
                    fprintf(output_file, "%s\n", city_to_print);
                    i = i + 1;
                }
                fclose(output_file);
            } else {
                printf("Error opening output file\n");
            }
            free(visited_path);
        }
    } else {
        printf("Start city not found in the graph\n");
    }
    
    void** all_nodes_array = graph_get_nodes(city_graph);
    int total_nodes_count = graph_num_nodes(city_graph);
    
    int j = 0;
    while (j < total_nodes_count) {
        char* city_string = (char*)all_nodes_array[j];
        free(city_string);
        j = j + 1;
    }
    free(all_nodes_array);
    
    Edge** all_edges_array = graph_get_edges(city_graph);
    if (all_edges_array != NULL) {
        int total_edges_count = graph_num_edges(city_graph);
        int k = 0;
        while (k < total_edges_count) {
            Edge* current_edge = all_edges_array[k];
            if (current_edge != NULL) {
                if (city_graph != NULL) { 
                    int is_lab = graph_is_labelled(city_graph);
                    if (is_lab == 1 && current_edge->label != NULL) {
                        free(current_edge->label);
                    }
                }
                free(current_edge);
            }
            k = k + 1;
        }
        free(all_edges_array);
    }
    
    hash_table_free(unique_cities_map);
    graph_free(city_graph);
    
    int exit_success = 0;
    return exit_success;
}