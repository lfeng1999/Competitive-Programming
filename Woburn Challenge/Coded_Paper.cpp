#include <bits/stdc++.h>

using namespace std;

#define max4(a, b, c, d) max(max(a,b), max(c, d))
#define max5(a, b, c, d, e) max(a, max4(b,c,d,e))
#define max3(a, b, c) max(a, max(b,c))
int N, R, grid[100010][2];
int dp1[100010], dp2[100010], dp3[100010], dp4[100010], dp5[100010];
//  none,       bottom,         top,       both         both individual

int main()
{
//    freopen("WoburnChallenge.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> R;

    for (int i=1; i<=N; ++i){
        cin >> grid[i][0];
    }
    for (int i=1; i<=N; ++i){
        cin >> grid[i][1];
    }

    dp1[1] = grid[1][0] + grid[1][1];
    dp2[1] = R + grid[1][1];
    dp3[1] = R + grid[1][0];
    dp4[1] = R;
    dp5[1] = 2*R;
    for (int i=2; i<=N; ++i){
        int max_before = max5(dp1[i-1], dp2[i-1], dp3[i-1], dp4[i-1], dp5[i-1]);
        dp1[i] = max_before + grid[i][0] + grid[i][1];
        //Correct

        dp2[i] = max_before + R + grid[i][1];
        dp2[i] = max3(dp2[i], dp2[i-1] + grid[i][1], dp5[i-1] + grid[i][1]);

        // dp3

        dp3[i] = max_before + R + grid[i][0];
        dp3[i] = max3(dp3[i], dp3[i-1] + grid[i][0], dp5[i-1] + grid[i][0]);

        // dp4

        dp4[i] = max_before + R;
        dp4[i] = max(dp4[i], dp4[i-1]);

        // dp5

        dp5[i] = max_before + 2*R;
        dp5[i] = max4(dp5[i], dp2[i-1] + R, dp3[i-1] + R, dp5[i-1]);


    }
//    for (int i=1; i<=N; ++i){
//        cout << dp1[i] << " " << dp2[i] << " " << dp3[i] << " " << dp4[i] << " " << dp5[i] << endl;
//}
    cout << max5(dp1[N], dp2[N], dp3[N], dp4[N], dp5[N]);

    return 0;
}
