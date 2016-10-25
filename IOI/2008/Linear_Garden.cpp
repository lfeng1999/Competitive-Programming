#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int N,  gard[1000010];
ll MOD, pow2[1000010];
string S;

int main()
{
    //freopen("IOI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N >> MOD >> S;

    for (int i = 0; i < N; ++i){
        if (S[i] == 'L')
            gard[i] = -1;
        else
            gard[i] = 1;
    }


    ll p2 = 1;
    for (int i = 0; i <= N; ++i){
        pow2[i] = p2;
        p2 *= 2;
        p2 %= MOD;
    }

    int lo2 = 0, hi2 = 0, dyn = 0;

    for (int i = 0; i < N; ++i){
        dyn += gard[i];
        lo2 = min(lo2, dyn);
        hi2 = max(hi2, dyn);
    }

    if (lo2 == -2 && hi2 == 0){
        ll ans = 1;
        for (int i = 1; i < N; i += 2){
            if (gard[i] == 1){
                ans += pow2[(N-1-i)/2];
                ans %= MOD;
            }
        }
        cout << ans;
    }
    else if (lo2 == -1 && hi2 == 0){
        cout << pow2[N/2];
    }
    else if (lo2 == -1 && hi2 == 1){
        ll ans = pow2[N/2];

        for (int i = 0; i < N; i += 2){
            if (gard[i] == 1){
                ans += pow2[(N-1-i)/2];
                ans %= MOD;
            }
        }

        cout << ans;
    }
    else if (lo2 == 0 && hi2 == 1){
        cout << (pow2[N/2] - 1 + pow2[(N+1)/2])%MOD;
    }
    else if (lo2 == 0 && hi2 == 2){
        ll ans = pow2[N/2] - 1 + pow2[(N+1)/2];
        for (int i = 1; i < N; i += 2){
            if (gard[i] == 1){
                ans += pow2[(N-1-i)/2];
                ans %= MOD;
            }
        }
        cout << ans;
    }
    return 0;
}
