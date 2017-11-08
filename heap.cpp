#include <iostream>
using namespace std;
template <class T>
class pq
{
  private:
    int curSize;
    T *a;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

  public:
    pq(int size = 3)
    {
        a = new T[size];
        maxSize = size;
        curSize = 0;
    }
    pq(const T data[], int size);
    ~pq() { delete[] a; }

    bool isEmpty() const { return !curSize; }
    void enQUeue(const T &x);
    T deQueue();
    T getHead() const { return a[1]; }

    void decrease(int i, const T &v)
    {
        a[i] -= v;
        T x = a[i];
        for (; i > 1 && x < a[i / 2]; i /= 2)
            a[i] = a[i / 2];
        a[i] = x;
    }

    int find(T &x)
    {
        int minvalue = 2147483647, minpos;
        for (int i = 1; i <= curSize; ++i)
            if (a[i] > x && a[i] < minvalue)
            {
                minpos = i;
                minvalue = a[i];
            }
        return minpos;
    }
};

template <class T>
void pq<T>::enQUeue(const T &x)
{
    if (curSize == maxSize - 1)
        doubleSpace();
    int hole = ++curSize;
    for (; hole > 1 && x < a[hole / 2]; hole /= 2)
        a[hole] = a[hole / 2];
    a[hole] = x;
}

template <class T>
T pq<T>::deQueue()
{
    T minItem = a[1];
    a[1] = a[curSize--];
    percolateDown(1);
    return minItem;
}

template <class T>
void pq<T>::percolateDown(int hole)
{
    int child;
    T tmp = a[hole];
    for (; hole * 2 <= curSize; hole = child)
    {
        child = hole * 2;
        if (child != curSize && a[child + 1] < a[child])
            ++child;
        if (a[child] < tmp)
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

template <class T>
void pq<T>::buildHeap()
{
    for (int i = curSize / 2; i > 0; --i)
        percolateDown(i);
}

template <class T>
pq<T>::pq(const T *items, int size) : maxSize(size + 10), curSize(size)
{
    a = new T[maxSize];
    for (int i = 0; i < size; ++i)
        a[i + 1] = items[i];
    buildHeap();
}

template <class T>
void pq<T>::doubleSpace()
{
    T *tmp = a;
    maxSize *= 2;
    a = new T[maxSize];
    for (int i = 0; i <= curSize; ++i)
        a[i] = tmp[i];
    delete[] tmp;
}

int main()
{
    pq<int> q;
    int M = 0, arg1 = 0, arg2 = 0;
    char cmd[10];
    cin >> M;
    for (int i = 0; i < M; ++i)
    {
        cin >> cmd;
        cin >> arg1;
        if (cmd[0] == 'i')
            q.enQUeue(arg1);
        else if (cmd[0] == 'd')
        {
            cin >> arg2;
            q.decrease(arg1, arg2);
        }
        else if (cmd[0] == 'f')
            cout << q.find(arg1) << endl;
    }

    return 0;
}