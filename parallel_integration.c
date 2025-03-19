#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>



#define NUM_THREADS 4  // Set the number of threads

// Function to integrate: f(x) = x^2
double f(double x) {
    return x * x;
}

// Parallel Trapezoidal Integration using OpenMP
double trapezoidal_parallel(double a, double b, int n, int chunk_size) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b)); // First and last terms

    #pragma omp parallel for num_threads(NUM_THREADS) schedule(dynamic, chunk_size) reduction(+:sum)
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

int main() {
    double a = 0.0, b = 10.0;  // Integration range
    int n = 1000000;           // Number of trapezoids (increase for better accuracy)
    int chunk_size = n / NUM_THREADS; // Calculate chunk size dynamically
    double result;
    double start, end;

    // Measure execution time
    start = omp_get_wtime();
    result = trapezoidal_parallel(a, b, n, chunk_size);
    end = omp_get_wtime();

    // Output results
    printf("Parallel Result: %.6f\n", result);
    printf("Execution Time: %.6f seconds\n", end - start);
    printf("Chunk Size Used: %d\n", chunk_size);

    return 0;
}
