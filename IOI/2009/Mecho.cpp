#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN = 810;
int N,S;
bool tree[MAXN][MAXN], past[MAXN][MAXN];
int t_occ[MAXN][MAXN], mv[4][2] = {{1,0},{-1,0},{0,1},{0,-1}}, H = 0, T = 0, dist[MAXN][MAXN];
pii spos, epos;
pii Q[MAXN*MAXN];

void occ_bfs(){//bfs with bee
    pii u, v;
    while (H < T){
        v = Q[H++];
        if (v == epos){
            continue;
        }
        for (int i=0; i!=4; ++i){
            u = make_pair(v.first + mv[i][0], v.second + mv[i][1]);
            if (u.first < 0 || u.second < 0 || u.first >= N || u.second >= N) continue;
            if (tree[u.first][u.second] || past[u.first][u.second]) continue;
            t_occ[u.first][u.second] = t_occ[v.first][v.second] + S;
            past[u.first][u.second] = true;
            Q[T++] = u;
        }
    }
}

bool valid(int tm){
    pii u, v;
    H = T = 0;
    memset(past,false,sizeof(past));
    Q[T++] = spos;
    dist[spos.first][spos.second] = tm;
    while (H < T){
        v = Q[H++];
        if (v == epos){
            return true;
        }
        if (dist[v.first][v.second] >= t_occ[v.first][v.second]) continue;
        for (int i=0; i!=4; ++i){
            u = make_pair(v.first + mv[i][0], v.second + mv[i][1]);
            if (u.first < 0 || u.second < 0 || u.first >= N || u.second >= N) continue;
            if (tree[u.first][u.second] || past[u.first][u.second]) continue;
            dist[u.first][u.second] = dist[v.first][v.second] + 1;
            past[u.first][u.second] = true;
            Q[T++] = u;
        }
    }
    return false;
}

int bin_search(){
    int L = -1, R = MAXN*MAXN;
    while (L < R){
        int mid = R - (R-L)/2;
        if (valid(mid*S)){
            L = mid;
        }
        else{
            R = mid - 1;
        }
    }
    return L;
}

int main()
{
//    freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> S;
    memset(t_occ,-1,sizeof(t_occ));
    for (int i=0; i!=N; ++i){
        for (int j=0; j!=N; ++j){
            char a;
            cin >> a;
            tree[i][j] = (a == 'T');
            if (a == 'H'){
                Q[T++] = make_pair(i,j);
                t_occ[i][j] = 0;
                past[i][j] = true;
            }
            else if (a == 'M'){
                spos = make_pair(i,j);
            }
            else if (a == 'D'){
                epos = make_pair(i,j);
            }
        }
    }
    occ_bfs();
    printf("%d",bin_search());
    return 0;
}
