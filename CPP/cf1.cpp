#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> s;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N; ++i){
		int x;
		cin >> x;
		s.push_back(x);
	}
	sort(s.begin(), s.end());
	int i = 0;
	for (; i!=s.size(); ++i){
		if (s[i] == s[0])
			continue;
		else
			break;
	}
	int j = N-1;
	for (; j>=0; --j){
		if (s[j] == s[N-1])
			continue;
		else
			break;
	}
	if (i > j){
		cout << 0;
		return 0;
	}
	cout << j-i+1;

	return 0;
}