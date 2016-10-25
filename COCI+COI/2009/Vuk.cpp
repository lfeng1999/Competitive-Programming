#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pair<int,int>> piii;

char grid[500][500];
int R, C, er, ec, sr, sc, sdist[500][500], dp[500][500];
int mov[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
bool past[500][500];
queue<piii> Q;
priority_queue<piii> q;

bool valid(int r,int c)
{
    if (r < 0 || c < 0 || r >= R || c >= C || past[r][c])
        return false;
    return true;
}
void bfs()
{
    while (!Q.empty())
    {
        piii a = Q.front(); Q.pop();
        int cnt = a.first, r = a.second.first, c = a.second.second;
        for (int i=0; i != 4; ++i)
        {
            int nr = r + mov[i][0], nc = c + mov[i][1];
            if (valid(nr,nc))
            {
                past[nr][nc]=true;
                sdist[nr][nc] = cnt+1;
                Q.push(make_pair(cnt+1,make_pair(nr,nc)));
            }
        }
    }
    memset(past,false,sizeof(past));
}

int pq()
{
    past[sr][sc] = true;
    while (!q.empty())
    {
        piii a = q.top(); q.pop();
        int cnt = a.first, r = a.second.first, c = a.second.second;
        for (int i=0; i!=4; ++i)
        {
            int nr = r + mov[i][0], nc = c + mov[i][1];
            int ncnt = min(cnt,sdist[nr][nc]);
            if (valid(nr,nc) && grid[nr][nc]!='+')
            {
                past[nr][nc] = true;
                dp[nr][nc] = ncnt;
                q.push(make_pair(ncnt,make_pair(nr,nc)));
            }
        }
    }
    return dp[er][ec];
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> R >> C;
    for (int i=0; i!=R; ++i)
    for (int j=0; j!=C; ++j)
    {
        char a;
        cin >> a;
        if (a=='J')
            er = i, ec = j;
        else if (a == 'V')
            sr = i, sc = j;
        else if (a == '+')
        {
            Q.push(make_pair(0,make_pair(i,j)));
            past[i][j] = true;
        }
        grid[i][j]=a;
    }
    bfs();
    q.push(make_pair(sdist[sr][sc],make_pair(sr,sc)));
    cout << pq();
}
