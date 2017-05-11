#include <bits/stdc++.h>

using namespace std;

int sf[1000010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	for (int qq=0; qq<t; ++qq){
		
		int N;
		cin >> N;
		int j=1, best = 0;
		for (int i=1; i<=N; ++i){
			cin >> sf[i];
		}
		set<int> S;
		int L = 1, R = 1;
		while (R <= N){
			while (R <= N && !S.count(sf[R])){
				S.insert(sf[R++]);
			}
			best = max(best, R - L);
			S.erase(sf[L++]);
		}
		cout << best << '\n';
	}

	return 0;
}