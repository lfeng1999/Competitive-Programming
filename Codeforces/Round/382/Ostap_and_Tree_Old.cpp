#include <bits/stdc++.h>

using namespace std;

const int mod = int(1e9) + 7;
const int MX = 105;
const int MK = 25;
long long dp[MX][2 * MK];
long long tmp[2 * MK];
int n, k;
vector<int> e[MX];

//dp[a][b] <= Current node is a. Next black node is of depth b from the node

void go(int u, int pr){ //Node, parent

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    dp[u][0] = dp[u][k + 1] = 1;// WTF DOES THE SECOND PART MEAN
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Each node is visited at most once. 

    for(int i = 0; i < e[u].size(); i++){
        int v = e[u][i];
        if(v == pr) continue;



        go(v, u); //Solve smaller subtree (next node, cur node)
        
        for(int j = 0; j <= 2 * k; j++)
            tmp[j] = 0;
        //RESET THE SOLVING        


        for(int u_len = 0; u_len <= 2 * k; u_len++){ // Length from current node to next black node? 
            for(int v_len = 0; v_len <= 2 * k; v_len++){ //Length from next node to next black node?
                int curr = min(u_len, v_len + 1);

                if(u_len + v_len > 2 * k) 
                    curr = max(u_len, v_len + 1);
                
                tmp[curr] = (tmp[curr] + dp[u][u_len] * dp[v][v_len]) % mod;
            }
        }
        for(int j = 0; j < 2 * k + 1; j++)
            dp[u][j] = tmp[j];
    }
    //cerr << u << ' ' << dp[u][0] << "\n";
}

int main()
{
    freopen("CF.txt","r", stdin);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);// Setup graph
        e[v].push_back(u);
    }
    go(0, 0); //Solve v, parent
    long long ans = 0;
    for(int i = 0; i <= k; i++) //Solving... vertex, # of black nodes
        ans += dp[0][i];
    cout << ans % mod << endl;
    return 0;
}