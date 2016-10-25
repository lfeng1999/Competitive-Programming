#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 1e6;
ll A[37], sum1[MAXN], sum2[MAXN];
int cnt = 0, cnt2 = 0;
map<ll, int> m1, m2;

void dfs(int pos, ll tot, int last){
    if (pos == last){
        sum1[cnt++] = tot;
        return;
    }
    dfs(pos+1, tot+A[pos], last);
    dfs(pos+1, tot, last);
}
void dfs2(int pos, ll tot, int last){
    if (pos == last){
        sum2[cnt2++] = tot;
        return;
    }
    dfs2(pos+1, tot+A[pos], last);
    dfs2(pos+1, tot, last);
}

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N, M;
    cin >> N >> M;
    for (int i=0; i<N; ++i) cin >> A[i];
    for (int i=N; i<N+M; ++i){
        cin >> A[i];
        A[i] *= -1;
    }
    sort(A, A+N+M);
    dfs(0, 0, (N+M)/2);
    dfs2((N+M)/2, 0, N+M);
    int sz = (int)pow(2, (N+M)/2), sz2 = (int)pow(2, N+M - (N+M)/2);
    sort(sum1, sum1+sz);
    sort(sum2, sum2+sz2);

//    for (int i=0; i<N+M; ++i) cout << A[i] << endl;
    for (int i=0; i<sz; ++i){
        m1[sum1[i]]++;
    }
    ll ans = 0;
    for (int i=0; i<sz2; ++i){
        if (m1.count(-sum2[i])){
            ans+=m1[-sum2[i]];
        }
    }
    cout << ans-1;


    return 0;
}
