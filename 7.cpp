#include <omp.h>
#include <stdio.h>
int main()
{
    int num_threads, THREAD_COUNT = 4;
    int thread_ID;
    int section_sizes[4] = {
        0, 100, 200, 300};
    printf("Work load sharing of threads...\n");
#pragma omp parallel private(thread_ID) num_threads(THREAD_COUNT)
    {
        thread_ID = omp_get_thread_num();
        printf("I am thread number %d!\n", thread_ID);
        int value_count = 0;
        if (thread_ID > 0)
        {
            int work_load = section_sizes[thread_ID];
            for (int i = 0; i < work_load; i++)
                value_count++;
            printf("Number of values computed : %d\n", value_count);
        }
#pragma omp barrier
        if (thread_ID == 0)
        {
            printf("Total number of threads are %d\n", omp_get_num_threads());
        }
    }
    return 0;
}