#include <iostream>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    if (n == 1)
    {
        cout << "true";
        return 0;
    }
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
        arr[i] = 0;
    pair<int, int> rest[10000];
    int size = 0;
    for (int i = 0; i < k; i++)
    {
        int a, b;
        cin >> a >> b;
        if (arr[a] == 0 || arr[b] == 0)
        {
            if (arr[a] != 0)
                arr[b] = -arr[a];
            else if (arr[b] != 0)
                arr[a] = -arr[b];
            else
            {
                if (i == 0)
                {
                    arr[a] = 1;
                    arr[b] = -1;
                }
                else
                {
                    pair<int, int> p;
                    p.first = a;
                    p.second = b;
                    rest[size++] = p;
                }
            }
        }
        else if (arr[a] == arr[b])
        {
            cout << "false";
            return 0;
        }
    }
    
    while (size != 0)
    {
        int newsize = 0;
        pair<int, int> newrest[size];
        for (int i = 0; i < size; i++)
        {
            int a, b;
            a = rest[i].first;
            b = rest[i].second;
            if (arr[a] == 0 || arr[b] == 0)
            {
                if (arr[a] != 0)
                    arr[b] = -arr[a];
                else if (arr[b] != 0)
                    arr[a] = -arr[b];
                else
                {
                    if (i == 0)
                    {
                        arr[a] = 1;
                        arr[b] = -1;
                    }
                    else
                    {
                        pair<int, int> p;
                        p.first = a;
                        p.second = b;
                        newrest[newsize++] = p;
                    }
                }
            }
            else if (arr[a] == arr[b])
            {
                cout << "false";
                return 0;
            }
        }
        size = newsize;
        for (int i = 0; i < size; i++)
        {
            rest[i] = newrest[i];
        }
    }
    cout << "true";
    return 0;
}