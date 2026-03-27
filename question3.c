#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 100000000

int main(void)
{
    int *x = (int *)malloc(N * sizeof(int));
    if (x == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    srand(42);
    for (int i = 0; i < N; i++) {
        x[i] = rand() % 101;
    }

    double norm_serial = 0.0;
    double start_serial = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        norm_serial += abs(x[i]);
    }
    double end_serial = omp_get_wtime();
    double time_serial = end_serial - start_serial;

    printf("Serial norm: %f\n", norm_serial);
    printf("Serial time: %f seconds\n\n", time_serial);

    double norm_parallel = 0.0;
    omp_set_num_threads(16);

    double start_parallel = omp_get_wtime();
    #pragma omp parallel for reduction(+:norm_parallel)
    for (int i = 0; i < N; i++) {
        norm_parallel += abs(x[i]);
    }
    double end_parallel = omp_get_wtime();
    double time_parallel = end_parallel - start_parallel;

    printf("Parallel norm: %f\n", norm_parallel);
    printf("Parallel time: %f seconds\n\n", time_parallel);

    printf("Time difference: %f seconds\n", time_serial - time_parallel);
    printf("Speedup: %.2fx\n", time_serial / time_parallel);

    free(x);
    return 0;
}
