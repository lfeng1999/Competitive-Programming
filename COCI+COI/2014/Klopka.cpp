#include <bits/stdc++.h>

using namespace std;

int N, minx = 1e9, maxx = -1e9, miny = 1e9, maxy = -1e9;

int main()
{
//    freopen("COCI.txt","r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        int x, y;
        cin >> x >>  y;
        minx = min(minx, x);
        maxx = max(maxx, x);
        miny = min(miny, y);
        maxy = max(maxy, y);
    }
    int s = max(maxx-minx, maxy-miny);
    cout << s*s;
    return 0;
}