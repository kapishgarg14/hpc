#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Hello world from process %s, rank %d out of %d processes\n\n",
           processor_name, world_rank, world_size);
    if (world_rank == 0)
    {
        char message[] = "Hello!";
        MPI_Send(message, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        char message[6];
        MPI_Recv(message, 6, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Message received!\n");
        printf("Message is : %s\n", message);
    }
    MPI_Finalize();
    return 0;
}