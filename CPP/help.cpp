#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define pii pair<int, int>
#define p3i pair<pii, int>
#define pll pair<ll, ll>
#define p3l pair<pll, ll>
#define lseg L, (L+R)/2, N*2+1
#define rseg (L+R)/2+1, R, N*2+2
#define ub upper_bound
#define lb lower_bound

int n, k, m, q, a, b, c=0;
int bit[100005], r[100005];
bool u[100005];
vector<int> v[100005];
void bitadd(int P){
    for (; P<=n; P+=P&-P) bit[P]++;
}
int bitsum(int P){
    int C=0; for (; P>0; P-=P&-P) C+=bit[P]; return C;
}
void dfs(int N){
    if (r[N]>0) return; r[N]=++c;
    for (int l=0; l<v[N].size(); ++l) dfs(v[N][l]);
}
int check(int N){
    if (u[N]) return 0;
    bool B=1;
    for (int l=0; l<v[N].size(); ++l){
        if (v[N][l]<a || v[N][l]>b) continue;
        if (r[v[N][l]]<r[N]) B=0;
    }
   // cout << N << ' ' << B << endl;
    return B;
}
int main(){
    scanf("%i%i%i", &n, &k, &m);
    for (int l=0; l<m; ++l){
        scanf("%i%i", &a, &b);
        v[a].pb(b); v[b].pb(a);
    }
    for (int l=1; l<=n; ++l)
        if (r[l]==0){
            dfs(l);
            bitadd(l); u[l]=1;
        }
    //cout << endl;
    scanf("%i", &q);
    for (int l=0; l<q; ++l){
        scanf("%i%i", &a, &b); c=0;
        for (int l2=a; l2<=min(b, a+k-1); ++l2) c+=check(l2);
        for (int l2=max(a+k, b-k+1); l2<=b; ++l2) c+=check(l2);
        c+=bitsum(b)-bitsum(a-1);
        printf("%i\n", c);
    }
    return 0;
}