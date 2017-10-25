#include <iostream>
using namespace std;
const int maxn = 100000 + 5;

int P[maxn], Q[maxn], V[maxn], F[maxn]={0}, queue[maxn];

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
        cin >> P[i] >> Q[i] >> V[i];
        F[P[i]] = i;
        F[Q[i]] = i;
    }
    root = find(1);

    int front = 0, rear = 0, cur = 0;
    queue[++rear] = root;
    while (front < rear)
    {
        cur = queue[++front];
        if (P[cur])
            queue[++rear] = P[cur];
        if (Q[cur])
            queue[++rear] = Q[cur];
        cout << V[cur] << ' ';
    }

    cout << endl;
    return 0;
}
