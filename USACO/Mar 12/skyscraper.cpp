#include <bits/stdc++.h>

using namespace std;

inline bool test(int n, int b){return (n >> b)&1;}
int n, maxw, w[18], bt[1 << 18];
bool past[1 << 18];
pair<int,int> best[1 << 18];

int main(){
	freopen("skyscraper.in","r",stdin);
	freopen("skyscraper.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> maxw;
	for (int i=0; i<n; ++i){
		cin >> w[i];
	}
	for (int i=0; i<(1<<n); ++i) best[i] = make_pair(1e9, 1e9);
	queue<int> Q; Q.push(0);
	past[0] = true;
	best[0] = make_pair(0, 0);
	while (!Q.empty()){
		int msk = Q.front(); Q.pop();
		int ne = best[msk].first, cw = best[msk].second;
		for (int i=0; i<n; ++i){
			if (!test(msk, i)){
				int nxt = (msk | (1 << i));
				pair<int,int> cur = make_pair(ne, cw + w[i]);
				if (cw + w[i] > maxw) cur = make_pair(ne+1, w[i]);
				if (cur < best[nxt]){
					best[nxt] = cur;
					bt[nxt] = msk;
				}
				if (!past[nxt]) Q.push(nxt);
				past[nxt] = true;
			}
		}
	}
	cout << best[(1 << n) - 1].first + 1 << '\n';
	int cur = (1 << n) - 1;
	vector<int> tmp;
	while (cur != 0){
		int k = cur^bt[cur];
		int p = 0;
		while (k > 0){
			k/=2;
			++p;
		}
		tmp.push_back(p);
		if (best[bt[cur]].first != best[cur].first){
			cout << tmp.size() << " ";
			for (int x : tmp){
				cout << x << " ";
			}
			cout << '\n';
			tmp.clear();
		}
		cur = bt[cur];
	}
	cout << tmp.size() << " ";
	for (int x : tmp){
		cout << x << " ";
	}
	cout << '\n';
	return 0;
}