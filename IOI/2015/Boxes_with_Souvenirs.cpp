#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000100;
long long N,K,L, cTime[MAXN], ccTime[MAXN], cdist[MAXN], ccdist[MAXN];

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> K >> L;
    for (int i=1; i<=N; ++i){
        cin >> cdist[i];
        if (cdist[i] == 0) {i--;N--;continue;}
        ccdist[i] = L - cdist[i];
        cTime[i] = 2*cdist[i] + ((i >= K)?cTime[i-K]:0);
    }
    reverse(ccdist+1, ccdist+N+1);
    for (int i=1; i<=N; ++i) ccTime[i] = 2*ccdist[i] + ((i >= K)?ccTime[i-K]:0);
    long long optval = 1e15, maxn = 1e15;
    if (K >= N) optval = L;
    for (int i=0; i<=N; ++i){
        optval = min(optval,min(cTime[i]+ccTime[N-i],\
                                min(cTime[i] + L + ((N-i-K >= 0)?ccTime[N-i-K]: maxn),\
                                    ccTime[i] + L + ((N-i-K >= 0)?cTime[N-i-K]: maxn))));
    }
    cout << optval;
    return 0;
}
