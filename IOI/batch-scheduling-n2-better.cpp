#include <bits/stdc++.h>

using namespace std; //reverse dp :/ fml

int n, S;
int T[10010], sumT[10010], F[10010], sumF[10010];
int ans[10010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> S;
	for (int i=1; i<=n; ++i){
		cin >> T[i] >> F[i];
	}
	for (int i=n; i>=0; --i){
		sumT[i] = T[i] + sumT[i+1];
		sumF[i] = F[i] + sumF[i+1];
		ans[i] = 2e9;
		for (int j=i; j<=n; ++j){
			ans[i] = min(ans[i], ans[j+1] + sumF[i]*(S + sumT[i] - sumT[j+1]));
		}
	}
	cout << ans[0];
	return 0;
}