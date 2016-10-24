#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int grid[2010][2010], psum[2010][2010], zone[2010][2010], bestzone[2010][2010], dp1[2010][2010], rowpsum[2010][2010], colpsum[2010][2010];
int rtzone[2010][2010], bestrtzone[2010][2010], lbzone[2010][2010], bestlbzone[2010][2010];

int main()
{
    //freopen("WC.txt","r",stdin);
    cin.sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for (int i=1; i<=N; ++i){
        for (int j=1; j<=M; ++j){
            cin >> grid[i][j];
            psum[i][j] = grid[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
            rowpsum[i][j] = rowpsum[i][j-1] + grid[i][j];
            colpsum[i][j] = colpsum[i-1][j] + grid[i][j];
            zone[i][j] = psum[i][j] - psum[i-1][j-1];
            bestzone[i][j] = max(bestzone[i-1][j], max(bestzone[i][j-1], zone[i][j]));
            dp1[i][j] = max(zone[i][j] + bestzone[i-1][j-1], max(dp1[i-1][j], dp1[i][j-1]));
        }
    }
    for (int i=1; i<=N; ++i){
        for (int j=M; j>=1; --j){
            rtzone[i][j] = max(colpsum[i][j], rtzone[i][j+1] + grid[i][j]);
            bestrtzone[i][j] = max(rtzone[i][j], max(bestrtzone[i-1][j], bestrtzone[i][j+1]));
        }
    }
    for (int i=N; i>=1; --i){
        for (int j=1; j<=M; ++j){
            lbzone[i][j] = max(rowpsum[i][j], lbzone[i+1][j] + grid[i][j]);
            bestlbzone[i][j] = max(lbzone[i][j],max(bestlbzone[i+1][j], bestlbzone[i][j-1]));
        }
    }
    int finans = 0;
    for (int i=1; i<=N; ++i){
        for (int j=1; j<=M; ++j){
            finans = max(finans, zone[i][j] + max(bestrtzone[N][j+1], bestlbzone[i+1][M]));
        }
    }
    cout << max(finans, dp1[N][M]);

    return 0;
}
