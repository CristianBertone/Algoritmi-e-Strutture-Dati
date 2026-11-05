#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

typedef struct {
    int id;
    int start;
    int length;
    int priority;
} Task;


int compare_task_priority(const void* a, const void* b) {
    Task* t1 = (Task*)a;
    Task* t2 = (Task*)b;
    return t1->priority - t2->priority;
}


int compare_task_start(const void* a, const void* b) {
    Task* t1 = *(Task**)a;
    Task* t2 = *(Task**)b;
    return t1->start - t2->start;
}


unsigned long hash_task(const void* key) {
    return (unsigned long)((Task*)key)->id;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <file_csv>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("Errore apertura file");
        return 1;
    }

    // Vettore dinamico per leggere un numero ignoto di task
    int capacity = 100;
    Task** task_list = malloc(capacity * sizeof(Task*));
    int total_tasks = 0;
    
    char line[128];
    while (fgets(line, sizeof(line), f)) {
        Task* t = malloc(sizeof(Task));
        if (sscanf(line, "%d,%d,%d,%d", &t->id, &t->start, &t->length, &t->priority) == 4) {
            if (total_tasks == capacity) {
                capacity *= 2;
                task_list = realloc(task_list, capacity * sizeof(Task*));
            }
            task_list[total_tasks++] = t;
        } else {
            free(t);
        }
    }
    fclose(f);

    qsort(task_list, total_tasks, sizeof(Task*), compare_task_start);
    PriorityQueue* pq = priority_queue_create(compare_task_priority, hash_task);
    
    printf("ID,StartTime,EndTime\n");
    
    int t = 0;
    int idx = 0;

    while (idx < total_tasks || priority_queue_size(pq) > 0) {

        if (priority_queue_size(pq) == 0 && idx < total_tasks && task_list[idx]->start > t) {
            t = task_list[idx]->start;
        }

        while (idx < total_tasks && task_list[idx]->start <= t) {
            priority_queue_push(pq, task_list[idx]);
            idx++;
        }

        if (priority_queue_size(pq) > 0) {
            Task* current_task = priority_queue_top(pq);
            priority_queue_pop(pq);
            
            int end_time = t + current_task->length;
            printf("%d,%d,%d\n", current_task->id, t, end_time);
            t = end_time; 
        }
    }

    priority_queue_free(pq);
    for (int i = 0; i < total_tasks; i++) free(task_list[i]);
    free(task_list);

    return 0;
}