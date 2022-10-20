#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ERR 1e-10 /* 許容する誤差 */

double **CreateMatrix(unsigned int m, unsigned int n) {
  double **A;
  unsigned int i, j;

  if (n == 0 || m == 0) {
    printf("n or m is 0\n");
    return NULL;
  }

  /* m行分のポインタ格納用のメモリを確保 */
  A = malloc(sizeof(double *) * m);
  if (A == NULL) {
    return NULL;
  }

  for (i = 0; i < m; i++) {
    /* 1行分ずつメモリを確保する */

    /* n列分のint型のデータが格納できるメモリを確保 */
    A[i] = malloc(sizeof(double) * n);
    if (A[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(A[i]);
      }
      free(A);
      return NULL;
    }
  }

  return A;
}

void ShowMatrix(unsigned int m, unsigned int n, double **A) {
  for (int i = 0; i < m; i++) {
    printf("{ ");
    for (int j = 0; j < n; j++) {
      printf("%lf ", A[i][j]);
    }
    printf("}\n");
  }
  printf("\n");
}

void InputMatrix(unsigned int m, unsigned int n, double **A) {
  printf("Matrix: %dx%d\n", m, n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("A[%d][%d]:", i, j);
      scanf("%lf", &A[i][j]);
    }
    printf("\n");
  }
  ShowMatrix(m, n, A);
}

void DeleteMatrix(double **A, unsigned int m) {
  for (int i = 0; i < m; i++) {
    free(A[i]);
  }
  free(A);
}

void Plus(unsigned int m, unsigned int n, double **A, double **B,
          double **ans) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      ans[i][j] = A[i][j] + B[i][j];
    }
  }
  ShowMatrix(m, n, ans);
}

void Minus(unsigned int m, unsigned int n, double **A, double **B,
           double **ans) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      ans[i][j] = A[i][j] - B[i][j];
    }
  }
  ShowMatrix(m, n, ans);
}

void Cross(unsigned int l, unsigned int m, unsigned int n, double **A,
           double **B, double **ans) {
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++) {
      ans[i][j] = 0.0;
      for (int k = 0; k < m; k++) {
        ans[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  ShowMatrix(l, n, ans);
}

void Inverse(unsigned int m, double **A, double **ans) {
  double sweep[m][m * 2];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      /* sweepの左側に逆行列を求める行列をセット */
      sweep[i][j] = A[i][j];
      /* sweepの右側に単位行列をセット */
      sweep[i][m + j] = (i == j) ? 1 : 0;
    }
  }

  /* 全ての列の対角成分に対する繰り返し */
  for (int k = 0; k < m; k++) {
    /* 最大の絶対値を注目対角成分の絶対値と仮定 */
    double max = fabs(sweep[k][k]);
    int max_i = k;

    /* k列目が最大の絶対値となる行を探す */
    for (int i = k + 1; i < m; i++) {
      if (fabs(sweep[i][k]) > max) {
        max = fabs(sweep[i][k]);
        max_i = i;
      }
    }

    if (fabs(sweep[max_i][k]) <= MAX_ERR) {
      /* 逆行列は求められない */
      printf("逆行列は求められません...\n");
      break;
    }

    /* 操作（１）：k行目とmax_i行目を入れ替える */
    if (k != max_i) {
      for (int j = 0; j < m * 2; j++) {
        double tmp = sweep[max_i][j];
        sweep[max_i][j] = sweep[k][j];
        sweep[k][j] = tmp;
      }
    }

    /* 全ての列の対角成分に対する繰り返し */
    for (int k = 0; k < m; k++) {
      /* sweep[k][k]に掛けると1になる値を求める */
      double a = 1 / sweep[k][k];
      /* 操作（２）：k行目をa倍する */
      for (int j = 0; j < m * 2; j++) {
        /* これによりsweep[k][k]が1になる */
        sweep[k][j] *= a;
      }
      /* 操作（３）によりk行目以外の行のk列目を0にする */
      for (int i = 0; i < m; i++) {
        if (i == k) {
          /* k行目はそのまま */
          continue;
        }
        /* k行目に掛ける値を求める */
        a = -sweep[i][k];
        for (int j = 0; j < m * 2; j++) {
          /* i行目にk行目をa倍した行を足す */
          /* これによりsweep[i][k]が0になる */
          sweep[i][j] += sweep[k][j] * a;
        }
      }
    }

    /* sweepの右半分がmatの逆行列 */
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        ans[i][j] = sweep[i][m + j];
      }
    }
  }
  /* 逆行列invを表示 */
  ShowMatrix(m, m, ans);
}

int main() {
  double **A = CreateMatrix(3, 3);
  InputMatrix(3, 3, A);
  double **B = CreateMatrix(3, 3);
  InputMatrix(3, 3, B);
  double **ans = CreateMatrix(3, 3);
  // double A[3][3] = {{6.0, 7.0, 3.0}, {8.0, 2.0, 9.0}, {2.0, 6.0, 9.0}};
  // double B[3][3] = {{3.0, 3.0, 9.0}, {4.0, 1.0, 3.0}, {8.0, 9.0, 5.0}};
  printf("------------\n");
  printf("A:\n");
  ShowMatrix(3, 3, A);
  printf("B:\n");
  ShowMatrix(3, 3, B);

  printf("A+B:\n");
  Plus(3, 3, A, B, ans);

  printf("A-B:\n");
  Minus(3, 3, A, B, ans);

  printf("A*B:\n");
  Cross(3, 3, 3, A, B, ans);

  printf("invA:\n");
  Inverse(3, A, ans);

  DeleteMatrix(A, 3);
  DeleteMatrix(B, 3);
  DeleteMatrix(ans, 3);
}
