#include <bits/stdc++.h>

using namespace std;

typedef pair<int,float> pid;
float dp[101][200001];
pid coins[100001], sorted[100001], onhand[100001];
int C, D, K, tot;
float origweight;

float genweight(int w)
{
    float cnt = 0;
    for (int i=0; i!=D; ++i)
    {
        int x = w/sorted[i].first;
        w-=x*sorted[i].first;
        cnt+=sorted[i].second*x;
    }
    return cnt;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> C >> D >> K;
    for (int i=0; i!=D; ++i)
    {
        cin >> coins[i].first >> coins[i].second;
        sorted[i] = coins[i];
    }
    sort(sorted,sorted+D);
    reverse(sorted,sorted+D);
    for (int i=1; i<=K; ++i)
    {
        int a;
        cin >> a;
        tot+=coins[--a].first;
        origweight+=coins[a].second;
        onhand[i]=coins[a];
    }
    if (tot < C)
    {
        printf("too poor");
        return 0;
    }
    memset(dp,0,sizeof(dp));
    for (int i=1; i<=K; ++i)
    {
        int d = onhand[i].first; float w = onhand[i].second;
        for (int j=1; j<=200000; ++j)
        {
            if (j>=d && (dp[i-1][j-d] || j==d))
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-d]+w);
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    float minweight = 1000000;
    for (int i=C; i<=200000; ++i)
    {
        if (dp[K][i])
            minweight = min(minweight, origweight - dp[K][i] + genweight(i-C));
    }
    printf("%.2f",minweight);

}
