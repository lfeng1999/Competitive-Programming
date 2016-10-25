#include <bits/stdc++.h>

using namespace std;
const int MAXN = 10001;
string s;
int len,dp[2][MAXN],M;

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> s;
    cin >> M;
    len = s.length();
    for (int i = 0;i<=len;i++) {
        dp[0][i] = 1;
    }
    dp[1][0] = 1;
    int a = 0, b = 1;
    for (int i = 1;i<=len;i++)
    {
        swap(a,b);
        for (int j = 1;j<=len;j++) {
            if (s[i-1]==s[j-1])
                dp[a][j] = (dp[b][j] + dp[a][j-1])%M;
            else
                dp[a][j] = ((dp[b][j] + dp[a][j-1])%M - dp[b][j-1]+M)%M;
        }
    }
    printf("%d\n",dp[a][len]);
}
