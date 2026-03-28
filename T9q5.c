#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    // ✅ Check command line argument
    if(argc < 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);

    long n = 100000000; // 100 million
    double dx = 1.0 / (n + 1);

    FILE *fp = fopen("calculations.txt", "w");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Running with %d threads...\n", num_threads);

    #pragma omp parallel
    {
        double x, y; // private variables

        #pragma omp for
        for(long i = 0; i <= n; i++)
        {
            x = i * dx;
            y = exp(x) * cos(x) * sin(x) * sqrt(5 * x + 6.0);

            // Every 1,000,000th iteration
            if(i % 1000000 == 0)
            {
                #pragma omp critical
                {
                    fprintf(fp, "i=%ld x=%f y=%f\n", i, x, y);
                }
            }
        }
    }

    fclose(fp);
    printf("Done. Output written to calculations.txt\n");

    return 0;
}