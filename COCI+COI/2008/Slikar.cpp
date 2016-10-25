#include <bits/stdc++.h>

using namespace std;

struct data
{
    int all0, all1, idk;
};

int N;
char grid[513][513], grid2[513][513];

data recur(int r, int c, int len)
{
    //cout << r << "  " << c << "  " << len << endl;
    data ret;
    if (len == 1)
    {
        ret.all0 = (grid[r][c]=='1');
        ret.all1 = (grid[r][c]=='0');
        ret.idk = 0;
        grid2[r][c] = grid[r][c];
        return ret;
    }
    int nlen = len/2;
    data pos[2][2];
    pos[0][0] = recur(r,c,nlen);
    pos[1][0] = recur(r+nlen,c,nlen);
    pos[0][1] = recur(r,c+nlen,nlen);
    pos[1][1] = recur(r+nlen,c+nlen,nlen);
    ret.all0 = ret.all1 = 0;
    for (int i=0; i!=4; ++i)
    {
        ret.all0+=pos[i>>1][i&1].all0;
        ret.all1+=pos[i>>1][i&1].all1;
    }
    ret.idk = 0x7fffffff;
    int mov[4] = {0,1,2,3}, best[4];
    do{
        int val =
            pos[mov[0]>>1][mov[0]&1].all0 +
            pos[mov[1]>>1][mov[1]&1].all1 +
            pos[mov[2]>>1][mov[2]&1].idk +
            pos[mov[3]>>1][mov[3]&1].idk;
        if (val < ret.idk)
        {
            for (int i=0; i!=4; ++i) best[i]=mov[i];
            ret.idk = val;
        }
    } while (next_permutation(mov,mov+4));

    for (int i=0; i!=nlen; ++i)
    for (int j=0; j!=nlen; ++j)
    {
        grid2[r+(best[0]>>1)*nlen+i][c+(best[0]&1)*nlen+j] = '0';
        grid2[r+(best[1]>>1)*nlen+i][c+(best[1]&1)*nlen+j] = '1';
    }

    return ret;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    scanf("%d",&N);
    for (int i=0; i!=N; ++i)
        scanf(" %s", grid[i]);
    data a = recur(0,0,N);
    printf("%d\n",a.idk);
    for (int i=0; i!=N; ++i)
    {
        printf("%s\n",grid2[i]);
    }
}
