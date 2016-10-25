#include <bits/stdc++.h>

using namespace std;

int dp[1010][5010], len;
bool past[1010][5010];
string S, rig;

int solve(int i, int sum){
    int &ans = dp[i][sum];
    if (past[i][sum]) return ans;
    ans = 1e9;

    past[i][sum] = true;

    if (i == len){
        if (sum == 0) return ans = 0;
        return ans = 1e9;
    }

    int ctot = 0, j = i + 1;
    for (; j <= len; ++j){
        ctot *= 10; ctot += S[j] - '0';
        if (ctot > sum) break;
        if (j < len && ctot == 0 && S[j+1] == '0'){
            continue;
        }
        ans = min(ans, 1 + solve(j, sum - ctot));
    }
    return ans;
}

string get_string(int i, int sum){
    if (i == len) return "";

    int ctot = 0;
    for (int j = i + 1; j <= len; ++j){
        ctot *= 10; ctot += S[j] - '0';
        if (j < len && S[j+1] == '0' && ctot == 0) continue;
        if (dp[i][sum] == 1 + dp[j][sum - ctot]){
                return S.substr(i+1, j - i) + "+" + get_string(j, sum - ctot);
        }
    }
    return  "";
}


int main(){
    //freopen("COCI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> S;

    int idx = S.find("=");
    rig = S.substr(idx+1, S.length() - idx);
    S = S.substr(0, idx);

    len = S.length();
    S = " " + S;
    solve(0, stoi(rig));
    string mS = get_string(0, stoi(rig)); mS = mS.substr(0, mS.length()-1);
    cout << mS << "=" << rig;
    return 0;
}
