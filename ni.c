#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>



#define NUM_THREADS 4  // Change this to test with different thread counts

// Function to integrate: f(x) = x^2
double f(double x) {
    return x * x;
}

// Sequential Trapezoidal Integration
double trapezoidal_sequential(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

// Parallel Trapezoidal Integration using OpenMP
double trapezoidal_parallel(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum)
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

int main() {
    double a = 0.0, b = 10.0;  // Integration range
    int n = 1000000;           // Number of trapezoids (increase for better accuracy)
    double seq_time, par_time, result_seq, result_par;

    // Sequential Execution
    double start = omp_get_wtime();
    result_seq = trapezoidal_sequential(a, b, n);
    seq_time = omp_get_wtime() - start;

    // Parallel Execution
    start = omp_get_wtime();
    result_par = trapezoidal_parallel(a, b, n);
    par_time = omp_get_wtime() - start;

    // Output results
    printf("Sequential Result: %.6f, Time: %.6f seconds\n", result_seq, seq_time);
    printf("Parallel Result  : %.6f, Time: %.6f seconds\n", result_par, par_time);
    printf("Speedup: %.2fx\n", seq_time / par_time);

    return 0;
}
