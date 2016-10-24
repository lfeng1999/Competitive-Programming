#include <bits/stdc++.h>

using namespace std;

int N, R[20001], C[20001], dpr[2][2010], dpc[2][2010];
//                  ignore  r value,      c value
//                       c pos known.   r pos known
int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    R[0] = 1000;
    C[0] = 1000;
    for (int i=1; i<=N; ++i)
    {
        cin >> R[i] >> C[i];
        R[i]+=1000;
        C[i]+=1000;
    }
    int a = 0, b = 1;
    for (int i = N-1; i>=0; --i)
    {
        swap(a,b);
        for (int r = 0; r<= 2000; ++r)
            dpc[a][r] = min(dpc[b][r] + abs(C[i+1]-C[i]), dpr[b][C[i]] + abs(R[i+1]-r));
        for (int c = 0; c<= 2000; ++c)
            dpr[a][c] = min(dpr[b][c] + abs(R[i+1]-R[i]), dpc[b][R[i]] + abs(C[i+1]-c));
    }
    printf("%d",dpr[a][1000]);
}
