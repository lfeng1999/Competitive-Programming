#include <bits/stdc++.h>

using namespace std;

struct pos{
    int mx, my, bx, by, moves;
    pos(int mx, int my, int bx, int by, int moves){
        this->mx = mx;
        this->my = my;
        this->bx = bx;
        this->by = by;
        this->moves = moves;
    }
};
bool past[50][50][50][50];
bool is_wall[50][50];
int fx, fy, mv[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};


int main()
{
  //  freopen("Glenforest.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int R, C, sx=0, sy=0, sbx=0, sby=0, moves;
    cin >> R >> C;
    for (int i=1; i<=R; ++i){
        for (int j=1; j<=C; ++j){
            char ch;
            cin >> ch;
            if (ch == '#')
                is_wall[i][j] = true;
            else if (ch == 'P')
                sy = i, sx = j;
            else if (ch == 'B')
                sby = i, sbx = j;
            else if (ch == 'X')
                fy = i, fx = j;
        }
    }
//    cout << fy << " " << fx << endl;
    for (int i=0; i <= C+1; i++){
        is_wall[0][i] = is_wall[R+1][i] = true;
    }
    for (int i=0; i <= R+1; i++){
        is_wall[i][0] = is_wall[i][C+1] = true;
    }
    queue<pos> Q;
    Q.push(pos(sx, sy, sbx, sby, 0));
    past[sy][sx][sby][sbx] = true;
    int mx, my, bx, by;
    while (!Q.empty()){
        pos v = Q.front(); Q.pop();
        mx = v.mx, my = v.my, bx = v.bx, by = v.by, moves = v.moves;
//        cout << my << " " << mx << " " << by << " " << bx << " " << moves << endl;
        if (moves > 30000) break;

        if (bx == fx && by == fy){
            cout << moves;
            return 0;
        }
        for (int i=0; i<4; ++i){
            int nx = mx + mv[i][0], ny = my + mv[i][1], nbx = bx, nby = by;
            if (nx == bx && ny == by){
                nbx = nx + mv[i][0], nby = ny + mv[i][1];
            }
            if (is_wall[ny][nx] || is_wall[nby][nbx]) continue;
            if (past[ny][nx][nby][nbx]) continue;
            past[ny][nx][nby][nbx] = true;
            Q.push(pos(nx, ny, nbx, nby, moves+1));
        }
    }
    cout << -1;

    return 0;
}