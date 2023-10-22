#include <iostream>
using namespace std;
const int cnt = 1000;
int main()
{
    //A n*t
    //B t*m
    //C n*m
    int n, t, m;
    cin >> n >> t >> m;
    int A[cnt][cnt]{}, B[cnt][cnt]{}, C[cnt][cnt]{};
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < t; ++j)
        {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> B[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int l = 0; l < t; ++l) {
            if(A[i][l] != 0){
                for (int j = 0; j < m; ++j) {
                    C[i][j] += A[i][l] * B[l][j];
                }
            }
        }
    }
    for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cout << C[i][j] << ' ';
            }
            cout << endl;
        }
}