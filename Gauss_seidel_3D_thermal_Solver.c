/******************************************************************************
 * Project: Temperature Distribution in a Heated Slab
 * Description: Solves for steady-state temperatures in a 3D grid using 
 * the Gauss-Seidel iterative method.
 * Authors: Michael Muchemi (ENM213-0158/2024), Amon Kipruto (ENM213-0186/2024)
 * Date: January 2026
 *****************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Dimensions from project documentation
#define L 7
#define M 5
#define N 12
// Function to calculate the new temperature of a node based on its 6 neighbors
double calculateNodeTemp(double T[L + 1][M + 1][N + 1], int i, int j, int k) {
    return (T[i - 1][j][k] + T[i + 1][j][k] + 
            T[i][j - 1][k] + T[i][j + 1][k] + 
            T[i][j][k - 1] + T[i][j][k + 1]) / 6.0;
}

int main() {
      // 3D array to store temperatures (L+1, M+1, N+1 to include boundary indices)
    double T[L + 1][M + 1][N + 1];
    // Stopping criterion (epsilon) and iteration limits
    double epsilon = 0.0001; 
    int max_sweeps = 100;
    int sweepCount = 0;
    double cumNodeErr = 0;
    double vol = 264.0; 
    FILE *fptr;


    // 1. Initialize entire volume to 0.0
    for (int i = 0; i <= L; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= N; k++) {
                T[i][j][k] = 0.0;
            }
        }
    }

    // 2. Open the input file where boundary temperatures are stored
    fptr = fopen("input_temperature.txt", "r");
    if (fptr == NULL) {
        printf("Error: Could not open input_temperature.txt\n");
        return 1;
    } 

    // 3. Read Boundary Faces temperature (A-F)
    for (int i = 0; i <= L; i++) 
      for (int j = 0; j <= M; j++) 
          fscanf(fptr, "%lf", &T[i][j][0]);
    for (int i = 0; i <= L; i++)
       for (int j = 0; j <= M; j++) 
         fscanf(fptr, "%lf", &T[i][j][N]);
    for (int j = 0; j <= M; j++) 
      for (int k = 0; k <= N; k++)
          fscanf(fptr, "%lf", &T[L][j][k]);
    for (int j = 0; j <= M; j++) 
     for (int k = 0; k <= N; k++) 
         fscanf(fptr, "%lf", &T[0][j][k]);
    for (int i = 0; i <= L; i++)
      for (int k = 0; k <= N; k++)
         fscanf(fptr, "%lf", &T[i][M][k]);
  for (int i = 0; i <= L; i++) 
     for (int k = 0; k <= N; k++) 
       fscanf(fptr, "%lf", &T[i][0][k]);
    fclose(fptr);
 // 3. SOLVING FOR TEMPERATURE (GAUSS-SEIDEL)
    while (sweepCount < max_sweeps) {
        cumNodeErr = 0.0; 
        for (int i = 1; i < L; i++) {
            for (int j = 1; j < M; j++) {
                for (int k = 1; k < N; k++) {
                    double previousTemp = T[i][j][k];
                    T[i][j][k] = calculateNodeTemp(T, i, j, k);
                    cumNodeErr += fabs(T[i][j][k] - previousTemp);
                }
            }
        }
        sweepCount++;
        if ((cumNodeErr / vol) <= epsilon) break; 
    }


    // 5. EXPORT TO FILE
    FILE *fptr_out = fopen("output.txt", "w");
    if (fptr_out != NULL) {
        for (int i = 0; i <= L; i++) {
            for (int j = 0; j <= M; j++) {
                for (int k = 0; k <= N; k++) {
                    fprintf(fptr_out, "%d %d %d %lf\n", i, j, k, T[i][j][k]);
                }
            }
        }
        fclose(fptr_out);
    }
    
 // 5. Group Results Output
    printf("==================================================\n");
    printf("             GROUP PROJECT RESULTS               \n");
    printf("==================================================\n");
    printf("Sweeps completed: %d\n", sweepCount);
    printf("Final average error: %.6f\n", cumNodeErr / vol);


    // 6. DAY 3: PRINT SPECIFIC PLANES
    printf("\n--- TEMPERATURE DISTRIBUTION AT PLANE i = 3 ---\n");
    for (int j = 0; j <= M; j++) {
        for (int k = 0; k <= N; k++) printf("%.2f\t", T[3][j][k]);
        printf("\n");
    }

    printf("\n--- TEMPERATURE DISTRIBUTION AT PLANE j = 3 ---\n");
    for (int i = 0; i <= L; i++) {
        for (int k = 0; k <= N; k++) printf("%.2f\t", T[i][3][k]);
        printf("\n");
    }

    printf("\n--- TEMPERATURE DISTRIBUTION AT PLANE k = 3 ---\n");
    for (int i = 0; i <= L; i++) {
        for (int j = 0; j <= M; j++) printf("%.2f\t", T[i][j][3]);
        printf("\n");
    }

    return 0; 
}