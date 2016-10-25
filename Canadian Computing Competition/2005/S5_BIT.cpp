#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
int plays[100010], bit[100010];
unordered_map<int,int> compress;

int query(int i){
    int tot = 0;
    for (; i > 0; i-=i&(-i))
        tot += bit[i];
    return tot;
}
void update(int i, int v){
    for (; i < MAXN; i += i&(-i))
        bit[i] += v;
}

int main()
{
//    freopen("CCC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    vector<int> Ps;
    for (int i=0; i<N; ++i){
        cin >> plays[i];
        Ps.push_back(plays[i]);
    }
    sort(Ps.begin(), Ps.end());
    reverse(Ps.begin(), Ps.end());
    for (int i=0; i<N; ++i){
        compress[Ps[i]] = i+1;
    }
    double ans = 0;
    for (int i=0; i<N; ++i){
        ans += query(compress[plays[i]] - 1) + 1;
        update(compress[plays[i]], 1);
    }
    printf("%.2f\n", ans/N);

    return 0;
}
