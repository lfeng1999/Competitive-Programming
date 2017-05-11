#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
int n, L, mlen[21], endtim[21];
int sdist[1100010];
vector<pair<int,int>> graph[21];

int main(){
	// freopen("test.txt","r",stdin);
	freopen("movie.in","r",stdin);
	freopen("movie.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> L;

	priority_queue<pii, vector<pii>, greater<pii>> Q;
	for (int i=0; i<n; ++i){
		endtim[i] = -1e9;
		cin >> mlen[i];
		int nm; cin >> nm;
		for (int qq=0; qq<nm; ++qq){
			int tim; cin >> tim;
			Q.push(make_pair(tim, i));
		}
	}
	int cur = 0;
	for (int i=0; i<1100010; ++i) sdist[i] = -1e9;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q2;
	Q2.push(make_pair(0, 0));
	sdist[0] = 0;
	int best = 1e9;
	while (!Q2.empty()){
		cur = Q2.top().first;
		bitset<21> b = Q2.top().second;
		int mask = Q2.top().second; Q2.pop();
		if (cur != sdist[mask]) continue;
		if (cur >= L){
			best = min(best, (int)b.count());
			continue;
		}
		while (!Q.empty() && Q.top().first <= cur){
			endtim[Q.top().second] = Q.top().first + mlen[Q.top().second];
			Q.pop();
		}
		for (int i=0; i<n; ++i){
			int id = (1 << i);
			if (!b.test(i) && endtim[i] >= cur && endtim[i] > sdist[id|mask]){
				sdist[id|mask] = endtim[i];
				Q2.push(make_pair(sdist[id|mask], id|mask));
			}
		}
	}
	if (best == 1e9)
		cout << -1;
	else
		cout << best;
	return 0;
}