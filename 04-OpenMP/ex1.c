#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10;
    int a[N], b[N], c[N];

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        b[i] = i * 2;
        c[i] = i * 3;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = b[i] + c[i];
        printf("Thread %d computes a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
    }

    return 0;
}
