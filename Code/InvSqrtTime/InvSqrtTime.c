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

int main() {
  clock_t t1 = 0, t2 = 0, t3 = 0;
  double number = 0;
  double invSqrtNum = 0;

  while (scanf("%lf", &number)) {
    t1 = clock();
    invSqrtNum = sqrt(number);
    invSqrtNum = 1 / invSqrtNum;
    printf("1/Sqrt(): %.4f\n", invSqrtNum);

    t2 = clock();
    invSqrtNum = Q_rsqrt(number);
    printf("InvSqrt():%.4f\n", invSqrtNum);

    t3 = clock();

    printf("1/Sqrt(): %ld(ms)\nInvSqrt(): %ld(ms)\nRatio: %lf\n", t2 - t1, t3 - t2, ((float)t2 - (float)t1) / ((float)t3 - (float)t2));
  }

  return 0;
}
