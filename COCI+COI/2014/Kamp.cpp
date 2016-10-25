#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 500010;
int N, K;
ll total_time = 0, maxbranch1[MAXN], maxbranch2[MAXN], furthest[MAXN], tographdist[MAXN];
//                  only for inPath                     only for inPath
int branch1[MAXN], branch2[MAXN], closestpoint[MAXN];
vector<pair<int,int>> graph[MAXN];
bool dest[MAXN], inPath[MAXN];

bool graphlength(int v, int p){
    bool flag = false;
    for (pair<int,int> E : graph[v]){
        int u = E.first, c = E.second;
        if (u!=p){
            if (graphlength(u, v)){
                total_time+=c;
                flag = true;
            }
        }
    }
    if (dest[v]){
        flag = true;
    }
    if (flag){
        inPath[v] = true;
    }
    return flag;
}

ll gen_maxbranch(int v, int p, ll curdist){
    for (int i=0; i<graph[v].size(); ++i){
        int u = graph[v][i].first, c = graph[v][i].second;
        if (u!=p && inPath[u]){
            ll dist = c + gen_maxbranch(u, v, curdist + c);
            if (dist > maxbranch1[v]){
                maxbranch2[v] = maxbranch1[v];
                branch2[v] = branch1[v];
                maxbranch1[v] = dist;
                branch1[v] = i;
            }
            else if (dist > maxbranch2[v]){
                maxbranch2[v] = dist;
                branch2[v] = i;
            }
        }
    }
    return maxbranch1[v];
}

void gen_furthest(int v, int p, ll curdist){
    furthest[v] = max(curdist, maxbranch1[v]);
    for (int i=0; i<graph[v].size(); ++i){
        int u = graph[v][i].first, c = graph[v][i].second;
        if (u!=p && inPath[v]){

            if (i != branch1[v]){
                gen_furthest(u, v, furthest[v] + c);
            }
            else{
                gen_furthest(u, v, max(maxbranch2[v], curdist) + c);
            }
        }
    }
}

void gen_closesttograph(int v, int p, ll curdist, int nearest){
    closestpoint[v] = nearest;
    tographdist[v] = curdist;
    for (int i=0; i<graph[v].size(); ++i){
        int u = graph[v][i].first, c = graph[v][i].second;
        if (u == p) continue;
        if (inPath[u]){
            gen_closesttograph(u, v, 0, u);
        }
        else{
            gen_closesttograph(u, v, curdist + c, nearest);
        }
    }
}

int main()
{
//    freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i=0; i<N-1; ++i){
        int v, u, c;
        cin >> v >> u >> c;
        graph[v].push_back(make_pair(u, c));
        graph[u].push_back(make_pair(v, c));
    }
    int v;
    for (int i=0; i<K; ++i){
        cin >> v;
        dest[v] = true;
    }
    graphlength(v, -1);
    gen_maxbranch(v, -1, 0);
    gen_furthest(v, -1, 0);
    gen_closesttograph(v, -1, 0, v);
    for (int i=1; i<=N; ++i){
        printf("%lld\n", total_time*2 + tographdist[i] - furthest[closestpoint[i]]);
//        cout << total_time*2 + tographdist[i] - furthest[closestpoint[i]] << endl;
    }
    return 0;
}