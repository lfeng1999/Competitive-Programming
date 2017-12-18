#include <bits/stdc++.h>

using namespace std;

int n, seq[1100010];

bool failed[2610][2610];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	memset(seg, true, sizeof(seg));
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> seq[i];
		// cout << seq[i] << " ";
	}
	vector<pair<int,int>> answers;
	for (int len=3; len <=n; ++len){
		for (int i=0; i <= n-len; ++i){
			int a = seq[i], b = seq[i+len-1];
			if (b - a != len - 1 || failed[i][i+len-1]){
				continue;
			}
			bool cont = true;
			for (int j=i; j<=i+len-1; ++j){
				if (seq[j] < a || seq[j] > b){
					cont = false;
					break;
				}
			}
			if (!cont) continue;

			answers.push_back({i, i+len-1});
			for (int k=i; k>=0; --k){
				for (int l=i+len-1; l<n; ++l){
					if (failed[k][l]) break;
					failed[k][l] = true;
				}
			}
		}
	}
	sort(answers.begin(), answers.end());
	cout << answers.size() << '\n';
	for (auto it : answers){
		cout << it.first + 1 << " " << it.second + 1 << '\n';
	}

	return 0;
}