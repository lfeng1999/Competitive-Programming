#include <bits/stdc++.h>

using namespace std;

int R, C, H, W, grid[3010][3010], psum[3010][3010];

bool valid(int med){
    memset(psum, 0, sizeof(psum));

    for (int i=1; i<=R; ++i){
        for (int j=1; j<=C; ++j){
            if (grid[i][j] > med)
                psum[i][j] = 1;
            else if (grid[i][j] < med)
                psum[i][j] = -1;

            psum[i][j] += psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
        }
    }

    for (int i=H; i<=R; ++i){
        for (int j=W; j<=C; ++j){
            if (psum[i][j] - psum[i-H][j] - psum[i][j-W] + psum[i-H][j-W] <= 0)
                return true;
        }
    }
    return false;
}

int main()
{
//    freopen("IOI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> R >> C >> H >> W;

    for (int i=1; i<=R; ++i){
        for (int j=1; j<=C; ++j){
            cin >> grid[i][j];
        }
    }

    int LL = 0, RR = R*C;

    while (LL < RR){
        int mid = (LL+RR)/2;

        if (valid(mid))
            RR = mid;
        else
            LL = mid + 1;
    }
    printf("%d\n", LL);

    return 0;
}
