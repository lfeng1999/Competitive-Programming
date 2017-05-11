#include <bits/stdc++.h>

using namespace std;

int n, fr[510];

int cur[510], diff[510], seg[1050], lazy[1050];

void build_tree(int v, int L, int R){
	if (L == R) {seg[v] = cur[L]; return;}
	build_tree(v*2, L, (L+R)/2); build_tree(v*2+1, (L+R)/2+1, R);
}
void push_lazy(int v){
	seg[v] += lazy[v];
	if (v*2 < 1050){lazy[v*2] += lazy[v]; lazy[v*2+1] += lazy[v];}
	lazy[v] = 0;
}
int query(int v, int L, int R, int p){
	push_lazy(v);
	if (L == R) return seg[v];
	if (p <= (L+R)/2) return query(v*2, L, (L+R)/2, p);
	else return query(v*2+1, (L+R)/2+1, R, p);
}
void update(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (UR < L || R < UL) return;
	if (UL <= L && R <= UR){lazy[v] += val; push_lazy(v); return;}
	update(v*2, L, (L+R)/2, UL, UR, val);
	update(v*2+1, (L+R)/2+1, R, UL, UR, val);
}

bool valid(int x){
	memset(seg, 0, sizeof(seg)); memset(lazy, 0, sizeof(lazy));
	set<int> S;
	int k = 0;
	for (int i=1; i<=n+1; ++i){
		if (i == x) continue;
		cur[++k] = fr[i];
	}
	sort(cur+1, cur+1+n);
	for (int i=1; i<=n; ++i){
		diff[i] = cur[i] - cur[i-1];
		// cout << cur[i] << endl;
		if (diff[i]){
			S.insert(i);
		}
	}
	build_tree(1, 0, n);
	for (int i=n; i>=1; --i){ 
		if (S.count(i)) S.erase(i);
		int cval = query(1, 0, n, i);
		int ocval = cval;
		if (cval > i-1) return false;
		auto it = S.lower_bound(i-1-cval+1);
		int pos = i;
		if (it != S.end()){
			pos = *it;
			update(1, 0, n, pos, i-1, -1);
			cval -= (i - 1 - pos + 1);
			if (query(1, 0, n, pos) == query(1, 0, n, pos-1)){
				S.erase(pos);
			}
		}
		if (cval == 0) continue;
		it = S.lower_bound(pos);
		if (it == S.begin()){
			return false; 	
		}
		--it;
		pos = *it;
		update(1, 0, n, pos, pos + cval - 1, -1);
		if (query(1, 0, n, pos) == query(1, 0, n, pos-1)) S.erase(pos);
		S.insert(pos+cval);
	}
	return query(1, 0, n, 1) == 0;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("fcount.in","r",stdin);
	freopen("fcount.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int tot = 0;
	for (int i=1; i<=n+1; ++i){
		cin >> fr[i]; tot += fr[i];
	}
	vector<int> ans;
	for (int i=1; i<=n+1; ++i){
		if ((tot - fr[i])%2 == 0 && valid(i)) ans.push_back(i);
	}
	cout << ans.size() << '\n';
	for (int x : ans){
		cout << x << '\n';
	}
	return 0;
}