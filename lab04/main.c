#include <gsl/gsl_blas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// A – Matrix n x m
// B – Matrix m x p
// C – Matrix n x p
double **naive_multiplication(double **A, double **B, int n, int p, int m) {
    double **C = (double **)calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        C[i] = (double *)calloc(p, sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < m; k++)
                C[i][j] = A[i][k] * B[k][j];

    return C;
}

// A – Matrix n x m
// B – Matrix m x p
// C – Matrix n x p
double **better_multiplication(double **A, double **B, int n, int p, int m) {
    double **C = (double **)calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        C[i] = (double *)calloc(p, sizeof(double));

    for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++)
            for (int j = 0; j < p; j++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j];

    return C;
}

// A – Matrix n x m
void destruct(double **A, int n, int m) {
    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
}

double **random_square_matrix(int n) {
    srand(time(NULL));
    double **A = (double **)calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        A[i] = (double *)calloc(n, sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = (double)rand() / RAND_MAX;

    return A;
}

double *random_square_array(int n) {
    srand(time(NULL));
    double *A = (double *)calloc(n * n, sizeof(double));
    for (int i = 0; i < n * n; i++)
        A[i] = (double)rand() / RAND_MAX;
    return A;
}

double *zeros_square_array(int n) {
    srand(time(NULL));
    double *A = (double *)calloc(n * n, sizeof(double));
    return A;
}

void print_matrix(double **A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%lf ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv) {
    FILE *csv = fopen(argv[1], "w");

    clock_t start_time;
    clock_t end_time;

    fprintf(csv, "n;naive;better;gsl\n");

    for (int n = 10; n <= 100; n += 10) {
        for (int i = 0; i < 10; i++) {
            // Prepare matrices
            double **A = random_square_matrix(n);
            double **B = random_square_matrix(n);
            double *tC = random_square_array(n);
            double *tD = random_square_array(n);
            double *tE = zeros_square_array(n);
            gsl_matrix_view C = gsl_matrix_view_array(tC, n, n);
            gsl_matrix_view D = gsl_matrix_view_array(tD, n, n);
            gsl_matrix_view E = gsl_matrix_view_array(tE, n, n);

            // Naive
            start_time = clock();
            double **F = naive_multiplication(A, B, n, n, n);
            end_time = clock();
            fprintf(csv, "%d;%lf;", n, (double)(end_time - start_time) / CLOCKS_PER_SEC);
            destruct(F, n, n);

            // Better
            start_time = clock();
            double **G = better_multiplication(A, B, n, n, n);
            end_time = clock();
            fprintf(csv, "%lf;", (double)(end_time - start_time) / CLOCKS_PER_SEC);
            destruct(G, n, n);

            // GSL
            start_time = clock();
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &C.matrix, &D.matrix, 0.0, &E.matrix);
            end_time = clock();
            fprintf(csv, "%lf\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

            // Free memory
            destruct(A, n, n);
            destruct(B, n, n);
            free(tC);
            free(tD);
            free(tE);
        }
    }

    fclose(csv);

    return 0;
}