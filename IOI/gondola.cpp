#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint MOD = 1000000009;
int subtask, n, arr[250010];

lint mypow(lint a, int b){
	if (b == 1) return a;
	else if (b == 0) return 1;
	lint cur = mypow(a, b/2);
	cur *= cur; cur %= MOD;
	if (b%2){
		cur *= a;
		cur %= MOD;
	}
	return cur;
}

int solve1(){
	cin >> n;
	int rot;
	set<int> past;
	for (int i=0; i<n; ++i){
		cin >> arr[i]; --arr[i];
		if (past.count(arr[i])){
			return 0;
		}
		past.insert(arr[i]);
		if (arr[i] < n) rot = arr[i] - i;
	}
	rot += n; rot %= n;
	for (int i=0; i<n; ++i){
		if (arr[i] < n){
			if ((arr[i] - i + n)%n != rot){
				return 0;
			}
		}
	}
	return 1;
}

void solve2(){
	int rot = -1, maxval = 0;
	for (int i=0; i<n; ++i){
		if (arr[i] < n) rot = arr[i] - i;
		maxval = max(maxval, arr[i]);
	}
	rot += n; rot %= n;
	rotate(arr, arr + n - rot, arr + n);
	cout << maxval - n + 1 << " ";
	vector<pair<int,int>> V;
	for (int i=0; i<n; ++i){
		if (arr[i] >= n){
			V.push_back(make_pair(arr[i], i));
		}
	}
	sort(V.begin(), V.end());
	int cur = n-1;
	for (auto &it : V){
		int to = it.first, st = it.second;
		cout << it.second + 1 << " ";
		cur++;
		while (cur != to){
			cout << cur + 1 << " ";
			cur++;
		}
	}
}
lint solve3(){
	int isvalid = solve1();
	if (!isvalid) return 0;
	lint ret = 1;
	int rot = -1, maxval = 0;
	set<int> past2;
	for (int i=0; i<n; ++i){
		if (arr[i] < n) rot = arr[i] - i;
		maxval = max(maxval, arr[i]);
		past2.insert(arr[i]);
	}
	past2.insert(n-1);

	int ntop = 0;
	for (auto it = --past2.end(); *it >= n; --it){
		auto it2 = it; --it2;
		++ntop;
		ret *= mypow(ntop, (*it) - (*it2) - 1);
		ret %= MOD;
	}
	if (rot == -1){
		ret *= n;
		ret %= MOD;
	}
	return ret;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> subtask;
	if (subtask <= 3){
		cout << solve1() << '\n';
	}
	else if (subtask <= 6){
		int s1 = solve1();
		if (s1 == 0){
			cout << 0 << '\n';
		}
		else{
			solve2();
		}
	}
	else if (subtask <= 10){
		cout << solve3() << '\n';
	}

	return 0;
}