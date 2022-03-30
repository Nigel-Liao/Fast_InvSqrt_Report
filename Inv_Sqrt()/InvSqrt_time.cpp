#include "assert.h"
#include "iostream"
#include "math.h"
#include "stdio.h"
#include "time.h"
using namespace std;

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

    /*
    #ifndef Q3_VM
    #ifdef __linux__
        assert(!isnan(y)); // bk010122 - FPE?
    #endif
    #endif
    */

    return y;
}

int main()
{
    clock_t t1 = 0, t2 = 0, t3 = 0;
    float number = 0;
    float invSqrtNum = 0;

    while (cin >> number)
    {
        t1 = clock();
        invSqrtNum = sqrt(number);
        invSqrtNum = 1 / invSqrtNum;
        printf("%f\n", invSqrtNum);

        t2 = clock();
        invSqrtNum = Q_rsqrt(number);
        printf("%f\n", invSqrtNum);

        t3 = clock();

        printf("1/Sqrt(): %ld(ms)\nInvSqrt(): %ld(ms)\nRatio: %ld\n", t2 - t1, t3 - t2, (t2 - t1) / (t3 - t2));
    }
}