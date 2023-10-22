#include <iostream>
#include <map>
using namespace std;
const int N = 1e6 + 6;
char s[N], p1[N], p2[N];
int ne1[N], ne2[N];
int m1 = 0, m2 = 0;
int main()
{
    int T;
    cin >> T;
    string p;
    cin >> p;
    bool flag = false;
    for (unsigned i = 0; i < p.length(); i++)
    {
        if (p[i] == '*')
        {
            flag = true;
        }
        else
        {
            if (!flag)
                p1[++m1] = p[i];
            else
                p2[++m2] = p[i];
        }
    }
    int k = m1 + 1;
    for (int i = 2, j = 0; i <= m1; i++)
    {
        while (j && p[i] != p[j + 1])
            j = ne1[j];
        if (p[i] == p[j + 1])
            j++;
        ne1[i] = j;
    }
    for (int i = 2, j = 0; i <= m1; i++)
    {
        while (j && p[i] != p[j + 1])
            j = ne2[j];
        if (p[i] == p[j + 1])
            j++;
        ne2[i] = j;
    }
    while (T--)
    {
        string s;
        cin >> s;
        int n = s.length();
        s = " " + s;
        map<int, bool> m;
        bool tt = false;

        for (int i = 1, j = 0; i <= n; i++)
        {
            while (j && s[i] != p2[j + 1])
                j = ne2[j];
            if (s[i] == p2[j + 1])
                j++;
            if (j == m2)
            {
                j = ne2[j];
                m[i - m2] = true;
            }
        }
        
        for (int i = 1, j = 0; i <= n; i++)
        {
            while (j && s[i] != p1[j + 1])
                j = ne1[j];
            if (s[i] == p1[j + 1])
                j++;
            if (j == m1)
            {
                j = ne1[j];
                if (m[i - m1 + k])
                {
                    tt = true;
                    break;
                }
            }
        }
        cout << (tt ? "true" : "false") << endl;
    }
    return 0;
}