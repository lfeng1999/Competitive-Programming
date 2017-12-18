#include <bits/stdc++.h>

using namespace std;

int N, a[100010];
pair<int,int> b[1000010]; 
int psum[1000010];
int Q, m[100010], ans[100010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> Q;
	for (int i=1; i<=N; ++i){
		cin >> b[i].first;
		b[i].second = i;
	}
	set<int> S;
	S.insert(0);
	S.insert(N+1);
	sort(b+1, b+1+N);
	reverse(b+1, b+1+N);
	for (int i=1; i<=N; ++i){
		int p = b[i].second;
		auto it = S.lower_bound(p);
		int rig = (*it) - p;
		int lef = p - (*(--it));
		psum[b[i].first] += rig*lef;
		S.insert(p);
	}
	for (int i=1; i<=1000000; ++i){
		psum[i] += psum[i-1];
	}
	for (int i=0; i<Q; ++i){
		int a, b; cin >> a >> b;
		cout << psum[b] - psum[a-1] << "\n";
	}

	return 0;
}