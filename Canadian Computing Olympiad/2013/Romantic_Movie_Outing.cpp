#include <bits/stdc++.h>

using namespace std;

const int cy = 2005;
int bit[4200][4200], R, T, a, b;
bool seats[2010][1005];
char M;

void update(int x, int y, int val)
{
    for (; x < 4200; x+=x&-x)
        for (int yy = y; yy < 4200; yy+=yy&-yy)
            bit[x][yy]+=val;
}

int query(int x, int y)
{
    int tot = 0;
    for (; x > 0; x-=x&-x)
        for (int yy = y; yy > 0; yy -= yy&-yy)
            tot+=bit[x][yy];
    return tot;
}

int main()
{
    //freopen("Romantic.txt","r",stdin);
    memset(seats,true,sizeof(seats));
    scanf("%d%d",&R,&T);
    for (int i=0; i!=T; ++i)
    {
        scanf(" %c%d%d",&M,&a,&b);
        //cout << M << " " << a << " " << b << endl;
        if (a > 2004)
            continue;
        if (M == 'E')
        {
            seats[a][b] = false;
            update(cy+a-b,a+b-1,1);
        }
        else if (M == 'L')
        {
            seats[a][b] = true;
            update(cy+a-b,a+b-1,-1);
        }
        else if (M=='S')
        {
            if (!seats[a][b] || !seats[a][b + 1])
                cout << "No" << endl;
            else
                printf("%d\n",query(cy+a-b,a+b-1) + query(cy + a - b - 1, a + b));
        }
    }
    int mcnt = 2e9, mcnt2 = 2e9;
    for (int x = R+1; x<=2000; ++x)
    for (int y = 1; y<=1000; ++y)
    {
        if (seats[x][y])
        {
            int ans = query(cy+x-y,x+y-1);
            if (ans < mcnt)
            {
                mcnt2 = mcnt;
                mcnt = ans;
            }
            else if (ans < mcnt2)
                mcnt2 = ans;
        }
    }
    printf("%d",mcnt+mcnt2);
    return 0;
}
