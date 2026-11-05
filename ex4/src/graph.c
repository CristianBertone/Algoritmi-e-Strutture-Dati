#include "graph.h"
#include "hash.h"
#include <stdlib.h>

struct graph {
    int is_labelled;
    int is_directed;
    int (*compare_function)(const void*, const void*);
    unsigned long (*hash_function)(const void*);
    HashTable* nodes_map; 
    void** nodes_array;
    int array_capacity;
    int total_nodes;
    int total_edges;
};

Graph graph_create(int labelled, int directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    Graph new_graph = (Graph)malloc(sizeof(struct graph));
    if (new_graph == NULL) {
        return NULL;
    }

    new_graph->is_labelled = labelled;
    new_graph->is_directed = directed;
    new_graph->compare_function = compare;
    new_graph->hash_function = hash;
    
    new_graph->nodes_map = hash_table_create(compare, hash);
    
    new_graph->array_capacity = 16;
    new_graph->nodes_array = (void**)malloc(new_graph->array_capacity * sizeof(void*));
    new_graph->total_nodes = 0;
    new_graph->total_edges = 0;

    if (new_graph->nodes_map == NULL || new_graph->nodes_array == NULL) {
        free(new_graph->nodes_array);
        free(new_graph->nodes_map);
        free(new_graph);
        return NULL;
    }

    return new_graph;
}

int graph_is_directed(const Graph gr) {
    if (gr != NULL) {
        return gr->is_directed;
    }
    return 0;
}

int graph_is_labelled(const Graph gr) {
    if (gr != NULL) {
        return gr->is_labelled;
    }
    return 0;
}

int graph_add_node(Graph gr, const void* node) {
    if (gr == NULL || node == NULL) {
        return 0;
    }

    if (graph_contains_node(gr, node) == 1) {
        return 0;
    }

    if (gr->total_nodes == gr->array_capacity) {
        int new_capacity = gr->array_capacity * 2;
        void** bigger_array = (void**)realloc(gr->nodes_array, new_capacity * sizeof(void*));
        if (bigger_array == NULL) {
            return 0;
        }
        gr->array_capacity = new_capacity;
        gr->nodes_array = bigger_array;
    }

    HashTable* edges_map = hash_table_create(gr->compare_function, gr->hash_function);
    if (edges_map == NULL) {
        return 0;
    }

    hash_table_put(gr->nodes_map, node, edges_map);
    
    int insert_index = gr->total_nodes;
    gr->nodes_array[insert_index] = (void*)node;
    gr->total_nodes = gr->total_nodes + 1;

    return 1;
}

int graph_contains_node(const Graph gr, const void* node) {
    int found = 0;
    
    if (gr != NULL && node != NULL) {
        void* value = hash_table_get(gr->nodes_map, node);
        if (value != NULL) {
            found = 1;
        }
    }
    
    return found;
}

int graph_num_nodes(const Graph gr) {
    int count = 0;
    if (gr != NULL) {
        count = gr->total_nodes;
    }
    return count;
}

void** graph_get_nodes(const Graph gr) {
    if (gr == NULL) {
        return NULL;
    }

    void** copied_nodes = (void**)malloc(gr->total_nodes * sizeof(void*));
    if (copied_nodes == NULL) {
        return NULL;
    }

    int i = 0;
    while (i < gr->total_nodes) {
        copied_nodes[i] = gr->nodes_array[i];
        i = i + 1;
    }

    return copied_nodes;
}

int graph_remove_node(Graph gr, const void* node) {
    if (gr == NULL || node == NULL) {
        return 0;
    }
    
    if (graph_contains_node(gr, node) == 0) {
        return 0;
    }
    
    for (int i = 0; i < gr->total_nodes; i++) {
        void* current_node = gr->nodes_array[i];
        if (current_node == node) continue;

        HashTable* current_edges = (HashTable*)hash_table_get(gr->nodes_map, current_node);
        if (current_edges != NULL) {
            if (hash_table_get(current_edges, node) != NULL) {
                hash_table_remove(current_edges, node);
                if (gr->is_directed == 1) {
                    gr->total_edges = gr->total_edges - 1;
                }
            }
        }
    }

    HashTable* node_edges = (HashTable*)hash_table_get(gr->nodes_map, node);
    if (node_edges != NULL) {
        int out_edges = hash_table_size(node_edges);
        gr->total_edges = gr->total_edges - out_edges;
        hash_table_free(node_edges);
    }

    hash_table_remove(gr->nodes_map, node);

    int found_index = -1;
    for (int i = 0; i < gr->total_nodes; i++) {
        if (gr->nodes_array[i] == node) {
            found_index = i;
            break;
        }
    }
    
    if (found_index != -1) {
        for (int i = found_index; i < gr->total_nodes - 1; i++) {
            gr->nodes_array[i] = gr->nodes_array[i + 1];
        }
        gr->total_nodes = gr->total_nodes - 1;
    }
    
    return 1;
}

