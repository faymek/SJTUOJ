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

    int getSize() { return curSize;}
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

    int findUB(T x)
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

    void increase(int i, const T &v)
    {
        a[i] += v;
        percolateDown(i);
    }

    int findLB(T x)
    {
        int maxvalue = -2147483648, maxpos = 1;
        for (int i = 1; i <= curSize; ++i)
            if (a[i] <= x && a[i] > maxvalue)
            {
                maxpos = i;
                maxvalue = a[i];
            }
        return maxpos;
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
    pq<double> q;
    double w;
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> w;
        q.enQUeue(w); 
    }

    for (int i = 0; i < n; ++i)
    {
        double head = q.getHead();
        int pos = q.findLB(1-head);
        if(pos ==  1) break;
        q.increase(pos, head);
        q.deQueue();
    }

    cout << q.getSize() << endl;
    return 0;
}    