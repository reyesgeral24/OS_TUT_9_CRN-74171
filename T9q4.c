#include <stdio.h>
#include <omp.h>

#define N 100

int main (int argc, char *argv[])
{
    int a[N][N], b[N][N];
    int c_parallel[N][N], c_sequential[N][N];

    int nthreads = 8;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    // Initialize matrices
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = i + j;      // based on index
            b[i][j] = i - j;      // based on index
            c_parallel[i][j] = 0;
            c_sequential[i][j] = 0;
        }
    }

    printf("Running parallel matrix multiplication...\n");

    // ✅ Parallel multiplication (OpenMP)
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                c_parallel[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    printf("Running sequential matrix multiplication...\n");

    // ✅ Sequential version (verification tool)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                c_sequential[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // ✅ Verify correctness
    int correct = 1;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(c_parallel[i][j] != c_sequential[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    if(correct)
        printf("Verification PASSED: Parallel result is correct.\n");
    else
        printf("Verification FAILED: Results do not match.\n");

    // Print sample value
    printf("Sample result c[0][0] = %d\n", c_parallel[0][0]);

    return 0;
}