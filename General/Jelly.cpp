#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Pos{
    int x, y, z;
    Pos(int x, int y, int z){
        this->x = x, this->y = y, this->z = z;
    }
};

int grid[155][155][155], mv[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}}, ans[155][155][155];
bool past[155][155][155];
int SX, SY, SZ, XX, YY, ZZ;

bool outofrange(int x, int y, int z){
    if (x == 0 || y == 0 || z == 0 || x > XX || y > YY || z > ZZ)
        return true;
    return false;
}
bool border(int x, int y, int z){
    if (x == 1 || y == 1 || z == 1 || x == XX || y == YY || z == ZZ)
        return true;
    return false;
}

int main()
{
//    freopen("Mac.txt","r",stdin);
    scanf("%d%d%d", &XX, &YY, &ZZ);
    for (int i=1; i<=ZZ; ++i){
        for (int j=1; j<=YY; ++j){
            for (int k=1; k<=XX; ++k){
                char ch; scanf(" %c", &ch);
                if (ch == 'J'){
                    SX = k, SY = j, SZ = i;
                    continue;
                }
                grid[k][j][i] = ch - '0';
                ans[k][j][i] = 2e9;
            }
        }
    }
    queue<Pos> Q;
    Q.push(Pos(SX, SY, SZ));
    past[SX][SY][SZ] = true;
    ans[SX][SY][SZ] = 0;
    int cnt = 0;
    while (!Q.empty()){
        int x = Q.front().x, y = Q.front().y, z = Q.front().z;
        Q.pop();
        if (outofrange(x,y,z)){
            continue;
        }
        past[x][y][z] = false;
        for (int i=0; i<6; ++i){
            int nx = x + mv[i][0], ny = y + mv[i][1], nz = z + mv[i][2];
            int nd = ans[x][y][z] + grid[nx][ny][nz];
            //printf("%d\n", nd);
            if (nd < ans[nx][ny][nz]){
                ans[nx][ny][nz] = nd;
                if (!past[nx][ny][nz]){
                    Q.push(Pos(nx,ny,nz));
                    past[nx][ny][nz] = true;
                }
            }
        }
    }
    int best = 2e9;
    for (int j=1; j<=YY; ++j){
        for (int k=1; k<=XX; ++k){
            best = min(best, min(ans[k][j][1], ans[k][j][ZZ]));
        }
    }
    for (int j=1; j<=XX; ++j){
        for (int k=1; k<=ZZ; ++k){
            best = min(best, min(ans[j][1][k], ans[j][YY][k]));
        }
    }
    for (int j=1; j<=YY; ++j){
        for (int k=1; k<=ZZ; ++k){
            best = min(best, min(ans[1][j][k], ans[XX][j][k]));
        }
    }
    printf("%d\n", best);
    return 0;
}