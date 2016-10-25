#include <bits/stdc++.h>

using namespace std;

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int H, M;
    cin >> H >> M;
    int tot = H*60 + M;
    int ext; cin >> ext;
    tot+=ext;
    tot%=1440;
    H = tot/60;
    M = tot-H*60;
    cout << H << " " << M;

    return 0;
}