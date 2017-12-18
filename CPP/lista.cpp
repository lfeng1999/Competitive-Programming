#include <bits/stdc++.h>

using namespace std;

int N, L[500010], R[500010], M, ord[500010], c[500010], lislen[500010];
bool inlis[500010];


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<=N+1; ++i){
		L[i] = i-1;
		R[i] = i+1;
	}
	cin >> M;
	for (int i=0; i<M; ++i){
		char ch; int x, y;
		cin >> ch >> x >> y;
		if (ch == 'A'){
			int rx = R[x], lx = L[x];
			R[lx] = rx;
			L[rx] = lx;
			int ly = L[y], ry = R[y];
			R[ly] = x;
			L[x] = ly;
			L[y] = x;
			R[x] = y;
		}
		else{
			int rx = R[x], lx = L[x];
			R[lx] = rx;
			L[rx] = lx;
			int ly = L[y], ry = R[y];
			L[ry] = x;
			R[x] = ry;
			L[x] = y;
			R[y] = x;
		}
	}
	int v = 0;
	for (int i=1; i<=N; ++i){
		if (L[i] == 0){
			v = i;
		}

	}
	for (int i=1; i<=N; ++i){
		ord[i] = v;
		v = R[v];
		// cout << ord[i] << " ";
	}
	// cout << endl;
	set<int> S;
	for (int i=1; i<=N; ++i){
		auto it = S.upper_bound(ord[i]);
		auto it2 = it;
		if (it2 != S.begin()){
			--it2;
			c[ord[i]] = *it2;
		}
		if (it != S.end())
			S.erase(it);
		S.insert(ord[i]);
	}
	printf("%d\n", N-S.size());
	int mlis = 0, p = 0;
	for (int i=1; i<=N; ++i){
		lislen[i] = lislen[c[i]] + 1;
		if (lislen[i] > mlis){
			mlis = lislen[i];
			p = i;
		}
	}
	while (true){
		inlis[p] = true;
		if (c[p] == 0)
			break;
		p = c[p];
	}
	for (int i=1; i<p; ++i){
		printf("%c %d %d\n", 'A', i, p);
	}
	for (int i=p+1; i<=N; ++i){
		if (inlis[i]){
			continue;
		}
		printf("%c %d %d\n", 'B', i, i-1);
	}




	return 0;
}