#include "dec.h"

int main()
{
    int A = 100;
    int B = -100;

    int *strA = &A;
    int *strB = &B;

    int &refA = A;
    int &refB = B;

    inverseByStr(strA, strB);
    inverseByRef(refA, refB);

    return 0;
}