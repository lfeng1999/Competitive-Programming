#include <bits/stdc++.h>

using namespace std; //reverse dp :/ fml

struct State{
	int m, b;
};

int n, S;
int T[10010], sumT[10010], F[10010], sumF[10010];
int ans[10010];
vector<State> Q;
int idx = 0;

int intersect(State p1, State p2){
	double ret = (double)(p2.b - p1.b)/(double)(p1.m - p2.m);
	return (int)(ret + 1.0 - 1e-9);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> S;
	for (int i=1; i<=n; ++i){
		cin >> T[i] >> F[i];
	}
	Q.push_back({0, 0});
	for (int i=n; i>=0; --i){
		sumT[i] = T[i] + sumT[i+1];
		sumF[i] = F[i] + sumF[i+1];
		while (idx + 1 < Q.size() && intersect(Q[idx], Q[idx+1]) <= sumF[i]) ++idx;
		ans[i] = Q[idx].b + sumF[i]*Q[idx].m;
		ans[i] += sumF[i]*(S + sumT[i]);
		State nxt = {-sumT[i], ans[i]};
		while (Q.size() >= 2 && intersect(Q[Q.size()-2], nxt) > intersect(Q[Q.size()-1], nxt)){
			Q.pop_back();
		}
		Q.push_back(nxt);
		idx = min(idx, (int)Q.size() - 1);
	}
	cout << ans[0];
	return 0;
}