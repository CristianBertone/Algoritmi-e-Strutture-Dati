#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "priority_queue.h"

PriorityQueue* pq;

int cmp_int(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
unsigned long hash_int(const void* key) { return (unsigned long)(*(int*)key); }

void setUp(void) {
    pq = priority_queue_create(cmp_int, hash_int);
}

void tearDown(void) {
    if (pq) {
        priority_queue_free(pq);
        pq = NULL;
    }
}

void test_priority_queue_common_cases(void) {
    int v1 = 10, v2 = 30, v3 = 20, v4 = 5;
    
    priority_queue_push(pq, &v1);
    priority_queue_push(pq, &v2);
    priority_queue_push(pq, &v3);
    priority_queue_push(pq, &v4);
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, priority_queue_size(pq), "Size iniziale non corretta");
    TEST_ASSERT_EQUAL_INT_MESSAGE(30, *(int*)priority_queue_top(pq), "Top iniziale non corretto");
    
    TEST_ASSERT_TRUE_MESSAGE(priority_queue_contains(pq, &v3), "Contains fallito per l'elemento v3");
    
    priority_queue_remove(pq, &v2); 
    TEST_ASSERT_FALSE_MESSAGE(priority_queue_contains(pq, &v2), "L'elemento v2 (30) dovrebbe essere stato rimosso");
    TEST_ASSERT_EQUAL_INT_MESSAGE(20, *(int*)priority_queue_top(pq), "Nuovo Top errato dopo il remove");

    priority_queue_pop(pq); 
    TEST_ASSERT_EQUAL_INT_MESSAGE(10, *(int*)priority_queue_top(pq), "Pop fallito, il top non è quello atteso");
}

void test_priority_queue_empty_operations(void) {
    int dummy = 42;

    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(pq));
    TEST_ASSERT_NULL(priority_queue_top(pq));
    TEST_ASSERT_FALSE(priority_queue_contains(pq, &dummy));

    priority_queue_pop(pq);
    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(pq));

    TEST_ASSERT_EQUAL_INT(0, priority_queue_remove(pq, &dummy));
}

void test_priority_queue_null_pointers(void) {
    int val = 10;

    TEST_ASSERT_EQUAL_INT(0, priority_queue_push(NULL, &val));
    TEST_ASSERT_EQUAL_INT(0, priority_queue_push(pq, NULL));

    TEST_ASSERT_EQUAL_INT(0, priority_queue_contains(NULL, &val));
    TEST_ASSERT_EQUAL_INT(0, priority_queue_contains(pq, NULL));

    TEST_ASSERT_NULL(priority_queue_top(NULL));

    priority_queue_pop(NULL);
    priority_queue_free(NULL);

    TEST_ASSERT_EQUAL_INT(0, priority_queue_remove(NULL, &val));
    TEST_ASSERT_EQUAL_INT(0, priority_queue_remove(pq, NULL));

    TEST_ASSERT_EQUAL_INT(0, priority_queue_size(NULL));
}

void test_priority_queue_capacity_resize(void) {
    int elements[50];
    for (int i = 0; i < 50; i++) {
        elements[i] = i; 
        TEST_ASSERT_EQUAL_INT(1, priority_queue_push(pq, &elements[i]));
    }

    TEST_ASSERT_EQUAL_INT(50, priority_queue_size(pq));
    
    TEST_ASSERT_EQUAL_INT(49, *(int*)priority_queue_top(pq));

    for (int i = 0; i < 50; i++) {
        TEST_ASSERT_TRUE(priority_queue_contains(pq, &elements[i]));
    }
}

void test_priority_queue_remove_non_existent(void) {
    int v1 = 10, v2 = 20, non_existent = 99;

    priority_queue_push(pq, &v1);
    priority_queue_push(pq, &v2);

    TEST_ASSERT_EQUAL_INT(0, priority_queue_remove(pq, &non_existent));
    TEST_ASSERT_EQUAL_INT(2, priority_queue_size(pq));
}

void test_priority_queue_heap_property_after_multiple_pops(void) {
    int vals[] = {15, 3, 42, 8, 99, 23, 4, 16};
    int num_elements = sizeof(vals) / sizeof(vals[0]);

    for (int i = 0; i < num_elements; i++) {
        priority_queue_push(pq, &vals[i]);
    }

    int prev = 99999; 
    
    while (priority_queue_size(pq) > 0) {
        int curr = *(int*)priority_queue_top(pq);
        TEST_ASSERT_LESS_OR_EQUAL_INT(prev, curr); 
        prev = curr;
        priority_queue_pop(pq);
    }
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_priority_queue_common_cases);
    RUN_TEST(test_priority_queue_empty_operations);
    RUN_TEST(test_priority_queue_null_pointers);
    RUN_TEST(test_priority_queue_capacity_resize);
    RUN_TEST(test_priority_queue_remove_non_existent);
    RUN_TEST(test_priority_queue_heap_property_after_multiple_pops);

    return UNITY_END();
}