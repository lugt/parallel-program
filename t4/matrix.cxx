#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>

#define MATRIX_SIZE 1000
typedef int dimensions[1000];

int main(int argc, char** argv) {
  int i, j, n, k;
  dimensions *a = new dimensions[MATRIX_SIZE];
  dimensions *b = new dimensions[MATRIX_SIZE];
  dimensions *c = new dimensions[MATRIX_SIZE];
  //  int b[MATRIX_SIZE][MATRIX_SIZE];
  //  int c[MATRIX_SIZE][MATRIX_SIZE];
  int cnt = 4;
  if (argc > 1) {
    cnt = atoi(argv[1]);
  }

  omp_set_num_threads(cnt);
  
  n = MATRIX_SIZE; //Max 719

  printf("Matrix A\n");

 
  {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        a[i][j] = rand();
      }
    }
  }
  
  printf("\nMatrix B\n");

  clock_t start = clock();    
  {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        b[i][j] = rand();
      }
    }
  }

  printf("\nA * B\n");

  {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        c[i][j] = 0;
      }
    }
  }

  {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        for (k = 0; k < n; ++k) {
          c[i][j] += a[i][k] * b[k][i];
        }
      }
    }
  }

  clock_t stop = clock();
  
  {
    for (i = MATRIX_SIZE; i < MATRIX_SIZE; ++i) {
      printf("%d\n", c[i][0]);
    }
  }


  double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
  printf("\nTime elapsed: %.5f\n", elapsed);
  return 0;
}
