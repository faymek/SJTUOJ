#include <iostream>
using namespace std;
const int maxn = 100000 + 5;

int P[maxn], Q[maxn], V[maxn], F[maxn] = {0}, queue[maxn];
int N, root;

void preOrder(int r = root)
{
    cout << V[r] << ' ';
    int m = P[r];
    while (m)
    {
        preOrder(m);
        m = Q[m];
    }
}

void postOrder(int r = root)
{
    int m = P[r];
    while (m)
    {
        postOrder(m);
        m = Q[m];
    }
    cout << V[r] << ' ';
}

void levelOrder()
{
    int front = 0, rear = 0, cur = 0, m = 0;
    queue[++rear] = root;
    while (front < rear)
    {
        cur = queue[++front];
        cout << V[cur] << ' ';

        m = P[cur];
        while (m)
        {
            queue[++rear] = m;
            m = Q[m];
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        cin >> P[i] >> Q[i] >> V[i];
        F[P[i]] = F[Q[i]] = 1;
    }
    for (int i = 1; i <= N; ++i)
        if(!F[i])
        {
            root = i;
            break;
        }
    
    preOrder();
    cout << endl;
    postOrder();
    cout << endl;
    levelOrder();
    cout << endl;
    return 0;
}
