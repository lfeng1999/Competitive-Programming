#include <bits/stdc++.h>

using namespace std;

int coal[8] = {0,1,1,2,1,2,2,3};
int dp[4][4][4][4][2], num[100010];

int diff(int i, int j, int k){
    return coal[((1 << i) | (1 << j) | (1 << k))/2];
}

int main(){
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    for (int qq=0; qq<N; ++qq){
        char ch;
        cin >> ch;
        num[qq] = (ch == 'M') ? 3 : (ch == 'F') + 1;
    }
    for (int qq = N-1; qq >= 0; --qq){
        int val = num[qq];
        for (int i=0; i<4; ++i)
        for (int j=0; j<4; ++j)
        for (int k=0; k<4; ++k)
        for (int l=0; l<4; ++l)
            dp[i][j][k][l][1&qq] = max(dp[i][j][l][val][1^(1&qq)] + diff(k,l,val), dp[j][val][k][l][1^(1&qq)] + diff(i,j,val));
    }
    cout << dp[0][0][0][0][0];
}
