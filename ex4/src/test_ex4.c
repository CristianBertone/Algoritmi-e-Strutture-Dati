#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "unity.h"


int cmp_str(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

unsigned long hash_str(const void* key) {
    unsigned long hash = 5381;
    int c = 0;
    const char* str = (const char*)key;
    while (*str != '\0') {
        c = *str;
        hash = ((hash << 5) + hash) + c;
        str++;
    }
    return hash;
}

Graph g = NULL;

void setUp(void) {

    g = graph_create(1, 0, cmp_str, hash_str);
}


void tearDown(void) {

    if (g != NULL) {
        graph_free(g);
        g = NULL;
    }
}

void test_graph_creation_should_succeed(void) {
    printf("[Test] Verifica creazione del grafo...\n");

    TEST_ASSERT_NOT_NULL(g);
}

void test_graph_nodes_management(void) {
    printf("[Test] Verifica inserimento e ricerca nodi...\n");
    char* n1 = "Torino";
    char* n2 = "Milano";
    char* n_inesistente = "Roma";


    TEST_ASSERT_EQUAL_INT(1, graph_add_node(g, n1));
    TEST_ASSERT_EQUAL_INT(1, graph_add_node(g, n2));
    

    TEST_ASSERT_EQUAL_INT(1, graph_contains_node(g, n1));
    

    TEST_ASSERT_EQUAL_INT(0, graph_contains_node(g, n_inesistente));


    TEST_ASSERT_EQUAL_INT(0, graph_add_node(g, n1)); 
}

void test_graph_edges_common_cases(void) {
    printf("[Test] Verifica inserimento e ricerca archi normali...\n");
    char* n1 = "Torino";
    char* n2 = "Milano";
    float peso = 140.5;

    graph_add_node(g, n1);
    graph_add_node(g, n2);


    TEST_ASSERT_EQUAL_INT(1, graph_add_edge(g, n1, n2, &peso));


    TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(g, n1, n2));
    

    TEST_ASSERT_EQUAL_INT(1, graph_contains_edge(g, n2, n1));


    float* label_trovata = (float*)graph_get_label(g, n1, n2);
    TEST_ASSERT_NOT_NULL(label_trovata);

    TEST_ASSERT_EQUAL_FLOAT(140.5, *label_trovata); 
}

void test_graph_edges_edge_cases(void) {
    printf("[Test] Verifica casi limite sugli archi...\n");
    char* n1 = "Torino";
    char* n2 = "Milano";
    float peso = 140.5;


    graph_add_node(g, n1);

    TEST_ASSERT_EQUAL_INT(0, graph_add_edge(g, n1, n2, &peso));
    

    TEST_ASSERT_NULL(graph_get_label(g, n1, "Roma"));
}


int main(void) {

    UNITY_BEGIN();

    printf("==========================================\n");
    printf("   INIZIO SUITE DI TEST: GRAFO\n");
    printf("==========================================\n");

    RUN_TEST(test_graph_creation_should_succeed);
    RUN_TEST(test_graph_nodes_management);
    RUN_TEST(test_graph_edges_common_cases);
    RUN_TEST(test_graph_edges_edge_cases);

    printf("==========================================\n");


    return UNITY_END();
}