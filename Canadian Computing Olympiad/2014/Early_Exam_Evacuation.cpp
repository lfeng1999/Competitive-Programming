#include <bits/stdc++.h>

using namespace std;

struct person
{
    long long up,down;
    person(long long a, long long b)
    {
        up = a, down = b;
    }
};

long long bit[100010], A, B, ans, N, M;
bool seats[100010][6];
vector<person> gone;

void update(long long x)
{
    for (; x <= N; x += x&-x)
        bit[x]++;
}
long long query(long long x)
{
    long long tot = 0;
    for (; x > 0; x -= x&-x)
        tot+=bit[x];
    return tot;
}

bool cmp(person a, person b)
{
    return (a.up - a.down) > (b.up - b.down);
}


int main()
{
    //freopen("Evacuation.txt","r",stdin);
    memset(seats,true,sizeof(seats));
    scanf("%lld%lld%lld%lld",&N,&M,&A,&B);
    for (long long i=0; i!=M; ++i)
    {
        long long a, b; char bb;
        scanf("%lld %c",&a,&bb);
        b = bb - 'A';
        seats[a][b] = false;
        if (b==2 || b== 3)
            update(a);
        long long up = 2*a - query(a), down = 2*(N - a + 1) - query(N) + query(a - 1), extra = 0;
        if (b == 0)
            extra+=seats[a][1];
        else if (b==5)
            extra+=seats[a][4];
        up+=extra;
        down+=extra;
        up*=A;
        down*=A;
        ans+=up;
        gone.push_back(person(up,down));
    }
    ans+=M*(M - 1)*B/2;
    sort(gone.begin(),gone.end(),cmp);
    long long best = ans;
    for (long long i=0; i != M; ++i)
    {
        ans = ans - gone[i].up + gone[i].down - (M - i - 1) * B + i * B;
        best = min(best,ans);
    }
    cout << best;

}
