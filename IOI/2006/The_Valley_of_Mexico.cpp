#include <bits/stdc++.h>

using namespace std;

int C, n;
bool path[1001][1001], lmove[1001][1001], rmove[1001][1001], rpast[1001][1001], lpast[1001][1001];
int dp[1001][1001];

int rmp(int x){//clock
    return (x+1)%C;
}
int lmp(int x){//counter
    return (x-1+C)%C;
}
bool lefmove(int a, int b);
bool rigmove(int a, int b){
    if (rmp(a) == b) return rmove[a][b] = true;
    if (rpast[a][b]) return rmove[a][b];
    int rp = rmp(a), lp = lmp(b);
    rpast[a][b] = true;
    rmove[a][b] = (path[a][rp] && rigmove(rp, b));
    if (rmove[a][b]) return true;
    return rmove[a][b] = (path[a][lp] && lefmove(lp, a));
}
bool lefmove(int a, int b){
    if (lmp(a) == b) return lmove[a][b] = true;
    if (lpast[a][b]) return lmove[a][b];
    int rp = rmp(b), lp = lmp(a);
    lpast[a][b] = true;
    lmove[a][b] = (path[a][lp] && lefmove(lp, b));
    if (lmove[a][b]) return true;
    return lmove[a][b] = (path[a][rp] && rigmove(rp, a));
}
void printlef(int a,int b);
void printrig(int a, int b){
    printf("%d\n", a+1);
    if (rmp(a) == b) return;
    int rp = rmp(a), lp = lmp(b);
    if (rmove[rp][b]) printrig(rp,b);
    else printlef(lp, a);
}
void printlef(int a,int b){
    printf("%d\n", a+1);
    if (lmp(a) == b) return;
    int rp = rmp(b), lp = lmp(a);
    if (lmove[lp][b]) printlef(lp,b);
    else printrig(rp, a);
}

int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> C >> n;
    for (int i=0; i!=n; ++i){
        int a,b;
        cin >> a >> b;
        path[--a][--b] = path[b][a] = true;
    }
    for (int i=0; i<C; ++i)
    if (rigmove(i,i)){
        printrig(i, i);
        break;
    }
    printf("%d", -1);
    return 0;
}
