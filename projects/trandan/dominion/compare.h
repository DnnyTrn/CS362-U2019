#ifndef compare_h
#define compare_h

int assertTrue(int x)
{
    if (x == 0)
        printf("assertion failed: x == %d \n", x);
    return x != 0;
}

int isSame(int val1, int val2)
{
    return val1 == val2;
}

#endif