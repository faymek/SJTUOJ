#include <iostream>
using namespace std;

template <class T>
class bernPQ
{
  private:
    struct node
    {
        node *son, *peer;
        int height;
        T data;

        node() : son(NULL), peer(NULL), height(1) {}
        node(T item, node *s = NULL, node *p = NULL, int h = 1) : data(item), son(s), peer(p), height(h) {}
        ~node();
    };
    node **a;
    int curSize;
    int maxSize;

    void doubleSpace();
    void buildTree(const T *items, int size);
    bernPQ breakTree(node *x);
    void merge(bernPQ &x);
    node *mergeTree(node *x, node *y)
    {
        if (x->data > y->data)
        {
            node *tmp = x;
            x = y;
            y = tmp;
        }
        ++x->height;
        if (x->son)
        {
            node *p = x->son;
            while (p->peer)
                p = p->peer;
            p->peer = y;
        }
        else
            x->son = y;
        return x;
    }

  public:
    bernPQ(int size = 5)
    {
        a = new node *[size];
        maxSize = size;
        curSize = 0;
    }
    bernPQ(const T &x, char)
    {
        a = new node *[1];
        a[0] = new node(x);
        maxSize = 1;
        curSize = 1;
    }
    ~bernPQ() { delete[] a; }

    bool isEmpty() const { return !curSize; }
    void enQueue(const T &x);
    void deQueue();
    T getHead();
    void display()
    {
        for (int i = 0; i < curSize; ++i)
            if(a[i]) cout << a[i]->data << ' ';
            else cout << "~ ";
        cout << endl;
    }
};

template <class T>
void bernPQ<T>::doubleSpace()
{
    node **tmp = a;
    maxSize *= 2;
    a = new node *[maxSize];
    for (int i = 0; i < curSize; ++i)
        a[i] = tmp[i];
    delete[] tmp;
}

template <class T>
bernPQ<T> bernPQ<T>::breakTree(node *x)
{
    int size = x->height - 1;
    bernPQ<T> tmp(size + 5);
    node *p = x->son, *q = NULL;
    int i = 0;
    while (p)
    {
        q = p->peer;
        p->peer = NULL;
        tmp.a[i++] = p;
        p = q;
    }
    tmp.curSize = size;
    return tmp;
}

template <class T>
void bernPQ<T>::merge(bernPQ &x)
{
    int size = max(curSize, x.curSize);
    if (maxSize <= size)
        doubleSpace();
    node *newTree = NULL, *carry = NULL;
    for (int i = 0; i < size; ++i)
    {
        newTree = NULL;
        if ((i < curSize) && (i < x.curSize) && a[i] && x.a[i])
            newTree = mergeTree(a[i], x.a[i]);
        else if ((i < curSize) && a[i])
            newTree = a[i];
        else if (i < x.curSize)
            newTree = x.a[i];
        else
            newTree = NULL;

        if (newTree && newTree->height == i + 2)
        {
            a[i] = carry;
            carry = newTree;
        }
        else if (newTree && newTree->height == i + 1)
        {
            if (carry)
            {
                a[i] = NULL;
                carry = mergeTree(carry, newTree);
            }
            else
            {
                a[i] = newTree;
            }
        }
        else
        {
            a[i] = carry;
            carry = NULL;
        }
    }
    
    a[size] = carry;
    for (int i = size; i >= 0; --i)
        if (a[i])
        {
            curSize = i + 1;
            break;
        }
}

template <class T>
void bernPQ<T>::enQueue(const T &x)
{
    bernPQ<T> tmp(x, '0');
    merge(tmp);
}

template <class T>
void bernPQ<T>::deQueue()
{
    int m = curSize - 1;
    for (int i = 0; i < curSize; ++i)
        if (a[i] && (a[i]->data) < (a[m]->data))
            m = i;
    bernPQ t = breakTree(a[m]);
    a[m] = NULL;
    merge(t);
}

template <class T>
T bernPQ<T>::getHead()
{
    int m = curSize-1;
    for (int i = 0; i < curSize; ++i)
        if (a[i] && (a[i]->data) < (a[m]->data))
            m = i;
    return a[m]->data;
}

int main()
{
    bernPQ<int> pq;
    int M = 0, arg = 0;
    char cmd[10];
    cin >> M;
    for (int i = 0; i < M; ++i)
    {
        cin >> cmd;
        if (cmd[0] == 'i')
        {
            cin >> arg;
            pq.enQueue(arg);
        }
        else if (cmd[0] == 'd')
            pq.deQueue();
        else if (cmd[0] == 'm')
            cout << pq.getHead() << endl;
        // pq.display();
    }

    return 0;
}
