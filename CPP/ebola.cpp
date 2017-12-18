#include <bits/stdc++.h>

using namespace std;

int N, M, root[100010], subsz[100010];

int find(int i){
	if (root[i] == i) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	int r1 = find(a);
	int r2 = find(b);

	if (r1 == r2) return;

	if (subsz[r1] < subsz[r2]){
		root[r2] = r1;
		subsz[r1] += subsz[r2];
	}
	else{
		root[r1] = r2;
		subsz[r2] += subsz[r1];
	}
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N >> M;
	for (int i=1; i<=N; ++i){
		root[i] = i;
		subsz[i] = 1;
	}

	for (int i=0; i<M; ++i){
		int cnt;
		cin >> cnt;
		int s; cin >> s;
		for (int i=0; i<cnt-1; ++i){
			int s2; cin >> s2;
			merge(s, s2);
		}
	}
	int ans = 0;
	for (int i=1; i<=N; ++i){
		if (find(1) == find(i)){
			ans++;
		}
	}
	cout << ans << '\n';

	for (int i=1; i<=N; ++i){
		if (find(1) == find(i)){
			cout << i << " ";
		}
	}


	return 0;
}