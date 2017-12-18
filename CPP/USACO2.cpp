#include <bits/stdc++.h>

using namespace std;

int bit[100010], c1[100010], c2[100010], N;

int query(int i){
	int tot = 0;
	for (; i > 0; i -= i&(-i))
		tot = max(tot, bit[i]);
	return tot;
}
void update(int i,int val){
	for (; i< 100010; i += i&(-i))
		bit[i] = max(bit[i], val);
}

int main(){
	freopen("nocross.in","r",stdin);
	freopen("nocross.out","w",stdout);
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		int x;
		cin >> x;
		c1[x] = i;
	}
	for (int i=1; i<=N; ++i){
		int c; cin >> c;
		vector<int> V;
		for (int j = max(1, c - 4); j <= min(N, c + 4); ++j){
			V.push_back(c1[j]);
		}
		sort(V.begin(), V.end());
		reverse(V.begin(), V.end());
		for (int x : V){
			update(x, query(x-1) + 1);
		}
	}
	cout << query(N);
	return 0;
}