#include "assert.h"
#include "math.h"
#include "stdio.h"

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;           // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y)); // 1st iteration
    //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

#ifndef Q3_VM
#ifdef __linux__
    assert(!isnan(y)); // bk010122 - FPE?
#endif
#endif
    return y;
}

float Q_fabs(float f)
{
    int tmp = *(int *)&f;
    tmp &= 0x7FFFFFFF;
    return *(float *)&tmp;
}

int main()
{
    float number = 0;
    float invSqrtNum = 0;

    scanf("Enter a Number: %f", &number);

    invSqrtNum = 1 / sqrt(number);
    printf("%f", invSqrtNum);

    Q_rsqrt(number);
    printf("%f", invSqrtNum);
}