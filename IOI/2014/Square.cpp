#include <bits/stdc++.h>

using namespace std;

int grid[1010][1010], N, best = 0;

bool works(int len){
    bool flag = false;
    int cnt = 0;
    for (int i = len; i <= N; ++i){
        for (int j = len; j <= N; ++j){
            if (grid[i][j] - grid[i-len][j] - grid[i][j-len] + grid[i-len][j-len] == 0){
                flag = true;
                cnt++;
            }
        }
    }
    if (flag)
        best = cnt*len;
//    if (flag) cout << len << endl;
    return flag;
}

int main()
{
//    freopen("IOI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N;
    for (int i=1; i<=N; ++i){
        for (int j=1; j<=N; ++j){
            cin >> grid[i][j];
            grid[i][j] ^= 1;
            grid[i][j] += grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1];
        }
    }


    int L = 0, R = N;
    while (L < R){
        int mid = (L+R)/2 + 1;

        if (works(mid))
            L = mid;
        else
            R = mid - 1;

    }
    printf("%d\n", best);

    return 0;
}
