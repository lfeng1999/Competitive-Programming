#include <bits/stdc++.h>

using namespace std;

int bit[3001][3001], vals[3001][3001], R, C, oper, a,b,c,d;
        // ==0, ==1 mod 2
void update(int r, int c, int val)
{
    for (; r <= R; r+= r&-r)
        for (int cc = c; cc <= C; cc+=cc&-cc)
            bit[r][cc]+=val;
}

int query(int r,int c)
{
    int tot = 0;
    for (; r > 0; r-=r&-r)
        for (int cc = c; cc > 0; cc-=cc&-cc)
            tot+=bit[r][cc];
    return tot;
}

int bash(int r1,int c1,int r2,int c2)
{
    return query(r2,c2) - query(r1-1,c2) - query(r2,c1-1) + query(r1-1,c1-1);
}

int main()
{
    scanf("%d%d",&R,&C);
    while (true)
    {
        scanf("%d",&oper);
        if (oper == 0)
            break;
        else if (oper == 1)
        {
            scanf("%d%d%d",&a,&b,&c);
            int col = (a+b)%2;
            update(a,b,-vals[a][b]);
            if (col == 0)
            {
                vals[a][b] = c;
                update(a,b, c);
            }
            else if (col == 1)
            {
                vals[a][b] = -c;
                update(a,b, -c);
            }
        }
        else if (oper == 2)
        {
            scanf("%d%d%d%d",&a,&b,&c,&d);
            int col = (a+b)%2, ans = bash(a,b,c,d);
            if (col == 0)
                printf("%d\n",ans);
            else if (col == 1)
                printf("%d\n",-ans);
        }
    }
    return 0;

}
