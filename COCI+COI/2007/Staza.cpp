#include <bits/stdc++.h>

using namespace std;

int N, M, occur[10010], low_link[10010];
vector<int> bridge[10010];
vector<int> hanging_ring[10010]; //hanging from v
vector<int> ring[10010];

vector<int> graph[10010];

stack<int> stk;
int occur_cnt = 1, ring_cnt = 0;

void dfs(int v, int p){
    occur[v] = low_link[v] = occur_cnt;
    occur_cnt++;

    stk.push(v);

    for (int u : graph[v]){
        if (u == p) continue;

        if (occur[u] != 0){
            low_link[v] = min(low_link[v], occur[u]);
        }
        else{

            dfs(u, v);

            if (low_link[u] < occur[v]){
                low_link[v] = min(low_link[v], low_link[u]);
            }
            else if (low_link[u] == occur[v]){
                hanging_ring[v].push_back(ring_cnt);
                do{
                    ring[ring_cnt].push_back(stk.top());
                    stk.pop();
                }while (ring[ring_cnt].back() != u);
                ring_cnt++;
            }
            else{
                bridge[v].push_back(stk.top());
                stk.pop();
            }
        }
    }
}

const int PATH = 0, RING = 1;
int dp[10010][2];

int solve(int v, int type){
//    cout << v << " " << type << endl;
    if (dp[v][type] != -1) return dp[v][type];

    int &ans = dp[v][type];
    ans = 0;

    int path_profit = 0;

    for (int u : bridge[v])
        path_profit = max(path_profit, 1 + solve(u, PATH));



    for (int r : hanging_ring[v]){
        ans += ring[r].size() + 1; //full round

        int clock_ring = 0, cclock_ring = 0, clock_path = 0, cclock_path = 0;
        for (int i=0; i<ring[r].size(); ++i){
            int clock_u = ring[r][i], cclock_u = ring[r][ring[r].size()-i-1];

            clock_path = max(clock_path, clock_ring + i + 1 + solve(clock_u, PATH));
            cclock_path = max(cclock_path, cclock_ring + i + 1 + solve(cclock_u, PATH));

            clock_ring += solve(clock_u, RING);
            cclock_ring += solve(cclock_u, RING);
        }
        ans += clock_ring;
        int cyc_length = ring[r].size() + 1;
        path_profit = max(path_profit, max(clock_path, cclock_path) - clock_ring - cyc_length);

    }

    dp[v][RING] = ans;
    dp[v][PATH] = ans + path_profit;

//    cout << v << " " << type << " " << dp[v][RING] << " " << dp[v][PATH] << endl;

    if (type == PATH)
        return dp[v][PATH];

    return dp[v][RING];
}


int main()
{
//    freopen("CCO.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(dp, -1, sizeof(dp));
    cin >> N >> M;

    for (int i=0; i<M; ++i){
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    dfs(1, -1);

    cout << solve(1, PATH);


    return 0;
}
