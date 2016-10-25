#include <bits/stdc++.h>

using namespace std;

int grid[810][810], N, S; bool bpast[810][810];
int mv[4][2] = {{1,0}, {-1, 0}, {0, 1}, {0, -1}}, sx, sy, ex, ey;

bool works(int tim){
    queue<pair<int,pair<int,int>>> Q;

    Q.push(make_pair(tim, make_pair(sx, sy)));
    bpast[sx][sy] = true;

    while (!Q.empty()){
        int sz = Q.size();

        while (sz-- && !Q.empty()){

            int cx = Q.front().second.first, cy = Q.front().second.second, ctime = Q.front().first;

            Q.pop();

            if (cx == ex && cy == ey) return true;


            for (int i=0; i<4; ++i){
                int nx = cx + mv[i][0], ny = cy + mv[i][1];

                if (nx < 0 || nx >= N || ny < 0 || ny >= N || bpast[nx][ny] || ctime + 1 >= grid[nx][ny]) continue;

                bpast[nx][ny] = true;

                Q.push(make_pair(ctime+1, make_pair(nx, ny)));
            }

        }
    }
    return false;
}

int bin_search(){
    int L = -1, R = (grid[sx][sy]/S) - 1;

    while (L < R){
        memset(bpast, false, sizeof(bpast));
        int mid = (L+R)/2.0 + 1;
        if (works(mid*S)) L = mid;
        else R = mid - 1;
    }
    return L;
}

int main(){
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    for (int i=0; i<810; ++i)
        fill(grid[i], grid[i] + 810, 1e9);

    cin >> N >> S;
    queue<pair<int,int>> hives;

    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            char ch;
            cin >> ch;
            if (ch == 'T') grid[i][j] = -1;
            else if (ch == 'H'){
                hives.push(make_pair(i, j));
                grid[i][j] = 0;
            }
            else if (ch == 'M') sx = i, sy = j;
            else if (ch == 'D') ex = i, ey = j;
        }
    }
    grid[ex][ey] = -1;
    while (!hives.empty()){
        int sz = hives.size();
        while (sz-- && !hives.empty()){
            int cx = hives.front().first, cy = hives.front().second;
            hives.pop();
            int ctime = grid[cx][cy];

            for (int j=0; j<4; ++j){
                int nx = cx + mv[j][0], ny = cy + mv[j][1];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N || grid[nx][ny] != 1e9) continue;
                grid[nx][ny] = ctime + S;
                hives.push(make_pair(nx, ny));
            }
        }
    }

    grid[ex][ey] = 1e9;
    if (!works(0)){
        printf("%d\n", -1);
        return 0;
    }
    printf("%d\n", bin_search());

    return 0;
}
