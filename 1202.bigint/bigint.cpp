#include <iostream>
#include <cstring>
using namespace std;

struct node
{
    int data;
    node *next;
};

void output(node *p)
{
    p = p->next;
    if (p)
    {
        output(p);
        cout << p->data;
    }
}

int main()
{
    node *headA = new node;
    node *headB = new node;
    node *headC = new node;
    node *p, *q, *r;
    char c;

    q = NULL;
    while ((c = cin.get()) != '\n')
    {
        p = new node;
        p->data = c - '0';
        p->next = q;
        q=p;
    }
    headA->next = q;

    q = NULL;
    while ((c = cin.get()) != '\n')
    {
        p = new node;
        p->data = c - '0';
        p->next = q;
        q=p;
    }
    headB->next = q;

    p = headA->next;
    q = headB->next;
    r = headC;
    int carry = 0;

    while (p || q || carry)
    {
        r->next = new node;
        r = r->next;
        if (p)
        {
            carry += p->data;
            p = p->next;
        }
        if (q)
        {
            carry += q->data;
            q = q->next;
        }
        r->data = carry % 10;
        carry /= 10;
    }
    r->next = NULL;

    output(headC);

    return 0;
}