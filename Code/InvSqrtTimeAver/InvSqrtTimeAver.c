#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

float Q_rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y)); // 1st iteration

  return y;
}

float N_rsqrt(float number) {
  number = sqrt(number);
  number = 1 / number;

  return number;
}

long tSqrt = 0;
long tQsqrt = 0;

int main() {
  clock_t t1 = 0, t2 = 0, t3 = 0;
  double number = 0, M = 0;
  double invSqrtNum = 0;
  double Ratio = 0;

  t1 = clock();

  for (double i = 0.0001; i <= 1; i += 0.0001) {
    number = i;
    invSqrtNum = N_rsqrt(number);
    // printf("%f\n", invSqrtNum);
  }
  t2 = clock();

  for (double i = 1.0; i <= M; i++) {
    number = i;
    invSqrtNum = Q_rsqrt(number);
    // printf("%f\n", invSqrtNum);
  }
  t3 = clock();

  tSqrt = t2 - t1;
  tQsqrt = t3 - t2;

  Ratio = (double)(tSqrt) / (double)(tQsqrt);
  printf("%ld\n%ld\n%lf\n", tSqrt, tQsqrt, Ratio);

  return 0;
}