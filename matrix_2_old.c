#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 1e-10 /* 許容する誤差 */

double **createMatrix(unsigned int m, unsigned int n) {
  double **mat;
  unsigned int i, j;

  if (n == 0 || m == 0) {
    printf("n or m is 0\n");
    return NULL;
  }

  /* m行分のポインタ格納用のメモリを確保 */
  mat = malloc(sizeof(double *) * m);
  if (mat == NULL) {
    return NULL;
  }

  for (i = 0; i < m; i++) {
    /* 1行分ずつメモリを確保する */

    /* n列分のint型のデータが格納できるメモリを確保 */
    mat[i] = malloc(sizeof(double) * n);
    if (mat[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(mat[i]);
      }
      free(mat);
      return NULL;
    }
  }

  return mat;
}

void showMatrix(unsigned int m, unsigned int n, double **A) {
  for (int i = 0; i < m; i++) {
    printf("{ ");
    for (int j = 0; j < n; j++) {
      printf("%lf ", A[i][j]);
    }
    printf("}\n");
  }
  printf("\n");
}

void inputMatrix(unsigned int m, unsigned int n, double **A) {
  printf("Matrix: %dx%d\n", m, n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("A[%d][%d]:", i, j);
      scanf("%lf", &A[i][j]);
    }
  }
  showMatrix(m, n, A);
}

/**************************************
 * 行列用のメモリを解放
 * m：行列の行数
 * 返却値：なし
 **************************************/
void deleteMatrix(double **mat, unsigned int m) {
  for (int i = 0; i < m; i++) {
    free(mat[i]);
  }

  free(mat);
}

int main() {
  double **A;
  int m, n;

  printf("n:");
  scanf("%d", &n);
  printf("m:");
  scanf("%d", &m);

  /* m行n列の行列用のメモリを確保 */
  A = createMatrix(m, n);
  if (A == NULL) {
    printf("メモリ確保エラー\n");
    return 0;
  }

  // A[0][0] = 1;
  // A[0][1] = 1;
  // A[0][2] = 1;
  // A[0][3] = 1;
  inputMatrix(m, n, A);
  showMatrix(m, n, A);

  // **A[0] = 0;
}
