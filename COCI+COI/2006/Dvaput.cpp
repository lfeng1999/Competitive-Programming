#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 10000000000007, MAXN = 200003;
ll expp[MAXN], nword[MAXN];
string word;
int len;


bool hashing(int n)
{
    unordered_set<ll> hset;
    ll t = 0;
    for (int i=0; i!=n; ++i)
    {
        t*=26;
        t+=nword[i];
        t%=MOD;
    }
    hset.insert(t);
    for (int i = n; i<len; ++i)
    {
        t-=((nword[i-n]*expp[n-1])%MOD);
        t+=MOD;
        t%=MOD;
        t*=26;
        t+=nword[i];
        t%=MOD;
        if (!hset.insert(t).second)
            return true;
    }
    return false;
}


int bin_search(int n)
{
    int L = 0, R = n;
    while (L < R)
    {
        int avg = (L+R+1)/2;
        if (hashing(avg))
            L = avg;
        else
            R = avg - 1;
    }
    return L;
}

int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cin >> len >> word;
    int tot = 1;
    expp[0] = 1;
    for (int i=1; i!=MAXN; ++i)
        expp[i] = (expp[i-1]*26)%MOD;
    for (int i=0; i!=word.length(); ++i)
        nword[i] = word[i]-'a';
    cout << bin_search(len);
    return 0;
}
