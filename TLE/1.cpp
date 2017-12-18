#include <bits/stdc++.h>

using namespace std;

map<string,int> M;

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	int N;
	cin >> N;

	for (int i=0; i<N; ++i){
		string word;
		cin >> word;
		if (!M.count(word)){
			M[word] = 1;
		}
		else{
			M[word] = M[word] + 1;
		}
	}

	int ans = 0;
	for (auto mpair : M){
		if (mpair.second == 1){
			ans += 1;
		}
	}
	cout << ans;


	return 0;
}