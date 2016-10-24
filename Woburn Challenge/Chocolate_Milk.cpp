#include <bits/stdc++.h>

using namespace std;

struct Tree{
    vector<pair<int,int>> edge;
    int dp[210], cmilk, par = 0;
}tree[210];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N, K, P, C, F;
    cin >> N >> K;
    for (int i=2; i<=N; ++i){
        cin >> P >> C >> F;
        tree[i].dp[0] = tree[i].cmilk = P;tree[i].par = C; tree[C].edge.push_back(make_pair(i,F));
        for (int j = 1; j<210; ++j) tree[i].dp[j] = tree[i].dp[0];
    }
    for (int v=N; v>=1; --v){
        if (tree[v].edge.size() == 0) continue;
        for (int i=0; i<tree[v].edge.size(); ++i){
            int u = tree[v].edge[i].first, d = tree[v].edge[i].second;
            for (int k=K; k>= 0; k--){
                int olddp[210];
                for (int l = 0; l<210; ++l) olddp[l] = tree[v].dp[l];
                for (int l=k; l>= 0; l--){
                    if (k == 0){
                        tree[v].dp[k] += min(tree[u].dp[l], d);
                        continue;
                    }
                    tree[v].dp[k] = max(tree[v].dp[k],olddp[k-l] + min(tree[u].dp[l],d));
                    if (k == l) continue;
                    tree[v].dp[k] = max(tree[v].dp[k],olddp[k-l-1] + tree[u].dp[l]);
                }
            }
        }
    }
    cout << tree[1].dp[K];
    return 0;
}
