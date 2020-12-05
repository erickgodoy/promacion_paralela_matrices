#include <iostream>
#include <omp.h>
#include <time.h>

#define dimension 500

using namespace std;

void multmat(int** A, int** B, int** C) {
    #pragma omp parallel
    {
        int i, j, k;
        #pragma omp for     
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                C[i][j] = 0;
                for (k = 0; k < dimension; k++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
            }
        }
    }
}

int main() {
    unsigned t0, t1;
    t0 = clock();
    int i, j, k;
    int** A, ** B, ** C;
    A = new int* [dimension], B = new int* [dimension], C = new int* [dimension];
    #pragma omp parallel for
    for (j = 0; j < dimension; j++) {
        A[j] = new int[dimension], B[j] = new int[dimension], C[j] = new int[dimension];
    }
    srand(time(NULL));
    #pragma omp parallel
    {
        #pragma omp for private(i,j)
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                A[i][j] = 1 + rand() % (9);
            }
        }
        #pragma omp for private(i,j)    
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                B[i][j] = 1 + rand() % (9);
            }
        }
    }
    multmat(A, B, C);
    #pragma omp parallel
    {
        #pragma omp for private(i, j)
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        #pragma omp for private(i,j)
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        #pragma omp for private(i,j)
        for (i = 0; i < dimension; i++) {
            for (j = 0; j < dimension; j++) {
                cout << C[i][j] << " ";
            }
            cout << endl;
        }
    }
    delete[] A, B, C; 
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Tiempo de Ejecucion: " << time << endl;
    return 0;
}