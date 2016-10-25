#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
int T, N;
int dp[5010], how[5010], break_len[5010];
int break_time[5010];

int main(){
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(how, -1, sizeof(how));
    memset(break_time, -1, sizeof(break_time));

    cin >> T >> N;
    for (int i=0; i<N; ++i){
        cin >> break_len[i];

        for (int j = T; j >= break_len[i]; --j){
            if (dp[j] < dp[j - break_len[i]] + break_len[i]){
                dp[j] = dp[j - break_len[i]] + break_len[i];
                how[j] = i;
            }
        }
    }

    for (int i = T; how[i] != -1; i -= break_len[how[i]]){
        break_time[how[i]] = i - break_len[how[i]];
    }

    int t2 = 0;

    for (int i=0; i<N; ++i){
        if (break_time[i] == -1){
            cout << t2 << " ";
            t2 += break_len[i];
        }
        else{
            cout << break_time[i] << " ";
        }
    }

    return 0;
}
