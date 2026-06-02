#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void friendly_numbers(long int start, long int end) {
	double inicio;	
	int c=0;
	long int last = end - start + 1;

	long int *the_num;
	the_num = (long int*) malloc(sizeof(long int) * last);
	long int *num;
	num = (long int*) malloc(sizeof(long int) * last);
	long int *den;
	den = (long int*) malloc(sizeof(long int) * last);

	long int i, j, factor, ii, sum, done, n;

	for (i = start; i <= end; i++) {
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
	
	for (i = 0; i < last; i++) {
		for (j = i + 1; j < last; j++) {
			if ((num[i] == num[j]) && (den[i] == den[j]))
				c++;
		}
	}
	printf("Founded %d pairs of mutually friendly numbers\n", c);

	free(the_num);
	free(num);
	free(den);
}

int main(int argc, char **argv) {
	long int start;
	long int end;

	//scanf("%ld %ld", &start, &end);
	start = atoi(argv[1]);
	end = atoi(argv[2]);
	printf("Number %ld to %ld\n", start, end);
	friendly_numbers(start, end);

	return EXIT_SUCCESS;
}
