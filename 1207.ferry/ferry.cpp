#include <iostream>
#include <cstdio>
using namespace std;

int A[20005], B[20005];
int pA = 1, lenA = 0, pB = 1, lenB = 0;
const int maxt = 1000000 + 5;

int main()
{
    int n, p, q;
    int t = 0, sumA = 0, sumB = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p >> q;
        if (p)
            B[++lenB] = q;
        else
            A[++lenA] = q;
    }
    A[lenA + 1] = B[lenB + 1] = maxt;

    t = 0;
    while (pA <= lenA || pB <= lenB)
    {
        int m = 0;
        for (; m < 8; ++m)
        {
            if (A[pA] > t)
                break;
            sumA += t - A[pA++];
        }
        for (; m < 10; ++m)
        {
            if (B[pB] > t)
                break;
            sumB += t - B[pB++];
        }
        for (; m < 10; ++m)
        {
            if (A[pA] > t)
                break;
            sumA += t - A[pA++];
        }

        t = max(t + 10, min(A[pA], B[pB]));
        t = (int)((t - 1) / 10 + 1) * 10;
    }

    printf("%.3f %.3f", 1.0 * sumA / lenA, 1.0 * sumB / lenB);
    return 0;
}
