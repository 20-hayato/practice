#include <math.h>
#include <stdio.h>

void MatrixShow(double C[3][3]) {
  for (int i = 0; i < 3; i++) {
    printf("{ ");
    for (int j = 0; j < 3; j++) {
      printf("%f ", C[i][j]);
    }
    printf("}\n");
  }
  printf("\n");
}

void MatrixPlus(double A[3][3], double B[3][3]) {
  double C[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  MatrixShow(C);
}

void MatrixMinus(double A[3][3], double B[3][3]) {
  double C[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
  MatrixShow(C);
}

void MatrixCross(double A[3][3], double B[3][3]) {
  double C[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j];
      // printf("C[%d][%d]:%f\n", i, j, C[i][j]);
    }
  }
  MatrixShow(C);
}

double MatrixDeterminant(double A[3][3]) {
  double det_A = A[0][0] * A[1][1] * A[2][2] + A[0][1] * A[1][2] * A[2][0] +
                 A[0][2] * A[1][0] * A[2][1] - A[0][2] * A[1][1] * A[2][0] -
                 A[0][1] * A[1][0] * A[2][2] - A[0][0] * A[1][2] * A[2][1];
  return det_A;
}

// 余因子で求める
void MatrixInverse(double A[3][3]) {
  double det_A = MatrixDeterminant(A);
  double A_inv[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double elem[4] = {0.0, 0.0, 0.0, 0.0};
      int counter = 0;
      for (int l = 0; l < 3; l++) {   // i:l
        for (int m = 0; m < 3; m++) { // j:m
          if (i != l && j != m) {
            printf("counter:%d\n", counter);
            elem[counter] = A[l][m];
            counter++;
          }
        }
      }
      printf("%f,%f,%f,%f\n", elem[0], elem[1], elem[2], elem[3]);
      if (det_A != 0.0) {
        A_inv[j][i] = pow((-1.0), (double)(i + j)) * 1.0 / det_A *
                      (elem[0] * elem[3] - elem[1] * elem[2]);
      } else {
        printf("Error : division by zero");
      }
    }
  }
  MatrixShow(A_inv);
}

int main() {
  double A[3][3] = {{6.0, 7.0, 3.0}, {8.0, 2.0, 9.0}, {2.0, 6.0, 9.0}};
  double B[3][3] = {{3.0, 3.0, 9.0}, {4.0, 1.0, 3.0}, {8.0, 9.0, 5.0}};
  MatrixShow(A);
  MatrixShow(B);

  MatrixPlus(A, B);
  MatrixMinus(A, B);
  MatrixCross(A, B);
  MatrixInverse(A);
}
