/*
String Theory DP
suppose there's a string abcsabct
And then we looked at abcsabcs
First we check the 2 strings
"abcsabc" matches
but then abcsabc"t" has that "t" this coincides with the abcsabc"s"
*/
#include <bits/stdc++.h>

using namespace std;

int nxt[1010][26], dp[10010][1010];
string st1, st2;
int s1[10010], s2[10010];
int len1, len2;
int solve(int i, int j){
    int &ret = dp[i][j];
    if (ret != -1) return ret;
    if (j == len2) return 1e9;
    if (i == len1) return 0;
    // cout << 2 << " " <<
    ret = 1e9;
    ret = min(ret, solve(i+1, nxt[j][s1[i]]));
    //if we remove s2[j]...
    ret = min(ret, 1+solve(i+1, j));
    // cout << i << " " << j << " " << ret << endl;
    return ret;
}
int main(){
	// freopen("test.txt","r",stdin);
    freopen("necklace.in","r",stdin);
    freopen("necklace.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
    for (int qq=0; qq<10010; ++qq) fill(dp[qq], dp[qq] + 1010, -1);
	cin >> st1 >> st2;
	len1 = st1.length(); len2 = st2.length();
	for (int i=0; i<len1; ++i) s1[i] = st1[i] - 'a';
	for (int i=0; i<len2; ++i) s2[i] = st2[i] - 'a';



    for (int i=0; i<len2; ++i){
        int prev = nxt[i][s2[i]];
        nxt[i][s2[i]] = i+1;
        for (int j=0; j<26; ++j){
            nxt[i+1][j] = nxt[prev][j];
        }
    }

    cout << solve(0, 0);
    // cout << solve(3, 2);



	return 0;
}