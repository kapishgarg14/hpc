#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int thread_count;

struct arguments
{
    int size;
    int *arr1;
    int *arr2;
    int *dot;
};
void *add_into_one(void *arguments);
void print_vector(int n, int *arr)
{
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("] \n");
}

int main(int argc, char *argv[])
{
    long thread;

    pthread_t *thread_handles;
    thread_count = 2;

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    printf("Enter the size of the vectors : ");
    int n;
    scanf("%d", &n);
    printf("Enter the max_val of the vectors : ");
    int max_val;
    scanf("%d", &max_val);
    struct arguments *args[2];
    for (int i = 0; i < 2; i++)
    {
        args[i] = malloc(sizeof(struct arguments) * 1);
        args[i]->size = n;
        args[i]->arr1 = malloc(sizeof(int) * n);
        args[i]->arr2 = malloc(sizeof(int) * n);
        args[i]->dot = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            args[i]->arr1[j] = rand() % max_val;
            args[i]->arr2[j] = rand() % max_val;
        }
    }
    printf("Vectors are : \n");
    print_vector(n, args[0]->arr1);
    print_vector(n, args[0]->arr2);
    print_vector(n, args[1]->arr1);
    print_vector(n, args[1]->arr2);
    int result[n];
    memset(result, 0, n * sizeof(int));
    for (thread = 0; thread < thread_count; thread++)
    {
        printf("Multiplying %ld and %ld with thread %ld...\n", thread + 1, thread + 2,
               thread);
        pthread_create(&thread_handles[thread], NULL, add_into_one, (void *)args[thread]);
    }
    printf("Hello from the main thread\n");
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);
    for (int i = 0; i < 2; i++)
    {
        printf("Multiplication for vector %d and %d \n", i + 1, i + 2);
        print_vector(n, args[i]->dot);
        printf("\n");
    }
    free(thread_handles);
    for (int i = 0; i < n; i++)
        result[i] = args[0]->dot[i] + args[1]->dot[i];
    printf("Result is : \n");
    print_vector(n, result);
    return 0;
}
void *add_into_one(void *argument)
{
    struct arguments *args = argument;
    int n = args->size;
    for (int i = 0; i < n; i++)
        args->dot[i] = args->arr1[i] * args->arr2[i];
    return NULL;
}