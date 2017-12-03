#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class bst
{
  private:
    struct node
    {
        T data;
        int count;
        node *left, *right;
        node(const T &d, node *lt = NULL, node *rt = NULL) : data(d), left(lt), right(rt), count(1) {}
    };

    node *root;

    void ins(const T &x, node *&t);
    void del(const T &x, node *&t);
    void del_lt(const T &x, node *&t);
    void del_gt(const T &x, node *&t);
    void del_in(const T &x, const T &y, node *&t);
    bool find(const T &x, node *t) const;
    bool find_ith(int i, T &x, node *t) const;
    int size(node *t) const;
    void clear(node *&t);
    void display(node *t);

  public:
    bst(node *t = NULL) : root(t) {}
    ~bst() { clear(root); }

    void ins(const T &x) { ins(x, root); }
    void del(const T &x) { del(x, root); }
    void del_lt(const T &x) { del_lt(x, root); }
    void del_gt(const T &x) { del_gt(x, root); }
    void del_in(const T &x, const T &y) { del_in(x, y, root); }
    bool find(const T &x) const { return find(x, root); }
    bool find_ith(int i, T &x) const { return find_ith(i, x, root); }

    void display() { display(root); }
};

template <class T>
bool bst<T>::find(const T &x, node *t) const
{
    if (!t)
        return false;
    if (x < t->data)
        return find(x, t->left);
    else if (x > t->data)
        return find(x, t->right);
    return true;
}

template <class T>
void bst<T>::ins(const T &x, node *&t)
{
    if (!t)
        t = new node(x);
    else if (x < t->data)
        ins(x, t->left);
    else if (x > t->data)
        ins(x, t->right);
    else
        ++t->count;
}

template <class T>
void bst<T>::del(const T &x, node *&t)
{
    if (!t)
        return;
    if (x < t->data)
        del(x, t->left);
    else if (x > t->data)
        del(x, t->right);
    else if (t->count > 1)
        --t->count;
    else if (t->left && t->right)
    {
        node *tmp = t->right;
        while (tmp->left)
            tmp = tmp->left;
        t->data = tmp->data;
        del(t->data, t->right);
    }
    else
    {
        node *tmp = t;
        t = (t->left) ? t->left : t->right;
        delete tmp;
    }
}

template <class T>
void bst<T>::del_gt(const T &x, node *&t)
{
    if (!t)
        return;
    if (x < t->data)
    {
        node *tmp = t;
        t = t->left;
        clear(tmp->right);
        delete tmp;
        del_gt(x, t);
    }
    else if (x > t->data)
        del_gt(x, t->right);
    else
        clear(t->right);
}

template <class T>
void bst<T>::del_lt(const T &x, node *&t)
{
    if (!t)
        return;
    if (x > t->data)
    {
        node *tmp = t;
        t = t->right;
        clear(tmp->left);
        delete tmp;
        del_lt(x, t);
    }
    else if (x < t->data)
        del_lt(x, t->left);
    else
        clear(t->left);
}

template <class T>
void bst<T>::del_in(const T &x, const T &y, node *&t)
{
    if (!t)
        return;
    if (t->data <= x)
        del_in(x, y, t->right);
    else if (t->data >= y)
        del_in(x, y, t->left);
    else
    {
        del(t->data, t);
        del_in(x, y, t);
    }
}

template <class T>
bool bst<T>::find_ith(int i, T &x, node *t) const
{
    if (!t)
        return false;
    int ls = size(t->left);
    if (ls + 1 <= i && i <= ls + t->count)
    {
        x = t->data;
        return true;
    }
    if (ls + 1 > i)
        return find_ith(i, x, t->left);
    else
        return find_ith(i - ls - t->count, x, t->right);
}

template <class T>
int bst<T>::size(node *t) const
{
    return t ? (t->count + size(t->left) + size(t->right)) : 0;
}

template <class T>
void bst<T>::display(node *t)
{
    if (t)
    {
        cout << t->data << ' ';
        display(t->left);
        display(t->right);
    }
    else
        cout << "# ";
}

template <class T>
void bst<T>::clear(node *&t)
{
    if (!t)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

int main()
{
    bst<int> tree;
    int n, arg, arg1;
    char cmd[25];
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> cmd >> arg;
        if (!strcmp(cmd, "insert"))
            tree.ins(arg);
        else if (!strcmp(cmd, "delete"))
            tree.del(arg);
        else if (!strcmp(cmd, "delete_less_than"))
            tree.del_lt(arg);
        else if (!strcmp(cmd, "delete_greater_than"))
            tree.del_gt(arg);
        else if (!strcmp(cmd, "delete_interval"))
        {
            cin >> arg1;
            tree.del_in(arg, arg1);
        }
        else if (!strcmp(cmd, "find"))
        {
            if (tree.find(arg))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
        else if (!strcmp(cmd, "find_ith"))
        {
            int x = 0;
            if (tree.find_ith(arg, x))
                cout << x << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}
