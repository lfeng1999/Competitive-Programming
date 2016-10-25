#include <bits/stdc++.h>

using namespace std;

vector<int> motels{0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
int dp[51];

int main()
{
    //freopen("CCC.txt", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int A, B, M;
    cin >> A >> B >> M;
    for (int i=0; i<M; ++i){
        int t;
        cin >> t;
        motels.push_back(t);
    }
    sort(motels.begin(), motels.end()); //lowest to highest

    dp[0] = 1; //Set first motel as 1

    for (int i=1; i<motels.size(); ++i){
        for (int j=i-1; j>=0; j--){
            if (A <= motels[i] - motels[j] && motels[i] - motels[j] <= B)
                dp[i] += dp[j];
        }
    }
    cout << dp[motels.size()-1];


    return 0;
}
