#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int be = 0, ok = 1;
    char ite = '0';
    char buf[80];
    while (cin >> buf && ok)
    {
        if (!strcmp(buf, "begin"))
            ++be;
        else if (!strcmp(buf, "end"))
            if (be > 0)
                --be;
            else
                ok = 0;
        else if (!strcmp(buf, "if"))
            ite = 'i';
        else if (!strcmp(buf, "then"))
            if (ite == 'i')
                ite = 't';
            else
                ok = 0;
        else if (!strcmp(buf, "else"))
            if (ite == 't')
                ite = 'e';
            else
                ok = 0;
    }
    if (ok && be == 0 && ite != 'i')
        cout << "Match!";
    else
        cout << "Error!";

    return 0;
}