#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
typedef long long ll;
ll L, R, dp[140][16], best = -1;

ll solve(int dig_sum, int dig_left, ll cur_sum){

    if (dig_sum < 0) return 0;

    if (dig_left == 0){
        if (dig_sum  != 0 || cur_sum > R || cur_sum < L) return 0;
        if (best == -1) best = cur_sum;
        return 1;
    }

    ll &ans = dp[dig_sum][dig_left];

    ll min_val = cur_sum, max_val = cur_sum + pow(10, dig_left) - 1;

    if (max_val < L || R < min_val) return 0;

    bool in_range = (L <= min_val && max_val <= R);

    if (in_range && ans != -1) return ans;

    ll cur_ans = 0;
    for (int i=0; i<10; ++i){
        cur_ans += solve(dig_sum - i, dig_left - 1, cur_sum + pow(10, dig_left-1) * i);
    }
    if (in_range) ans = cur_ans;

    return cur_ans;
}


int main()
{
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(dp, -1, sizeof(dp));
    int sum;
    cin >> L >> R >> sum;

    ll ans = solve(sum, 15, 0);

    cout << ans << endl << best << endl;


    return 0;
}
