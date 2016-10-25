#include <bits/stdc++.h>

using namespace std;

int bit[100010], N, pos[100010];

void update(int i, int val){
    for (; i < N + 5; i += i&(-i))
        bit[i] += val;
}

int query(int i){
    int tot = 0;
    for (; i > 0; i -= i&(-i))
        tot += bit[i];
    return tot;
}

int main()
{
//    freopen("COCI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N;

    for (int i=1; i<=N; ++i){
        int v; cin >> v;
        pos[v] = i;
    }
    int lo = 1, hi = N;

    for (int i = 1; i <= N; ++i){
        int ans = 0;
        if (i&1){ //odd, lo

            printf("%d\n", pos[lo] - query(pos[lo]) - 1);
            update(pos[lo], 1);
            lo++;
        }
        else{
            printf("%d\n", N - pos[hi] - (query(N) - query(pos[hi])));
            update(pos[hi], 1);
            hi--;
        }
    }

    return 0;
}
