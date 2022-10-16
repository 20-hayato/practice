#include <math.h>
#include <stdio.h>

#define MAX_ERR 1e-10 /* 許容する誤差 */

void ShowMatrix(double C[3][3]) {
  for (int i = 0; i < 3; i++) {
    printf("{ ");
    for (int j = 0; j < 3; j++) {
      printf("%f ", C[i][j]);
    }
    printf("}\n");
  }
  printf("\n");
}

void Plus(double A[3][3], double B[3][3]) {
  double C[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  ShowMatrix(C);
}

void Minus(double A[3][3], double B[3][3]) {
  double C[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
  ShowMatrix(C);
}

void Cross(double A[3][3], double B[3][3]) {
  double C[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j];
      // printf("C[%d][%d]:%f\n", i, j, C[i][j]);
    }
  }
  ShowMatrix(C);
}

double Determinant(double A[3][3]) {
  double det_A = A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] +
                 A[0][2] * A[1][0] * A[2][1] - A[0][2] * A[1][1] * A[2][0] -
                 A[0][1] * A[1][0] * A[2][2] - A[0][0] * A[1][2] * A[2][1];
  return det_A;
}

// 余因子で求める
void Inverse1(double A[3][3]) {
  double det_A = Determinant(A);
  double A_inv[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double elem[4] = {0.0, 0.0, 0.0, 0.0};
      int counter = 0;
      for (int l = 0; l < 3; l++) {   // i:l
        for (int m = 0; m < 3; m++) { // j:m
          if (i != l && j != m) {
            // printf("counter:%d\n", counter);
            elem[counter] = A[l][m];
            counter++;
          }
        }
      }
      // printf("%f,%f,%f,%f\n", elem[0], elem[1], elem[2], elem[3]);
      if (det_A != 0.0) {
        A_inv[j][i] = pow((-1.0), (double)(i + j)) * 1.0 / det_A *
                      (elem[0] * elem[3] - elem[1] * elem[2]);
      } else {
        printf("Error : division by zero");
      }
    }
  }
  ShowMatrix(A_inv);
}

void Inverse2(double A[3][3]) {
  double sweep[3][3 * 2];
  double inv_A[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      /* sweepの左側に逆行列を求める行列をセット */
      sweep[i][j] = A[i][j];

      /* sweepの右側に単位行列をセット */
      sweep[i][3 + j] = (i == j) ? 1 : 0;
    }
  }

  /* 全ての列の対角成分に対する繰り返し */
  for (int k = 0; k < 3; k++) {
    /* 最大の絶対値を注目対角成分の絶対値と仮定 */
    double max = fabs(sweep[k][k]);
    int max_i = k;

    /* k列目が最大の絶対値となる行を探す */
    for (int i = k + 1; i < 3; i++) {
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
      for (int j = 0; j < 3 * 2; j++) {
        double tmp = sweep[max_i][j];
        sweep[max_i][j] = sweep[k][j];
        sweep[k][j] = tmp;
      }
    }

    /* 全ての列の対角成分に対する繰り返し */
    for (int k = 0; k < 3; k++) {
      /* sweep[k][k]に掛けると1になる値を求める */
      double a = 1 / sweep[k][k];
      /* 操作（２）：k行目をa倍する */
      for (int j = 0; j < 3 * 2; j++) {
        /* これによりsweep[k][k]が1になる */
        sweep[k][j] *= a;
      }
      /* 操作（３）によりk行目以外の行のk列目を0にする */
      for (int i = 0; i < 3; i++) {
        if (i == k) {
          /* k行目はそのまま */
          continue;
        }
        /* k行目に掛ける値を求める */
        a = -sweep[i][k];
        for (int j = 0; j < 3 * 2; j++) {
          /* i行目にk行目をa倍した行を足す */
          /* これによりsweep[i][k]が0になる */
          sweep[i][j] += sweep[k][j] * a;
        }
      }
    }

    /* sweepの右半分がmatの逆行列 */
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        inv_A[i][j] = sweep[i][3 + j];
      }
    }
  }
  /* 逆行列invを表示 */
  ShowMatrix(inv_A);
}

int main() {
  double A[3][3] = {{6.0, 7.0, 3.0}, {8.0, 2.0, 9.0}, {2.0, 6.0, 9.0}};
  double B[3][3] = {{3.0, 3.0, 9.0}, {4.0, 1.0, 3.0}, {8.0, 9.0, 5.0}};
  printf("A:\n");
  ShowMatrix(A);
  printf("B:\n");
  ShowMatrix(B);

  printf("A+B:\n");
  Plus(A, B);

  printf("A-B:\n");
  Minus(A, B);

  printf("A*B:\n");
  Cross(A, B);

  printf("invA1:\n");
  Inverse1(A);

  printf("invA2:\n");
  Inverse2(A);
}
