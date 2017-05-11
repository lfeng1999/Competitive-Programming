#include <bits/stdc++.h>

using namespace std;

int n, cows[21], mid = 0;
unordered_map<int,unordered_set<int>> m1, m2;

void setup1(int i, int msk, int tot){
	if (i > mid){
		m1[tot].insert(msk);
		return;
	}
	msk = msk*2;
	setup1(i+1, msk, tot);
	setup1(i+1, msk+1, tot - cows[i]);
	setup1(i+1, msk+1, tot + cows[i]);
}
void setup2(int i, int msk, int tot){
	if (i == mid){
		m2[tot].insert(msk);
		return;
	}
	msk = msk*2;
	setup2(i-1, msk, tot);
	setup2(i-1, msk+1, tot - cows[i]);
	setup2(i-1, msk+1, tot + cows[i]);
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> cows[i];
	}
	mid = n/2;
	setup1(0, 0, 0);
	setup2(n-1, 0, 0);
	int ans = -1;
	set<int> nans;
	nans.insert(0);
	for (auto &it : m1){
		for (auto &msk1 : it.second){
			for (auto &msk2 : m2[-it.first]){
				nans.insert(msk1 | (msk2 << (mid+1)));
			}
		}
		// ans += it.second.size()*m2[-it.first].size();
	}
	cout << nans.size() - 1;
	return 0;
}