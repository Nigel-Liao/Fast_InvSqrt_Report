#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float FastInvSqrt(float number);

int main() {
  float x = 0;
  time_t t;

  srand((unsigned)time(&t));

  int N = 1000000;
  int i = 0;

  double sum_time2 = 0.0;

  do {
    x = (float)(rand() % 10000) * 0.22158;
    clock_t start2 = clock();
    float z = 1.0 / sqrt(x);
    clock_t end2 = clock();
    sum_time2 = sum_time2 + (end2 - start2);
    i++;
  } while (i < N);

  printf("1/sqrt() spends %13f sec.\n\n", sum_time2 / (double)CLOCKS_PER_SEC);

  double sum_time1 = 0.0;

  i = 0;
  do

  {
    x = (float)(rand() % 10000) * 0.22158;
    clock_t start1 = clock();
    float y = FastInvSqrt(x);
    clock_t end1 = clock();
    sum_time1 = sum_time1 + (end1 - start1);
    i++;
  } while (i < N);

  printf("FastInvSqrt() spends %f sec.\n\n", sum_time1 / (double)CLOCKS_PER_SEC);

  printf("fast inverse square root is faster %f times than 1/sqrt().\n", sum_time2 / sum_time1);

  return 0;
}

float FastInvSqrt(float x) {
  float xhalf = 0.5F * x;
  int i = *(int *)&x;            // store floating-point bits in integer
  i = 0x5f3759df - (i >> 1);     // initial guess for Newton's method
  x = *(float *)&i;              // convert new bits into float
  x = x * (1.5 - xhalf * x * x); // One round of Newton's method
  // x = x * (1.5 - xhalf * x * x);      // One round of Newton's method
  // x = x * (1.5 - xhalf * x * x);      // One round of Newton's method
  // x = x * (1.5 - xhalf * x * x);      // One round of Newton's method
  return x;
}