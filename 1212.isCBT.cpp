#include <iostream>
using namespace std;
const int maxn = 100000 + 5;

int P[maxn], Q[maxn], F[maxn]={0}, queue[maxn];

int find(int n)
{
    return F[n]?find(F[n]):n;
}

int main()
{
    int N, root;
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        cin >> P[i] >> Q[i];
        F[P[i]] = i;
        F[Q[i]] = i;
    }
    root = find(1);

    int front = 0, rear = 0, cur = 0, full = 1;
    queue[++rear] = root;
    while (front < rear)
    {
        cur = queue[++front];
        if (P[cur])
        {
            queue[++rear] = P[cur];
            if (!full)
                break;
        }
        else
            full = 0;
        
        if (Q[cur])
        {
            queue[++rear] = Q[cur];
            if (!full)
                break;
        }
        else
            full = 0;
    }

    if (rear == front)
        cout << "Y\n";
    else
        cout << "N\n";
    return 0;
}
