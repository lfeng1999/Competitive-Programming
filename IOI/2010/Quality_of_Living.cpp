#include <bits/stdc++.h>

using namespace std;

int R,C,H,W, qual[3010][3010], prefix[3010][3010];

bool valid(int med){
    for (int i=0; i!=R; ++i)
        for (int j=0; j!=C; ++j)
            prefix[i][j] = (qual[i][j] <= med?1:0)+(i?prefix[i-1][j] : 0) + (j?prefix[i][j-1] : 0) - (i&&j?prefix[i-1][j-1] : 0);
    for (int i=H-1; i<R; ++i)
        for (int j=W-1; j<C; ++j)
            if (prefix[i][j] - (i>=H ? prefix[i-H][j]:0) - (j>=W ? prefix[i][j-W]:0) + (i>=H && j>=W? prefix[i-H][j-W]:0) > (H*W)/2){
                return true;
            }
    return false;
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> R >> C >> H >> W;
    for (int i=0; i != R; ++i)
        for (int j=0; j!=C; ++j)
            cin >> qual[i][j];
    int LL = 1, RR = R*C + 1;
    while (LL + 1< RR)
        (valid((LL+RR)/2)?RR:LL) = (LL+RR)/2;
    cout << LL + 1;
}
