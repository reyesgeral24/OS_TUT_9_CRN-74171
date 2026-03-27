#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int nthreads = atoi(argv[1]);

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    long int n = 100000000;

    double *y = (double*) malloc(n * sizeof(double));
    if (y == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    double dx = 1.0 / (n + 1);

    double start = omp_get_wtime();

    double x; 
    #pragma omp parallel for private(x)
    for (long int i = 0; i < n; i++) {
        x = i * dx;

        y[i] = exp(x) * cos(x) * sin(x) * sqrt(5.0 * x + 6.0);
    }

    double end = omp_get_wtime();

    printf("Execution time with %d threads: %f seconds\n", nthreads, end - start);

    printf("y[0] = %f, y[n-1] = %f\n", y[0], y[n-1]);

    free(y);

    return 0;
}