int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label) {
    if (gr == NULL || node1 == NULL || node2 == NULL) {
        return 0;
    }

    if (graph_contains_node(gr, node1) == 0) {
        return 0;
    }
    if (graph_contains_node(gr, node2) == 0) {
        return 0;
    }

    HashTable* edges_of_node1 = (HashTable*)hash_table_get(gr->nodes_map, node1);
    
    if (hash_table_get(edges_of_node1, node2) != NULL) {
        return 0;
    }

    void* actual_label = (void*)label;
    if (gr->is_labelled == 0) {
        actual_label = (void*)1; 
    } else if (label == NULL) {
        return 0; 
    }

    gr->total_edges = gr->total_edges + 1;
    hash_table_put(edges_of_node1, node2, actual_label);

    if (gr->is_directed == 0) {
        HashTable* edges_of_node2 = (HashTable*)hash_table_get(gr->nodes_map, node2);
        hash_table_put(edges_of_node2, node1, actual_label);
    }

    return 1;
}

int graph_contains_edge(const Graph gr, const void* node1, const void* node2) {
    int edge_exists = 0;
    
    if (gr != NULL && node1 != NULL && node2 != NULL) {
        HashTable* edges_of_node1 = (HashTable*)hash_table_get(gr->nodes_map, node1);
        if (edges_of_node1 != NULL) {
            void* label = hash_table_get(edges_of_node1, node2);
            if (label != NULL) {
                edge_exists = 1;
            }
        }
    }
    
    return edge_exists;
}

void* graph_get_label(const Graph gr, const void* node1, const void* node2) {
    void* found_label = NULL;
    
    if (gr != NULL && node1 != NULL && node2 != NULL) {
        HashTable* edges_of_node1 = (HashTable*)hash_table_get(gr->nodes_map, node1);
        if (edges_of_node1 != NULL) {
            found_label = hash_table_get(edges_of_node1, node2);
        }
    }
    
    if (gr != NULL && gr->is_labelled == 0) {
        found_label = NULL;
    }
    
    return found_label;
}

int graph_num_edges(const Graph gr) {
    int count = 0;
    if (gr != NULL) {
        count = gr->total_edges;
    }
    return count;
}

int graph_remove_edge(Graph gr, const void* node1, const void* node2) {
    if (gr == NULL || node1 == NULL || node2 == NULL) {
        return 0;
    }
    
    HashTable* edges_of_node1 = (HashTable*)hash_table_get(gr->nodes_map, node1);
    
    if (edges_of_node1 != NULL) {
        if (hash_table_get(edges_of_node1, node2) != NULL) {
            hash_table_remove(edges_of_node1, node2);
            gr->total_edges = gr->total_edges - 1;
            
            if (gr->is_directed == 0) {
                HashTable* edges_of_node2 = (HashTable*)hash_table_get(gr->nodes_map, node2);
                if (edges_of_node2 != NULL) {
                    hash_table_remove(edges_of_node2, node1);
                }
            }
            return 1;
        }
    }
    return 0;
}

int graph_num_neighbours(const Graph gr, const void* node) {
    int count = 0;
    if (gr != NULL && node != NULL) {
        HashTable* edges_map = (HashTable*)hash_table_get(gr->nodes_map, node);
        if (edges_map != NULL) {
            count = hash_table_size(edges_map); 
        }
    }
    return count;
}

void** graph_get_neighbours(const Graph gr, const void* node) {
    void** keys = NULL;
    if (gr != NULL && node != NULL) {
        HashTable* edges_map = (HashTable*)hash_table_get(gr->nodes_map, node);
        if (edges_map != NULL) {
            keys = hash_table_keyset(edges_map); 
        }
    }
    return keys;
}

