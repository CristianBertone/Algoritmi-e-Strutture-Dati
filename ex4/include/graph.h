#ifndef GRAPH_H  
#define GRAPH_H   

typedef struct graph *Graph;

typedef struct edge {
    void* source;   // nodo d'origine
    void* dest;     // nodo di destinazione
    void* label;    // etichetta dell'arco
} Edge;

//Crea un grafo vuoto, etichettato se labelled == 1 e diretto
// se directed == 1. Le funzioni compare e hash sono necessarie 
// per la costruzione della tavola hash 
// che deve essere usata dalla libreria. Complessità: O(1)
Graph graph_create(int labelled,
                  int directed,
                  int (*compare)(const void*, const void*),
                  unsigned long (*hash)(const void*));

//Dice se il grafo è diretto o meno.
//Complessità: O(1)
int graph_is_directed(const Graph gr);

//Dice se il grafo è etichettato o meno.
//Complessità: O(1)
int graph_is_labelled(const Graph gr);

//Aggiunge un nodo al grafo.
//Complessità: O(1)
int graph_add_node(Graph gr, const void* node);

//Controlla se un nodo è presente nel grafo.
//Complessità: O(1)
int graph_contains_node(const Graph gr, const void* node);

//Rimuove un nodo dal grafo.
//Complessità: O(N)
int graph_remove_node(Graph gr, const void* node);

//Restituisce il numero di nodi nel grafo.
//Complessità: O(1)
int graph_num_nodes(const Graph gr);

//Recupera tutti i nodi del grafo.
//Complessità: O(N)
void** graph_get_nodes(const Graph gr);

//Gestione Archi

//Aggiunge un arco dati gli estremi e l'etichetta.
//Complessità: O(1) (*)
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);

//Controlla se un arco è presente nel grafo.
//Complessità: O(1) (*)
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);

//Rimuove un arco dal grafo.
//Complessità: O(1) (*)
int graph_remove_edge(Graph gr, const void* node1, const void* node2);

//Restituisce il numero di archi nel grafo.
//Complessità: O(N)
int graph_num_edges(const Graph gr);

//Recupera tutti gli archi del grafo.
//Complessità: O(N)
Edge** graph_get_edges(const Graph gr);

//Recupera l'etichetta di un arco.
//Complessità: O(1) (*)
void* graph_get_label(const Graph gr, const void* node1, const void* node2);

//Adiacenza

//Recupera i nodi adiacenti a un dato nodo.
//Complessità: O(1) (*)
void** graph_get_neighbours(const Graph gr, const void* node);

//Recupera il numero di nodi adiacenti a un dato nodo.
//Complessità: O(1)
int graph_num_neighbours(const Graph gr, const void* node);

//Distruzione

//Libera la memoria allocata per il grafo.
void graph_free(Graph gr);

//Algorimto di visita in ampiezza
void** breadth_first_visit(Graph gr,
                          void* start,
                          int (*compare)(const void*, const void*),
                          unsigned long (*hash)(const void*));

#endif