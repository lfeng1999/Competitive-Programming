#include <bits/stdc++.h>

using namespace std;

int lef[20010], rig[20010], dpR[20010], dpL[20010];

int main()
{
//    freopen("CCO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> lef[i] >> rig[i];
    }
    dpL[1] = rig[1] - 1 + (rig[1] - lef[1]);
    dpR[1] = rig[1] - 1;
    for (int i=2; i<=N; ++i){
        dpL[i] = rig[i] - lef[i] + min(dpL[i-1] + abs(rig[i] - lef[i-1]), dpR[i-1] + abs(rig[i] - rig[i-1]));
        dpR[i] = rig[i] - lef[i] + min(dpL[i-1] + abs(lef[i] - lef[i-1]), dpR[i-1] + abs(lef[i] - rig[i-1]));
    }
    int ans = min(dpL[N] + N - lef[N], dpR[N] + N - rig[N]);
    cout << ans + N - 1;

    return 0;
}
