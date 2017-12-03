#include <iostream>
using namespace std;

template <class T>
class Set
{
    template <class U>
    friend Set<U> operator*(const Set<U> &x, const Set<U> &y);
    template <class U>
    friend Set<U> operator+(const Set<U> &x, const Set<U> &y);
    template <class U>
    friend Set<U> operator-(const Set<U> &x, const Set<U> &y);

  private:
    T *elem;
    int size, maxSize;

    void doubleSpace()
    {
        maxSize *= 2;
        T *tmp = new T[maxSize];
        for (int i = 0; i < size; ++i)
            tmp[i] = elem[i];
        delete[] elem;
        elem = tmp;
    }

    int find(T x) const
    {
        for (int i = 0; i < size; ++i)
            if (elem[i] == x)
                return i;
        return -1;
    }

    void qsort(int s, int t)
    {
        if (s >= t)
            return;
        int i = s, j = t, mid = elem[(s + t) >> 1];
        while (i <= j)
        {
            while (elem[i] < mid)
                ++i;
            while (elem[j] > mid)
                --j;
            if (i <= j)
            {
                int tem = elem[i];
                elem[i] = elem[j];
                elem[j] = tem;
                ++i;
                --j;
            }
        }
        qsort(s, j);
        qsort(i, t);
    }

  public:
    Set()
    {
        size = 0;
        maxSize = 10;
        elem = new T[maxSize];
    }

    Set(const Set<T> &x)
    {
        size = x.size;
        maxSize = x.maxSize;
        elem = new T[maxSize];
        for (int i = 0; i < size; ++i)
            elem[i] = x.elem[i];
    }

    Set<T> &operator=(const Set<T> &x)
    {
        size = x.size;
        maxSize = x.maxSize;
        delete[] elem;
        elem = new T[maxSize];
        for (int i = 0; i < size; ++i)
            elem[i] = x.elem[i];
        return *this;
    }

    bool insert(T &x)
    {
        if (find(x) != -1)
            return false;
        if (size == maxSize)
            doubleSpace();
        elem[size++] = x;
        return true;
    }

    bool del(T &x)
    {
        int pos = find(x);
        if (pos == -1)
            return false;
        for (int i = pos; i < size - 1; ++i)
            elem[i] = elem[i + 1];
        return true;
    }

    void display()
    {
        qsort(0, size - 1);
        for (int i = 0; i < size; ++i)
            cout << elem[i] << " ";
        cout << '\n';
    }
};

template <class T>
Set<T> operator*(const Set<T> &x, const Set<T> &y)
{
    Set<T> z;
    for (int i = 0; i < x.size; ++i)
        if (y.find(x.elem[i]) != -1)
            z.insert(x.elem[i]);
    return z;
}

template <class T>
Set<T> operator+(const Set<T> &x, const Set<T> &y)
{
    Set<T> z = x;
    for (int i = 0; i < y.size; ++i)
        z.insert(y.elem[i]);
    return z;
}

template <class T>
Set<T> operator-(const Set<T> &x, const Set<T> &y)
{
    Set<T> z;
    for (int i = 0; i < x.size; ++i)
        if (y.find(x.elem[i]) == -1)
            z.insert(x.elem[i]);
    return z;
}

int main()
{
    int n, m, a;
    char c;
    Set<int> x;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> c;
        cin >> m;
        Set<int> y;
        for (int j = 0; j < m; ++j)
        {
            cin >> a;
            y.insert(a);
        }

        if (c == '*')
            x = x * y;
        else if (c == '+')
            x = x + y;
        else if (c == '-')
            x = x - y;
        x.display();
    }
    return 0;
}