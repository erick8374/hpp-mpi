#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

typedef long li;

/* Recursiva
int gcd(int u, int v) {
	if (v == 0)
		return u;
	return gcd(v, u % v);
}
*/

/* Standard C Function: Greatest Common Divisor */
int gcd ( int a, int b ){
  	int c;
	while ( a != 0 ) {
     	c = a; 
		a = b % a;  
		b = c;
	}
  	return b;
}

void friendly_numbers(li start, li end, int meurank, int procs) {
	double inicio;	
	int c_slice = 0; // cont pares encontrados no proc
	int c_total = 0;
	li last = end - start + 1;

	li chunk = last / procs; // fatia
	li remainder = last % procs; // resto

	li *the_num;
	the_num = (li*) malloc(sizeof(li) * last);
	li *num;
	num = (li*) malloc(sizeof(li) * last);
	li *den;
	den = (li*) malloc(sizeof(li) * last);

	// vars globais para usar com o mpi
	li *num_recv;
	num_recv = (li*) malloc(sizeof(li) * last);
	li *den_recv;
	den_recv = (li*) malloc(sizeof(li) * last);

	li i, j, factor, ii, sum, done, n;

	// desloc do vet global
	li ix_start = meurank * chunk + (meurank < remainder ? meurank : remainder);
	li tam_slice = chunk + (meurank < remainder ? 1 : 0);
	
    // mapeamento da fatia local com os alvos - start e end
    li actual_start = start + ix_start;
    li actual_end = actual_start + tam_slice;

	for (i = actual_start; i < actual_end; i++) {
		ii = i - start;
		sum = 1 + i;
		the_num[ii] = i;
		done = i;
		factor = 2;
		while (factor < done) {
			if ((i % factor) == 0) {
				sum += (factor + (i / factor));
				if ((done = i / factor) == factor)
					sum -= factor;
			}
			factor++;
		}
		num[ii] = sum;
		den[ii] = i;
		n = gcd(num[ii], den[ii]);
		num[ii] /= n;
		den[ii] /= n;
	} // end for	

	// procs somam os vets num e den e guardam nas var globais
    MPI_Allreduce(num, num_recv, last, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(den, den_recv, last, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);
	
	for (i = meurank; i < last; i+=procs) {
		for (j = i + 1; j < last; j++) {
			if ((num_recv[i] == num_recv[j]) && (den_recv[i] == den_recv[j]))
				c_slice++;
		}
	}
	MPI_Reduce(&c_slice, &c_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (meurank == 0)
		printf("Founded %d pairs of mutually friendly numbers\n", c_total);

	free(the_num);
	free(num);
	free(den);
    free(num_recv);
    free(den_recv);
}

int main(int argc, char **argv) {

	int procs, meurank;
	li start, end, last;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &meurank);

	start = atoi(argv[1]);
	end = atoi(argv[2]);

	if (meurank == 0) 
		printf("Number %ld to %ld\n", start, end);

	// check para validar num de procs
	if (procs != 2 && procs != 4 && procs != 8 && procs != 16 && procs != 32) {
        if (meurank == 0)
            printf("Error! Number of proccess incorrect, try: [2|4|8|16|32]\n");		
		MPI_Finalize();
		return EXIT_FAILURE;
    }

	//scanf("%ld %ld", &start, &end);
	
	friendly_numbers(start, end, meurank, procs);

    MPI_Finalize();
	return EXIT_SUCCESS;
}