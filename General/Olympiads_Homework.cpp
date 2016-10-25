#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 13;

ll pow2(ll v){
    if (v == 0) return 1;
    if (v%2 == 1) return (2*(pow2(v/2)*pow2(v/2))%MOD)%MOD;
    else return (pow2(v/2)*pow2(v/2))%MOD;
}

int main()
{
    //freopen("TLE.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    ll n;
    cin >> n;
    if (n == 0 || n == 1 || n == 2 || n == 3){
        cout << 1; return 0;
    }
    if (n%8 == 0){
        cout << (pow2(n-2) + pow2((n-2)/2))%MOD;
    }
    else if (n%8 == 1 || n%8 == 7){
        cout << (pow2(n-2) + pow2((n-3)/2))%MOD;
    }
    else if (n%8 == 2 || n%8 == 6){
        cout << (pow2(n-2))%MOD;
    }
    else if (n%8 == 3 || n%8 == 5){
        cout << (pow2(n-2) - pow2((n-3)/2) + MOD)%MOD;
    }
    else if (n%8 == 4){
        cout << (pow2(n-2) - pow2((n-2)/2) + MOD)%MOD;
    }

    return 0;
}