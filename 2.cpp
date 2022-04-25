#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
// it is a message passing interface
// processes live inside a COMM_WORLD
// processes are LIVING, and exist in a COMMUNICATOR
int main(int argc, char **argv)
{
    // start the MPI code
    MPI_Init(NULL, NULL);
    int num_procs; // to store the size of the world / num of procs MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        // read the array
        int n;
        printf("Enter number of elements : ");
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 10000 + 1;
        }
        printf("Array is -\n [ ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("]\n");
        int elem_to_send = n / 2;
        if (n % 2)
            elem_to_send++;
        // send the size
        MPI_Send(&elem_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // send the array
        MPI_Send(&arr[n / 2], elem_to_send, MPI_INT, 1, 1, MPI_COMM_WORLD);
        float t1 = clock();
        int local = 0;
        for (int i = 0; i < n / 2; i++)
            local = local + arr[i];
        int s_rec = 0;
        float t2 = clock();
        printf("Time taken by process %d : %f\n", rank, (t2 - t1) / CLOCKS_PER_SEC);
        // recv the data into the local var s_rec
        MPI_Recv(&s_rec, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        local = local + s_rec;
        printf("Total sum of array is %d\n", local);
    }
    else
    {
        // recieve the size of elements
        float t1 = clock();
        int size;
        MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int arr[size];
        MPI_Recv(arr, size, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        float t2 = clock();
        printf("Total time for recieving : %f", (t2 - t1) / CLOCKS_PER_SEC);
        // lol, the time for recieving the elements is a thousand times slower // than the processing, lol waste
        t1 = clock();
        int local = 0;
        for (int i = 0; i < size; i++)
            local = local + arr[i];
        printf("\nProcess %d sending sum %d back to main...\n", rank, local);
        t2 = clock();
        printf("Time taken by process for addition %d : %f\n", rank, (t2 - t1) / CLOCKS_PER_SEC);
        MPI_Send(&local, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}