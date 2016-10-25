// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[51];
vector<int> motels {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};

int main()
{
    int A, B;
    cin >> A >> B;
    int N;
    cin >> N;
    for (int i=0; i<N; ++i){
        int m; cin >> m;
        motels.push_back(m);
    }
    sort(motels.begin(), motels.end());
    
    dp[0] = 1;
    
    for (int i=1; i<motels.size(); ++i){
        
        for (int j = i - 1; j >= 0; --j){
            
            if (A <= motels[i] - motels[j] && motels[i] - motels[j] <= B){
                dp[i] += dp[j];
            }
        }
    }
    cout << dp[motels.size() - 1];
    
    
    
}
