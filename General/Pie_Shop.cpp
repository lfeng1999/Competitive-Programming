#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;
typedef bitset<16> Mask;
vector<int> pos, bitpos[16];
long long R,C, pies[16][16], dp[16][1 << 16][2];
//                      row, bitmask, (value,#ofways)

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> R >> C;
    for (int i=0; i!=R; ++i)
        for (int j=0; j!=C; ++j)
            cin >> pies[i][j];
    for (int i=0; i!=(1<<C); ++i)
    {
        Mask x = i;
        bool flag = true;
        for (int j=0; j!=16; ++j)
        if (j && x[j] && x[j-1])
            flag = false;
        if (!flag)
            continue;
        pos.push_back(i);
        for (int j=0; j!=16; ++j)
            if (!x[j])
                bitpos[j].push_back(i);
    }
    for (int qq = 0; qq!=R; ++qq)
    {
        for (int i: pos)
        {
            int tot = 0;
            Mask x = i;
            for (int j=0; j!=C; ++j)
                if (x[j])
                    tot+=pies[qq][j];
            if (qq == 0)
            {
                dp[qq][i][0] = tot;
                dp[qq][i][1] = 1;
                continue;
            }
            for (int j = 0; j!=16; ++j)
            {
                if (x[j])
                {
                    for (int k: bitpos[j])
                    {
                        if (k&i)
                            continue;
                        if (dp[qq-1][k][0] > dp[qq][i][0])
                        {
                            dp[qq][i][0] = dp[qq-1][k][0];
                            dp[qq][i][1] = 0;
                        }
                        if (dp[qq-1][k][0] == dp[qq][i][0])
                        {
                            dp[qq][i][1] = (dp[qq][i][1]+dp[qq-1][k][1])%MOD;
                        }
                    }
                    dp[qq][i][0] = (dp[qq][i][0]+tot)%MOD;
                    break;
                }
            }
        }
    }
    int maxn = 0, mcnt = 0;
    for (int i: pos)
    {
        if (dp[R-1][i][0] > maxn)
        {
            maxn = dp[R-1][i][0];
            mcnt = 0;
        }
        if (dp[R-1][i][0] == maxn)
        {
            mcnt = (mcnt+dp[R-1][i][1])%MOD;
        }
    }
    cout << maxn << " " << mcnt << endl;

}
