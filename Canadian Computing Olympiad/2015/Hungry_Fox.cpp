#include <bits/stdc++.h>

using namespace std;

long long N,W,cracker[100001], reorder[100001];

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin >> N >> W;
    for (int i=1; i<=N; ++i)
    {
        cin >> cracker[i];
    }
    long long maxv = 0;
    sort(cracker,cracker+N+1);
    reorder[0] = W;
    for (int i=1; i<=N; ++i)
    {
        if (i%2==1)
            reorder[i] = cracker[(i+1)/2];
        else
            reorder[i] = cracker[N+1-i/2];
    }
    for (int i=1; i<=N; ++i)
    {
        maxv += max(abs(reorder[i]-reorder[i-1]),abs(reorder[i]-W));
    }
    long long maxv2 = 0;
    for (int i=1; i<=N; ++i)
    {
        if (i%2==1)
            reorder[i] = cracker[N+1-(i+1)/2];
        else
            reorder[i] = cracker[i/2];
    }
    for (int i=1; i<=N; ++i)
    {

        maxv2 += max(abs(reorder[i]-reorder[i-1]),abs(reorder[i]-W));
    }
    int v;
    for ( v = 1; v<=N; ++v)
    if (cracker[v] >= W) break;
    reverse(cracker+1,cracker+v);
    long long minv = 0;
    for (int i=1; i<=N; ++i)
    {
        minv += min(abs(cracker[i]-cracker[i-1]), abs(cracker[i]-W));
    }

    cout << minv << " " << max(maxv,maxv2);
}