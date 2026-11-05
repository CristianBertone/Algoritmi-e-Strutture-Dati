#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "hybrid_sort.h"

int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

void setUp(void) {}
void tearDown(void) {}


void test_sorted_array(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    
    hybridsort(arr, 5, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
}

void test_reverse_array(void) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    
    hybridsort(arr, 5, sizeof(int), 3, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
}

void test_empty_array(void) {
    int arr[] = {0}; 
    hybridsort(arr, 0, sizeof(int), 10, cmp_int);
    TEST_ASSERT_TRUE(1); 
}

void test_single_element(void) {
    int arr[] = {42};
    int expected[] = {42};
    
    hybridsort(arr, 1, sizeof(int), 10, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 1);
}


void test_identical_elements(void) {
    int arr[] = {7, 7, 7, 7, 7};
    int expected[] = {7, 7, 7, 7, 7};
    
    hybridsort(arr, 5, sizeof(int), 2, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
}

void test_negative_and_positive_numbers(void) {
    int arr[] = {3, -1, 4, -5, 0, 2};
    int expected[] = {-5, -1, 0, 2, 3, 4};
    
    hybridsort(arr, 6, sizeof(int), 3, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 6);
}


void test_threshold_extremes(void) {
    int arr1[] = {9, 2, 5, 1, 8};
    int expected[] = {1, 2, 5, 8, 9};
    
    hybridsort(arr1, 5, sizeof(int), 0, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr1, 5);

    int arr2[] = {9, 2, 5, 1, 8};
    hybridsort(arr2, 5, sizeof(int), 100, cmp_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr2, 5);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_array);
    RUN_TEST(test_single_element);
    RUN_TEST(test_sorted_array);
    RUN_TEST(test_reverse_array);
    RUN_TEST(test_identical_elements);
    RUN_TEST(test_negative_and_positive_numbers);
    RUN_TEST(test_threshold_extremes);

    return UNITY_END();
}