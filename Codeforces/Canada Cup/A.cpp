#include <bits/stdc++.h>

using namespace std;

bool fallable[200010], past[200010];
int N;
char grid[200010];

bool solve(int pos){
    if (pos == 0 || pos == N + 1) return true;
    if (past[pos]) return fallable[pos];
    past[pos] = true;
    if (grid[pos] == '<') return fallable[pos]= solve(pos-1);
    else return fallable[pos]=solve(pos+1);
}

int main(){
//	freopen("CF.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i=1; i<=N; ++i){
        cin >> grid[i];
    }
    int ans = 0;
    for (int i=1; i<=N; ++i){
        if (!past[i])
            solve(i);
        ans += fallable[i];
    }
    cout << ans;

	return 0;
}