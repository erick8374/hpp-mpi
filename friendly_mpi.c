#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int gcd(int a, int b) { ... } // igual ao original

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Validação do número de processos (exigência do trabalho)
    if (size != 2 && size != 4 && size != 8 && size != 16 && size != 32) {
        if (rank == 0)
            printf("Erro: use 2, 4, 8, 16 ou 32 processos.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    long int start = atol(argv[1]);
    long int end   = atol(argv[2]);
    long int N = end - start + 1;

    // --- Divisão do intervalo por processo ---
    long int chunk = N / size;
    long int resto = N % size;
    long int local_start = start + rank * chunk;
    long int local_end   = local_start + chunk - 1;
    if (rank == size - 1) local_end += resto; // último pega o resto

    long int local_size = local_end - local_start + 1;

    // --- Etapa 1: cada processo calcula sua fatia ---
    long int *local_num = malloc(sizeof(long int) * local_size);
    long int *local_den = malloc(sizeof(long int) * local_size);

    for (long int i = local_start; i <= local_end; i++) {
        long int ii = i - local_start;
        long int sum = 1 + i;
        long int done = i, factor = 2;
        while (factor < done) {
            if (i % factor == 0) {
                sum += factor + (i / factor);
                if ((done = i / factor) == factor)
                    sum -= factor;
            }
            factor++;
        }
        local_num[ii] = sum;
        local_den[ii] = i;
        long int g = gcd(local_num[ii], local_den[ii]);
        local_num[ii] /= g;
        local_den[ii] /= g;
    }

    // --- Etapa 2: reunir tudo no processo 0 ---
    // (ou usar Allgather para todos contarem)
    long int *all_num = NULL, *all_den = NULL;
    int *recvcounts = NULL, *displs = NULL;

    if (rank == 0) {
        all_num = malloc(sizeof(long int) * N);
        all_den = malloc(sizeof(long int) * N);
        recvcounts = malloc(sizeof(int) * size);
        displs     = malloc(sizeof(int) * size);
    }

    // Informa ao processo 0 quantos elementos cada um enviará
    int my_count = (int)local_size;
    MPI_Gather(&my_count, 1, MPI_INT,
               recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        displs[0] = 0;
        for (int i = 1; i < size; i++)
            displs[i] = displs[i-1] + recvcounts[i-1];
    }

    MPI_Gatherv(local_num, my_count, MPI_LONG,
                all_num, recvcounts, displs, MPI_LONG, 0, MPI_COMM_WORLD);
    MPI_Gatherv(local_den, my_count, MPI_LONG,
                all_den, recvcounts, displs, MPI_LONG, 0, MPI_COMM_WORLD);

    // --- Etapa 3: processo 0 conta os pares ---
    if (rank == 0) {
        long int c = 0;
        for (long int i = 0; i < N; i++)
            for (long int j = i + 1; j < N; j++)
                if (all_num[i] == all_num[j] && all_den[i] == all_den[j])
                    c++;
        printf("Founded %ld pairs of mutually friendly numbers\n", c);

        free(all_num); free(all_den);
        free(recvcounts); free(displs);
    }

    free(local_num); free(local_den);
    MPI_Finalize();
    return EXIT_SUCCESS;
}