#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
int vis[100000];
vector<pii> graph[100000];

int main()
{
    //freopen("CUC.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    int N,M,K;
    cin >> N >> M >> K;
    for (int i=0; i!=M; ++i){
        int a,b,c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(c,b));
        graph[b].push_back(make_pair(c,a));
    }
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for (int i=0; i!=K; ++i){
        int a;
        cin >> a;
        Q.push(make_pair(0,a));
        vis[a] = 1;
    }
    while (!Q.empty()){
        int c = Q.top().second, d = Q.top().first; Q.pop();
        if (vis[c] == 0){
            vis[c]++;
            continue;
        }
        else if (vis[c] == 2){
            continue;
        }
        if (c == 0){
            cout << d;
            return 0;
        }
        vis[c]++;
        for (int i=0; i!=graph[c].size(); ++i){
            if (vis[graph[c][i].second]!=2){
                Q.push(make_pair(graph[c][i].first + d,graph[c][i].second));
            }
        }
    }
    return 0;
}
