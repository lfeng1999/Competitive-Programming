#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;

bool past[50010][2], complete[50010];
int N, M;
vector<int> graph[50010];

int main()
{
    //freopen("Woburn.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i=0; i<M; ++i){
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    double ans = 0;
    for (int i=1; i<=N; ++i){
        if (complete[i]) continue;
        vector<int> p0, p1;
        queue<pair<int,int>> Q;
        Q.push(make_pair(i, 0));
        past[i][0] = true;
        while (!Q.empty()){
            int v = Q.front().first, parity = Q.front().second;Q.pop();
            if (parity == 0){
                p0.push_back(v);
            }
            else{
                p1.push_back(v);
            }
            for (int u : graph[v]){
                if (!past[u][1-parity]){
                    Q.push(make_pair(u, 1-parity));
                    past[u][1-parity] = true;
                }
            }
        }
        if (past[i][0] == past[i][1]){
            ans+=p0.size()*p0.size();
        }
        else{
            ans+= p0.size()*p0.size() + p1.size()*p1.size();
        }
        for (int v : p0){
            complete[v] = true;
        }
        for (int v : p1){
            complete[v] = true;
        }
    }
    printf("%.7f", ans/N/N);


    return 0;
}
