
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define LENGTH 1000000000

unsigned countBitsStd(unsigned long arg);
unsigned countBitsStd2(unsigned long arg);
unsigned countBits(unsigned long arg);
unsigned countBits2(unsigned long arg);
unsigned countBits3(unsigned long arg);
unsigned countBits4(unsigned long arg);
unsigned countBits5(unsigned long arg);

void printInBinary(unsigned long num, char *str)
{
    int stri = 0;
    unsigned long x = 0x8000000000000000;
    while (x)
    {
        if (num & x)
        {
            str[stri] = '1';
        }
        else
        {
            str[stri] = '0';
        }

        stri++;
        x >>= 1;
    }
}
unsigned long randomizeULong()
{
    unsigned long x = (unsigned long)rand();
    return (x << 33) | ((x + 0x50505) << 2) | ((x + 0x030303) >> 29);
}

char binaryStr[sizeof(char) * 65] = {0};

int main(void)
{
    srand(time(NULL));

    unsigned long *nums = malloc(LENGTH * sizeof(unsigned long));
    unsigned *res = malloc(LENGTH * sizeof(unsigned));

    long time;

    time = clock();
    for (int i = 0; i < LENGTH; i += 100)
    {
        unsigned long x = randomizeULong();
        for (int j = 0; j < 100; j++)
        {
            nums[i + j] = x + j;
        }
    }
    printf("randomized numbers in %ld\n", clock() - time);

    // time = clock();
    // for (int i = 0; i < LENGTH; i++)
    // {
    //     res[i] = countBitsStd(nums[i]);
    // }
    // printf("computed std way the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits(nums[i]);
    }
    printf("computed opt way the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits(nums[i]);
    }
    printf("computed opt way the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits2(nums[i]);
    }
    printf("computed opt way 2 the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits3(nums[i]);
    }
    printf("computed opt way 3 the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits4(nums[i]);
    }
    printf("computed opt way 4 the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBits5(nums[i]);
    }
    printf("computed opt way 5 the number of bits for those numbers in %ld\n", clock() - time);

    time = clock();
    for (int i = 0; i < LENGTH; i++)
    {
        res[i] = countBitsStd2(nums[i]);
    }
    printf("computed std way 2 the number of bits for those numbers in %ld\n", clock() - time);

    // unsigned long x = randomizeULong();
    // printInBinary(x, binaryStr);
    // printf("number of bits in %s (%lu): %u \n", binaryStr, x, countBits4(x));
    // printf("number of bits in %s (%lu): %u / %u / %u \n", binaryStr, x, countBits(x), countBits2(x), countBits4(x));
}

unsigned countBitsStd(unsigned long arg)
{
    unsigned count = 0;

    unsigned long x = 1;
    for (int i = 0; i < 64; i++)
    {
        if (arg & x)
        {
            count++;
        }

        x <<= 1;
    }

    return count;
}

unsigned countBitsStd2(unsigned long arg)
{
    unsigned count = 0;

    while (arg)
    {
        count += arg & (unsigned)1;
        arg >>= 1;
    }

    return count;
}

unsigned countBits(unsigned long arg)
{
    arg = ((arg & 0xAAAAAAAAAAAAAAAA) >> 1) + (arg & 0x5555555555555555);
    arg = ((arg & 0xCCCCCCCCCCCCCCCC) >> 2) + (arg & 0x3333333333333333);
    arg = ((arg & 0xF0F0F0F0F0F0F0F0) >> 4) + (arg & 0x0F0F0F0F0F0F0F0F);
    arg = ((arg & 0xFF00FF00FF00FF00) >> 8) + (arg & 0x00FF00FF00FF00FF);
    arg = ((arg & 0xFFFF0000FFFF0000) >> 16) + (arg & 0x0000FFFF0000FFFF);
    arg = ((arg & 0xFFFFFFFF00000000) >> 32) + (arg & 0x00000000FFFFFFFF);

    return arg;
}

unsigned countBits2(unsigned long arg)
{
    arg = ((arg >> 1) & 0x5555555555555555) + (arg & 0x5555555555555555);
    arg = ((arg >> 2) & 0x3333333333333333) + (arg & 0x3333333333333333);
    arg = ((arg >> 4) & 0x0F0F0F0F0F0F0F0F) + (arg & 0x0F0F0F0F0F0F0F0F);
    arg = ((arg >> 8) & 0x00FF00FF00FF00FF) + (arg & 0x00FF00FF00FF00FF);
    arg = ((arg >> 16) & 0x0000FFFF0000FFFF) + (arg & 0x0000FFFF0000FFFF);
    arg = (arg >> 32) + (arg & 0x00000000FFFFFFFF);

    return arg;
}

unsigned countBits3(unsigned long arg)
{
    arg = ((arg >> 1) & 0x5555555555555555) + (arg & 0x5555555555555555);
    arg = ((arg >> 2) & 0x3333333333333333) + (arg & 0x3333333333333333);
    arg = (arg + (arg >> 4)) & 0x0F0F0F0F0F0F0F0F;
    arg = (arg + (arg >> 8)) & 0x00FF00FF00FF00FF;
    arg = (arg + (arg >> 16)) & 0x0000FFFF0000FFFF;
    arg = (arg + (arg >> 32)) & 0x00000000FFFFFFFF;

    return arg;
}

unsigned countBits4(unsigned long arg)
{
    arg = ((arg >> 1) & 0x5555555555555555) + (arg & 0x5555555555555555);
    arg = ((arg >> 2) & 0x3333333333333333) + (arg & 0x3333333333333333);
    arg = (arg + (arg >> 4)) & 0x0F0F0F0F0F0F0F0F;
    arg = arg + (arg >> 8);
    arg = arg + (arg >> 16);
    arg = arg + (arg >> 32);

    return arg & 0x00000000000000FF;
}

unsigned countBits5(unsigned long arg)
{
    arg = arg - ((arg >> 1) & 0x5555555555555555);
    arg = ((arg >> 2) & 0x3333333333333333) + (arg & 0x3333333333333333);
    arg = (arg + (arg >> 4)) & 0x0F0F0F0F0F0F0F0F;
    arg = arg + (arg >> 8);
    arg = arg + (arg >> 16);
    arg = arg + (arg >> 32);

    return arg & 0x00000000000000FF;
}
