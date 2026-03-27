#include <stdio.h>
#include <omp.h>

int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;

    // If OpenMP is enabled, set how many threads will be used
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    printf("Testing OpenMP, you should see each thread print...\n");

    // Starts the parallel part of the program
    #pragma omp parallel
    {
        // only one thread runs this part at a time
        #pragma omp critical
        {
            // Only runs this part if OpenMP is active
            #ifdef _OPENMP
            thread_num = omp_get_thread_num();
            num += 1;
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }

    return 0;
}