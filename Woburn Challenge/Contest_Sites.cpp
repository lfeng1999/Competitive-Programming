#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> rgraph[100010];
int N, M, K, peep[100010], v, u, d;
bool past[100010], ispos[100010], ispos2[100010];
long long sdist[100010], sdist2[100010];
pair<long long, pair<long long, int>> fast[100010];


void dijkstra(){
    for (int i=0; i<100010; ++i) sdist[i] = sdist2[i] = 1e18;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    Q.push(make_pair(0,1));//dist, v
    while (!Q.empty()){
        v = Q.top().second; d = Q.top().first; Q.pop();
        ispos[v] = true;
        if (past[v]) continue;
        past[v] = true; sdist[v] = d;
        for (int i=0; i<rgraph[v].size(); ++i){
            u = rgraph[v][i].first;int d2 = rgraph[v][i].second;
            if (!past[u]){
                Q.push(make_pair(d+d2,u));
            }
        }
    }
    memset(past,false,sizeof(past));
    Q.push(make_pair(0,2));
    while (!Q.empty()){
        v = Q.top().second; d = Q.top().first; Q.pop();
        ispos2[v] = true;
        if (past[v]) continue;
        past[v] = true; sdist2[v] = d;
        for (int i=0; i<rgraph[v].size(); ++i){
            u = rgraph[v][i].first;int d2 = rgraph[v][i].second;
            if (!past[u]){
                Q.push(make_pair(d+d2,u));
            }
        }
    }

}

int main()
{
    //freopen("WoburnChallenge.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    for (int i=1; i<=N; ++i){
        cin >> peep[i];
    }
    for (int i=0; i<M; ++i){ cin >> v >> u >> d; rgraph[u].push_back(make_pair(v,d));}
    dijkstra();
    for (int i=1; i<=N; ++i){
        fast[i-1] = make_pair(sdist[i]-sdist2[i],make_pair(sdist2[i], peep[i]));
    }
    sort(fast, fast+N); reverse(fast, fast+N);
    long long ans = 0, pcount = K;
    for (int i=0; i<N; ++i){
        long long d1 = fast[i].first, d2 = fast[i].second.first, nump = fast[i].second.second;
        if (fast[i].first < 0 || pcount == 0){
            ans += (d1+d2)*nump;
            continue;
        }
        if (pcount < nump){
            ans+=d2*pcount;
            nump-=pcount; pcount = 0;
            ans+=(d1+d2)*nump;
            continue;
        }
        ans+= d2*nump;
        pcount-=nump;
    }
    for (int i = 1; i<=N; ++i) if (!ispos[i] && !ispos2[i] && peep[i]!=0) {cout << -1; return 0;}
    if (ans < 1e18 && ans > 0)
        cout << ans;
    else cout << -1;
    return 0;
}
