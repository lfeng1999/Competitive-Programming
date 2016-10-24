#include <bits/stdc++.h>

using namespace std;

int N;
int arr[1000010][2];
int dp[1000010], extratm = 0;

int main()
{
  //  freopen("WoburnChallenge.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i) cin >> arr[i][0] >> arr[i][1];
    for (int i=1; i<=N; ++i){
        dp[i] = dp[i-1] + max(0,arr[i][1] - (arr[i][0] - arr[i-1][0]) - extratm);
        extratm = max(0, extratm - arr[i][1] + (arr[i][0] - arr[i-1][0]));
        //cout << dp[i] << " " << extratm << endl;
    }
    cout << dp[N];
    return 0;
}