#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




// Function to integrate: f(x) = x^2
double f(double x) {
    return x * x;
}

// Sequential Trapezoidal Integration
double trapezoidal_sequential(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b)); // First and last terms

    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return sum * h;
}

int main() {
    double a = 0.0, b = 10.0;  // Integration range
    int n = 1000000;           // Number of trapezoids (increase for better accuracy)
    double result;
    clock_t start, end;
    double time_spent;

    // Measure time
    start = clock();
    result = trapezoidal_sequential(a, b, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Output results
    printf("Sequential Result: %.6f\n", result);
    printf("Execution Time: %.6f seconds\n", time_spent);

    return 0;
}
