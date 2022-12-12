#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M 1
#define K 10
#define C 2

double fx(double x, double dx, double u) { return dx; }
double fdx(double x, double dx, double u) {
  return -K / M * x - C / M * dx + 1 / M * u;
}

int main() {
  FILE *outputfile; // 出力ストリーム

  outputfile = fopen("data.txt", "w");
  if (outputfile == NULL) {
    printf("cannot open\n");
    exit(1);
  }

  double x = 4.0;
  double dx = -7.0;
  double u = 0.0; // 0入力
  double k_x = 0.0;
  double k1_x = 0.0;
  double k2_x = 0.0;
  double k3_x = 0.0;
  double k4_x = 0.0;
  double k_dx;
  double k1_dx = 0.0;
  double k2_dx = 0.0;
  double k3_dx = 0.0;
  double k4_dx = 0.0;

  double dt = 0.001;
  double t_end = 10.0; // [sec] 0 start
  for (int i = 0; i < t_end / dt + 1; i++) {
    k1_x = dt * fx(x, dx, u);
    k2_x = dt * fx(x + dt / 2, dx + k1_x / 2, u);
    k3_x = dt * fx(x + dt / 2, dx + k2_x / 2, u);
    k4_x = dt * fx(x + dt, dx + k3_x, u);
    k1_dx = dt * fdx(x, dx, u);
    k2_dx = dt * fdx(x + dt / 2, dx + k1_dx / 2, u);
    k3_dx = dt * fdx(x + dt / 2, dx + k2_dx / 2, u);
    k4_dx = dt * fdx(x + dt, dx + k3_dx, u);

    k_x = (k1_x + 2 * k2_x + 2 * k3_x + k4_x) / 6;
    k_dx = (k1_dx + 2 * k2_dx + 2 * k3_dx + k4_dx) / 6;

    x = x + k_x;
    dx = dx + k_dx;

    fprintf(outputfile, "%f %f %f\n", i * dt, x, dx);
  }

  fclose(outputfile);
  return 0;
}
