#include <bits/stdc++.h>

using namespace std;

int N, A[110];
double B[110];

int main()
{
//    freopen("COCI.txt","r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> B[i];
        A[i] = B[i]*i - B[i-1]*(i-1);
        cout << A[i] << " ";
    }
    return 0;
}