#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll MOD = 100000;
int N;
ll dp[210][210];
string S;
char lef[3] = {'(','{','['}, rig[3] {')','}',']'};
bool lead_zero = false;

ll solve(int L, int R){
    ll &ans = dp[L][R];
    if (ans != -1) return ans;

    ans = 0;

    if (L > R){return ans = 1;}

    for (int mid = L + 1; mid <= R; mid += 2){
        for (int i=0; i<3; ++i){
            if (S[L] == lef[i] || S[L] == '?'){
                if (S[mid] == rig[i] || S[mid] == '?'){
                    ans += solve(L + 1, mid - 1) * solve(mid+1, R);
                    if (ans > MOD){
                        ans = MOD + ans%MOD;
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
//    freopen("COCI.in", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    memset(dp, -1, sizeof(dp));
    cin >> N >> S;
    ll ans = solve(0, N - 1);
    if (ans > MOD)
        printf("%05lld", ans%MOD);
    else
        printf("%lld", ans);

    return 0;
}
