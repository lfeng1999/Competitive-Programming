#include <bits/stdc++.h>

using namespace std;

struct item
{
    char typ;
    int r,c,cnt;
    item(char a, int b, int cc, int d)
    {
        typ = a, r = b, c = cc, cnt = d;
    }
};

bool pos[50][50];
int R, C, er, ec, mov[4][2] = {{1,0},{-1,0},{0,1},{0,-1}}; //row,column, end row, end column

bool valid(char type, int r,int c)
{
    if (type == '*' && r == er && c == ec)
        return false;
    if (r < 0 || c < 0  || r >= R || c >= C || !pos[r][c])
        return false;
    return true;
}

int main()
{
    cin.sync_with_stdio(0);cin.tie(0);
    //freopen("COCI.txt","r",stdin);
    memset(pos,true,sizeof(pos));
    cin >> R >> C;
    item hedge = item('0',0,0,0);
    queue<item> Q;
    for (int i=0; i!=R; ++i)
    for (int j=0; j!=C; ++j)
    {
        char a;
        cin >> a;
        if (a == 'X')
            pos[i][j] = false;
        else if (a == '*')
        {
            item water('*',i,j, 0);
            pos[i][j] = false;
            Q.push(water);
        }
        else if (a == 'S')
            hedge = item('S',i,j,0);
        else if (a == 'D')
            er = i, ec = j;
    }
    Q.push(hedge);
    while (!Q.empty())
    {
        item t = Q.front(); Q.pop();
        char type = t.typ;
        int r = t.r, c = t.c, cnt = t.cnt;
        //cout << type << " " << r << " " << c << " " << cnt << endl;
        if (r == er && c == ec)
        {
            if (type == '*')
            {
                cout << "KAKTUS";
                return 0;
            }
            else if (type == 'S')
            {
                cout << cnt;
                return 0;
            }
        }
        for (int i=0; i!=4; ++i)
        {
            int nr = r+mov[i][0], nc = c+mov[i][1];
            if (valid(type,nr,nc))
            {
                pos[nr][nc] = false;
                Q.push(item(type,nr,nc,cnt + 1));
            }
        }
    }
    cout << "KAKTUS";
    return 0;
}