Edge** graph_get_edges(const Graph gr) {
    if (gr == NULL) {
        return NULL;
    }
    
    Edge** all_edges = (Edge**)malloc((gr->total_edges + 1) * sizeof(Edge*));
    if (all_edges == NULL) {
        return NULL;
    }
    
    int edge_index = 0;
    int i = 0;
    while (i < gr->total_nodes) {
        void* current_node = gr->nodes_array[i];
        HashTable* edges_map = (HashTable*)hash_table_get(gr->nodes_map, current_node);
        
        if (edges_map != NULL) {
            int num_neigh = hash_table_size(edges_map);
            void** neigh_keys = hash_table_keyset(edges_map);
            
            if (neigh_keys != NULL) {
                int j = 0;
                while (j < num_neigh) {
                    void* dest_node = neigh_keys[j];
                    
                    if (gr->is_directed == 0) {
                        if (gr->compare_function(current_node, dest_node) > 0) {
                            j = j + 1;
                            continue;
                        }
                    }
                    
                    void* label = hash_table_get(edges_map, dest_node);
                    
                    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
                    if (new_edge != NULL) {
                        new_edge->source = current_node;
                        new_edge->dest = dest_node;
                        if (gr->is_labelled == 0) {
                            new_edge->label = NULL;
                        } else {
                            new_edge->label = label;
                        }
                        all_edges[edge_index] = new_edge;
                        edge_index = edge_index + 1;
                    }
                    j = j + 1;
                }
                free(neigh_keys);
            }
        }
        i = i + 1;
    }
    all_edges[edge_index] = NULL;
    return all_edges;
}

void graph_free(Graph gr) {
    if (gr != NULL) {
        int i = 0;
        while (i < gr->total_nodes) {
            void* current_node = gr->nodes_array[i];
            HashTable* node_edges = (HashTable*)hash_table_get(gr->nodes_map, current_node);
            if (node_edges != NULL) {
                hash_table_free(node_edges);
            }
            i = i + 1;
        }
        
        hash_table_free(gr->nodes_map);
        free(gr->nodes_array);
        free(gr);
    }
}

void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    if (gr == NULL || start == NULL) {
        return NULL;
    }
    
    int contains_start = graph_contains_node(gr, start);
    if (contains_start == 0) {
        return NULL;
    }
    
    int total_nodes = graph_num_nodes(gr);
    void** visit_queue = (void**)malloc(total_nodes * sizeof(void*));
    void** visit_result = (void**)malloc((total_nodes + 1) * sizeof(void*));
    HashTable* visited_map = hash_table_create(compare, hash);
    
    if (visit_queue == NULL || visit_result == NULL || visited_map == NULL) {
        if (visit_queue != NULL) {
            free(visit_queue);
        }
        if (visit_result != NULL) {
            free(visit_result);
        }
        if (visited_map != NULL) {
            hash_table_free(visited_map);
        }
        return NULL;
    }
    
    int queue_head = 0;
    int queue_tail = 0;
    int result_index = 0;
    
    visit_queue[queue_tail] = start;
    queue_tail = queue_tail + 1;
    
    void* visited_marker = (void*)1;
    hash_table_put(visited_map, start, visited_marker);
    
    while (queue_head < queue_tail) {
        void* current_node = visit_queue[queue_head];
        queue_head = queue_head + 1;
        
        visit_result[result_index] = current_node;
        result_index = result_index + 1;
        
        int num_neighbors = graph_num_neighbours(gr, current_node);
        void** neighbors_array = graph_get_neighbours(gr, current_node);
        
        if (neighbors_array != NULL) {
            int i = 0;
            while (i < num_neighbors) {
                void* neighbor = neighbors_array[i];
                void* check_visited = hash_table_get(visited_map, neighbor);
                
                if (check_visited == NULL) {
                    hash_table_put(visited_map, neighbor, visited_marker);
                    visit_queue[queue_tail] = neighbor;
                    queue_tail = queue_tail + 1;
                }
                
                i = i + 1;
            }
            free(neighbors_array);
        }
    }
    
    visit_result[result_index] = NULL;
    
    free(visit_queue);
    hash_table_free(visited_map);
    
    return visit_result;
}