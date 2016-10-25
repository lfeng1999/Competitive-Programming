#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
map<long long, long long> compX, compY, decompX, decompY;
long long X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN], T[MAXN];
long long dsum[MAXN*2][MAXN*2];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int N, mT;
    cin >> N >> mT;
    set<int> Sx, Sy;
    for (int i=0; i<N; ++i){
        cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i] >> T[i];
        Sx.insert(X1[i]); Sx.insert(X2[i]);
        Sy.insert(Y1[i]); Sy.insert(Y2[i]);
    }
    int cntx = 1, cnty = 1;
    for (int x : Sx) {decompX[cntx] = x; compX[x] = cntx++;}
    for (int y : Sy) {decompY[cnty] = y; compY[y] = cnty++;}
    for (int i=0; i<N; ++i){
        for (int j=compY[Y1[i]]; j<compY[Y2[i]]; ++j){
            dsum[j][compX[X1[i]]]+=T[i]; dsum[j][compX[X2[i]]]-=T[i];
        }
    }
    for (int i=1; i<cnty; ++i){
        for (int j=1; j<cntx; ++j){
            dsum[i][j]+=dsum[i][j-1];
        }
    }
    long long tot = 0;
    for (int i=1; i<cnty; ++i){
        for (int j=1; j<cntx; ++j){
            if (dsum[i][j] >= mT){
                tot+=(decompY[i+1]-decompY[i])*(decompX[j+1]-decompX[j]);
            }
        }
    }
    printf("%lld",tot);
    return 0;
}
