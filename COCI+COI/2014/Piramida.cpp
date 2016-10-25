#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Query{
    int id;
    ll r;
    Query(ll r, int id){
        this->r = r;
        this->id = id;
    }
};
ll MOD;
ll N, K, ans[50010];
int cnt, prefixcnt[1000010];
string word;
vector<Query> Q[26];

ll position(ll r){
    ll a = r, b = r-1;
    if (r%2 == 0){
        a/=2;
    }
    else{
        b/=2;
    }
    a%=MOD;
    b%=MOD;
    return (a*b)%MOD;
}

ll solve(ll r, int let){
    ll ans = 0, curpos = position(r);

    ans += (r/word.length())*cnt;
    r -= (r/word.length())*word.length();
    if (r == 0) return ans;
    if (curpos + r > word.length()){
        ans += prefixcnt[word.length()-1];
        ans -= prefixcnt[curpos-1];

        r -= word.length()-curpos;
        if (r == 0) return ans;
        ans += prefixcnt[r-1];
    }
    else{
        if (curpos+r-1 >= 0)
            ans += prefixcnt[curpos+r-1];
        if (curpos-1 >= 0){
            ans -= prefixcnt[curpos-1];
        }
    }
    return ans;
}

int main()
{
//    freopen("COCI.txt","r", stdin);

    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> word >> K;
    MOD = word.length();
    for (int i=0; i<K; ++i){
        char ch; ll r;
        cin >> r >> ch;
        Q[ch-'A'].push_back(Query(r, i));
    }
    for (int i=0; i<26; ++i){
        cnt=0;
        memset(prefixcnt, 0 , sizeof(prefixcnt));
        for (int j=0; j<word.length(); ++j){ //prefix counters
            if (j>=1)
                prefixcnt[j] += prefixcnt[j-1];
            if (word[j]-'A'!=i) continue;
            cnt++;
            prefixcnt[j]++;
        }
        for (int j=0; j<Q[i].size(); ++j){
            ll r = Q[i][j].r; int id = Q[i][j].id;
            ans[id] = solve(r, i);
        }
    }
    for (int i=0; i<K; ++i){
        printf("%lld\n",ans[i]);
//        cout << ans[i] << endl;
    }
    return 0;
}