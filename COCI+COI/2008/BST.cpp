#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    long long cnt = 0;
    cin >> N;
    map<int,int> depth;
    for (int i=0; i!=N; ++i)
    {
        int a, d = 0;
        cin >> a;
        map<int,int>::const_iterator iter = depth.lower_bound(a);
        if (iter != depth.end())
            d = max(d, iter->second + 1);
        if (iter != depth.begin())
            d = max(d, (--iter)->second + 1);
        cnt+=d;
        //cout << a << " " << d << endl;
        depth[a] = d;
        printf("%lld\n",cnt);
    }
}
