#include <bits/stdc++.h>

using namespace std;

vector<pair<int,pair<int,char> > > cars;
// row, column, move

int bit[2501][2501], bit2[2501][2501];
bool done[5000000];
//updown            //left right
void update(int rr, int cc, int val)
{
    for (int r = rr; r <= 2010; r+=r&(-r))//updown
        bit[r][cc]+=val;// column is constant, row shift
    for (int c = cc; c <= 2010; c+=c&(-c))//left right
        bit2[rr][c]+=val;
}
int query(int r,int c, char dir)
{
    int tot = 0;
    if (dir == 'C')
        for (; r > 0; r-=r&(-r))//updown
            tot+=bit[r][c];
    else if (dir == 'R')
        for (; c > 0; c-=c&(-c))
            tot+=bit2[r][c];
    return tot;
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    int N,M;
    cin >> N >> M;
    for (int i=1; i<=N; ++i)
    for (int j=1; j<=M; ++j)
    {
        char a;
        cin >> a;
        if (a!='.')
        {
            cars.push_back(make_pair(i,make_pair(j,a)));
            update(i,j,1);
        }
    }
    int a=0;
    while (!cars.empty())
    {
        a = 1-a;
        vector<int> del;
        bool flag = false;
        if (a==0)
        {
            for (int i=0; i!=cars.size(); ++i)
            {
                if (done[i]) continue;
                int r = cars[i].first, c = cars[i].second.first;
                char dir = cars[i].second.second;
                int v1 = query(r,c,'C')-1, v2 = query(r,c,'R')-1;
                if (dir == 'N')
                {
                    if (v1 == 0)
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'S')
                {
                    if (v1+1 == query(N,c,'C'))
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'E')
                {
                    if (v2+1 == query(r,M,'R'))
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'W')
                {
                    if (v2 == 0)
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
            }
        }
        else
            for (int i=cars.size()-1; i>=0; --i)
            {
                if (done[i]) continue;
                int r = cars[i].first, c = cars[i].second.first;
                char dir = cars[i].second.second;
                int v1 = query(r,c,'C')-1, v2 = query(r,c,'R')-1;
                if (dir == 'N')
                {
                    if (v1 == 0)
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'S')
                {
                    if (v1+1 == query(N,c,'C'))
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'E')
                {
                    if (v2+1 == query(r,M,'R'))
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
                else if (dir == 'W')
                {
                    if (v2 == 0)
                    {
                        del.push_back(i);
                        update(r,c,-1);
                        done[i] = true;
                        flag = true;
                    }
                }
            }
        for (int i=0; i!=del.size(); ++i)
        {
            printf("(%d,%d)\n",cars[del[i]].first-1,cars[del[i]].second.first-1);
        }
        if (!flag)
            break;
    }

}