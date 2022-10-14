#include <stdio.h>
#include <stdlib.h>

/**************************************
 * m行n列の行列用のメモリを確保（成分の型はint）
 * m：行列の行数
 * n：行列の列数
 * 返却値：確保したメモリの先頭アドレス（失敗時はNULL）
 **************************************/
int **createMatrix(unsigned int m, unsigned int n) {
  int **mat;
  unsigned int i, j;

  if (n == 0 || m == 0) {
    printf("n or m is 0\n");
    return NULL;
  }

  /* m行分のポインタ格納用のメモリを確保 */
  mat = malloc(sizeof(int *) * m);
  //   printf("%p\n", mat);
  if (mat == NULL) {
    return NULL;
  }

  for (i = 0; i < m; i++) {
    /* 1行分ずつメモリを確保する */

    /* n列分のint型のデータが格納できるメモリを確保 */
    mat[i] = malloc(sizeof(int) * n);
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

/**************************************
 * 行列用のメモリを解放
 * m：行列の行数
 * 返却値：なし
 **************************************/
void deleteMatrix(int **mat, unsigned int m) {
  unsigned int i;

  for (i = 0; i < m; i++) {
    free(mat[i]);
  }

  free(mat);
}

int main(void) {

  /* 行列を指すポインタ */
  int **matA;

  int m, n; /* 実際に扱う行数の行数と列数 */
  int i, j;

  /* ユーザーから行数と列数の入力を受け付ける */
  printf("行数：");
  scanf("%d", &m);
  printf("列数：");
  scanf("%d", &n);

  /* m行n列の行列用のメモリを確保 */
  matA = createMatrix(m, n);
  if (matA == NULL) {
    printf("メモリ確保エラー\n");
    return 0;
  }

  /* 以降ではmatAをm行n列の行列として扱う */

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      matA[i][j] = n * i + j;
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%d,", matA[i][j]);
    }
    printf("\n");
  }

  /* 行列用のメモリを解放 */
  deleteMatrix(matA, m);

  return 0;
}