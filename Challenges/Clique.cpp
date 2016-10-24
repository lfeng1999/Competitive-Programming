#include <bits/stdc++.h>

using namespace std;

int N,M, best;
bool adj[32][32], tempc[32];


void bash(int n, int maxc)
{
    if (n == N)
    {
        best = max(best,maxc);
        return;
    }
    if (maxc + N - n <= best)
        return;
    bash(n+1,maxc);
    for (int i=0; i!=n; ++i)
        if (tempc[i])
            if (!adj[i][n])
                return;
    tempc[n]=true;
    bash(n+1,maxc+1);
    tempc[n]=false;
}

int main()
{
    cin.sync_with_stdio(false); cin.tie(0);
    cin >> N >> M;
    for (int i=0; i!=M; ++i)
    {
        int a,b;
        cin >> a >> b;
        adj[--a][--b] = adj[b][a] = true;
    }
    bash(0,0);
    cout << best << endl;
}
