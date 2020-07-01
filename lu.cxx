#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MaxN 1010
#define infilename "LU.in"
#define outfilename "LU_bx.out"
#ifndef NUM_OF_THREADS
#define NUM_OF_THREADS 4
#endif 
FILE *fin, *fout;                    // fin 为输入文件fout 为输出文件
double A[MaxN][MaxN];                // A 为原矩阵
double L[MaxN][MaxN], U[MaxN][MaxN]; // L 和U 为分解后的矩阵
int n;                               // n 为矩阵行数
int nthreads, tid;
int init() {
  int i, j;
  fscanf(fin, "%d", &n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fscanf(fin, "%lf", &A[i][j]);
  omp_set_num_threads(NUM_OF_THREADS);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      L[i][j] = 0;
      U[i][j] = 0;
    }
  for (i = 0; i < n; i++)
    L[i][i] = 1;
  return 0;
}
int factorize() {
  int i, j, k;
#pragma omp parallel shared(A) private(tid, i, j, k)
  {
    for (k = 0; k < n; k++) {
#pragma omp for
      for (i = k + 1; i < n; i++)
        A[i][k] = A[i][k] / A[k][k];
#pragma omp for
      for (i = k + 1; i < n; i++)
        for (j = k + 1; j < n; j++) {
          A[i][j] = A[i][j] - A[i][k] * A[k][j];
        }
    }
  }
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (i <= j)
        U[i][j] = A[i][j];
      else
        L[i][j] = A[i][j];
    }
  return 0;
}
int output() {
  int i, j;
  //输出L 矩阵
  fprintf(fout, "Matrix L:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fprintf(fout, "%.10lf%c", L[i][j], (j == n - 1) ? '\n' : ' ');
  //输出U 矩阵
  fprintf(fout, "Matrix U:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fprintf(fout, "%.10lf%c", U[i][j], (j == n - 1) ? '\n' : ' ');
  return 0;
}
int main() {
  double ts, te;
  fin = fopen(infilename, "r");
  fout = fopen(outfilename, "w");
  //初始化
  init();
  //矩阵分解
  ts = omp_get_wtime();
  factorize();
  te = omp_get_wtime();
  printf("time = %f s\n", te - ts);
  //输出结果
  output();
  fclose(fin);
  fclose(fout);
  return 0;
}
