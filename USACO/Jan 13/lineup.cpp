#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	int seg[260010];
	void reset(){memset(seg, 0, sizeof(seg));}
	void update(int v, int L, int R, int p, int val){
		if (L == R) {seg[v] += val; return;}
		if (p <= (L+R)/2) update(v*2, L, (L+R)/2, p, val);
		else update(v*2+1, (L+R)/2+1, R, p, val);
		seg[v] = max(seg[v*2], seg[v*2+1]);
	}
}seg;

int n, k, b[100010];
unordered_map<int,int> comp;
int main(){
	// freopen("test.txt","r",stdin);
	freopen("lineup.in","r",stdin);
	freopen("lineup.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i=0; i<n; ++i){
		cin >> b[i]; comp[b[i]];
	}
	seg.reset();
	int m = 0;
	for (auto it = comp.begin(); it != comp.end(); ++it){it->second = ++m;}
	for (int i=0; i<n; ++i){b[i] = comp[b[i]];}
	unordered_map<int,int> cnt;
	set<pair<int,int>, greater<pair<int,int>>> best;
	int L = 0, R = 0, ans = 0;
	for (R = 0; R<n; ++R){
		cnt[b[R]]++;
		seg.update(1, 1, m, b[R], 1);
		//best.find(make_pair(cnt[b[R]], b[R]))
		while (cnt.size() > k+1){
			cnt[b[L]]--;
			seg.update(1, 1, m, b[L], -1);
			if (cnt[b[L]] == 0) cnt.erase(b[L]); //best.erase(make_pair(cnt[b[L]], b[L]));
			++L;
		}
		ans = max(ans, seg.seg[1]);
		// ans = max(ans, (*best.begin()).first);

		//or u can do in linear time. ans = max(ans, cnt[b[R]]);
	}
	cout << ans;
	return 0;
}