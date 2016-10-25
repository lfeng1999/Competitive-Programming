#include <bits/stdc++.h>

using namespace std;

int N;
vector<pair<int,int>> sortx, sorty;

bool cmpx(const pair<int,int> &a, const pair<int,int> &b)
{
    if (a.first < b.first)
        return true;
    else if (a.first > b.first)
        return false;
    return (a.second < b.second);
}

bool cmpy(const pair<int,int> &a, const pair<int,int> &b)
{
    if (a.second < b.second)
        return true;
    else if (a.second > b.second)
        return false;
    return (a.first < b.first);
}

int xseg(int x1, int x2, int y1)
{
    pair<int,int> a = make_pair(x1,y1), b = make_pair(x2,y1);
    return upper_bound(sorty.begin(),sorty.end(),b,cmpy) - lower_bound(sorty.begin(),sorty.end(),a,cmpy);
}
int yseg(int x1, int y1, int y2)
{
    pair<int,int> a = make_pair(x1,y1), b = make_pair(x1,y2);
    return upper_bound(sortx.begin(),sortx.end(),b,cmpx) - lower_bound(sortx.begin(),sortx.end(),a,cmpx);
}

int main()
{
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0);cin.tie(0);
    cin >> N;
    for (int i=0;i!=N; ++i)
    {
        int a,b;
        cin >> a >> b;
        sortx.push_back(make_pair(a,b));
        sorty.push_back(make_pair(a,b));
    }
    sort(sortx.begin(),sortx.end(),cmpx);
    sort(sorty.begin(),sorty.end(),cmpy);
    //for (int i=0; i!=N; ++i)
    //    cout << sortx[i].first << " ";
    //cout << endl;
    int K;
    cin >> K;
    for (int i=0; i!=K; ++i)
    {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int tot = 0;
        tot += xseg(x1,x2,y1);
        tot += xseg(x1,x2,y2);
        tot += yseg(x1,y1+1,y2-1);
        tot += yseg(x2,y1+1,y2-1);
        printf("%d\n",tot);
    }
}
