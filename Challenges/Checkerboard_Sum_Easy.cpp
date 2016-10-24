#include <bits/stdc++.h>

using namespace std;

int dp[3001][3001], R, C;

int area(int a, int b)
{
    if (a < 0  || b < 0)
        return 0;
    return dp[a][b];
}

int query(int r, int c, bool col)
{
    if (r < 0 || c < 0)
        return 0;
    if ((r+c)%2 == col)
        return area(r,c) + area(r-1,c-1);
    return area(r-1,c) + area(r,c-1);
}

int bash2(int r1,int c1,int r2,int c2, bool col)
{
//    cout << r1 << " " << c1 << " " << r2 << " " << c2 << " " << col << endl;
//    cout << query(r1,c2 - 1,col) << endl << endl;
    return query(r2,c2,col) - query(r1-1,c2,col) - query(r2,c1-1,col) + query(r1-1,c1-1,col);
}

int bash(int r1,int c1,int r2,int c2)
{
    bool col = (r1+c1)%2;
    int x1 = bash2(r1,c1,r2,c2,col), x2 = bash2(r1,c1,r2,c2,!col);
//    cout << x1 << " " << x2 << endl;
    return x1 - x2;
}


int main()
{
//    freopen("CheckerEasy.txt","r",stdin);
    cin >> R >> C;
    int a = 1,b = 1,c = 1,d = 1;
    scanf("%d%d%d",&a,&b,&c);
    while (a!=0 || b!=0 || c!=0)
    {
        dp[a-1][b-1] = c;
        scanf("%d%d%d",&a,&b,&c);
    }
    for (int i=0; i!=R; ++i)
        for (int j=2; j!=C; ++j)
            dp[i][j] += dp[i][j-2];
    for (int i=2; i!=R; ++i)
        for (int j=0; j!=C; ++j)
            dp[i][j]+=dp[i-2][j];
//    for (int i=0; i!=R; ++i)
//    {
//        for (int j=0; j!=C; ++j)
//            cout << dp[i][j] << " ";
//        cout << endl;
//    }
    a = b = c = 1;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    while (a!=0 || b!=0 || c!=0 || d!=0)
    {
        int col = (a+b)%2;
        cout << bash(a - 1,b - 1,c - 1,d - 1) << endl;
        scanf("%d%d%d%d",&a,&b,&c,&d);
    }
    return 0;
}
