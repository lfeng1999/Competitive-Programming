#include <bits/stdc++.h>

using namespace std;

int val[210], dp[210][210], psum[210];

int get_sum(int i, int j){return psum[j] - psum[i-1];}

int solve(int i, int j){
    if (dp[i][j] != -1) return dp[i][j];
    int &ans = dp[i][j];
    if (i > j) return ans = 0;

    int tot = psum[j] - psum[i-1];

    return ans = tot - min(solve(i, j-1), solve(i+1, j));
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(dp, -1, sizeof(dp));
    int N;
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> val[i];
        psum[i] = psum[i-1] + val[i];
    }

    int p1 = solve(1, N);
    printf("%d %d\n", p1, psum[N] - p1);

    return 0;
}
