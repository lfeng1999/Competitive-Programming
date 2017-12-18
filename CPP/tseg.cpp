#include <bits/stdc++.h>

using namespace std;

int N;
unordered_map<int,int> comp;

struct Node{
	int val = 0, lazy = 0;
} seg[525010];

void push_lazy(int v){
	seg[v].val += seg[v].lazy;
	if (v*2 < 525000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
}

void update(int v, int L, int R, int UL, int UR){
	push_lazy(v);
	if (UR < L || R < UL)
		return;
	if (UL <= L && R <= UR){
		seg[v].val++;
		if (v*2 < 525000){
			seg[v*2].lazy++;
			seg[v*2+1].lazy++;
		}
		return;
	}
	int mid = (L+R)/2;
	update(v*2, L, mid, UL, UR);
	update(v*2+1, mid+1, R, UL, UR);
	seg[v].val = max(seg[v*2].val, seg[v*2+1].val);
}

struct Line{
	int b, e;
} l[100010];


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int T;
	cin >> T;
	for (int qq = 1; qq<=T; ++qq){
		cin >> N;
		set<int> S;
		for (int i=1; i<=N; ++i){
			cin >> l[i].b >> l[i].e;
			S.insert(l[i].b);
			S.insert(l[i].e);
		}
		int cnt = 0;
		for (int x : S){
			comp[x] = ++cnt;
		}
		vector<pair<int,pair<int,int>>> V;
		// cur, type, other p (type -1 is add)
		for (int i=1; i<=N; ++i){
			l[i].b = comp[l[i].b];
			l[i].e = comp[l[i].e];
			V.push_back(make_pair(l[i].b, make_pair(-1, l[i].e)));
			V.push_back(make_pair(l[i].e, make_pair(1, l[i].b)));
		}
		sort(V.begin(), V.end());

		int cur = 0, ans = 0;
		for (int i = 0; i < V.size(); ++i){
			int b = V[i].first, e = V[i].second.second, t = V[i].second.first;
			if (t == 1)
				swap(b, e);
			if (t == -1){
				cur++;
				ans = max(ans, cur + seg[1].val);
			}
			else{
				cur--;
				update(1, 1, cnt, b, e);
			}
		}
		cout << "Case " << qq << ": " << ans << '\n';

		for (int i=0; i<525000; ++i){
			seg[i].val = seg[i].lazy = 0;
		}

		comp.clear();
	}
	return 0;
}