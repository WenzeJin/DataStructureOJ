#include <iostream>
using namespace std;
const int Max = 1e6 + 1;

int *KMP(string a, string b)
{
    int *Next = new int[Max];
    int *ans = new int[Max]{};
    int pos = 0;
    int la = a.length(), lb = b.length();
    for (int i = 1; i < lb; i++)
    {
        int j = Next[i - 1];
        while (j && b[i] != b[j])
        {
            j = Next[j - 1];
        }
            if(b[i]==b[j]){
                j++;
            }
            Next[i] = j;
    }
        for(int i=0,j=0;i<la;i++){
            while(j&&b[j]!=a[i]){
                j = Next[j - 1];
            }
        if(a[i]==b[j]){
            j++;
        }
        // cout<<j<<endl;
        if(j==lb){
            ans[pos] =  i - lb + 2;
            pos++;
            j = Next[j - 1];
        }
    }
    ans[pos] = -1;
    return ans;
}

int main()
{
    int n;
    cin >> n;
    string a, b;
    int p1 = 0, p2 = 0;
    cin >> a;
    
    cout << endl;
}