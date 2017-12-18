#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
int bsize, cur[100010], a[100010], ans[100010], N, Q;
pair<pii, int> q[100010];
bool cmp(const pair<pii, int> a, const pair<pii, int> b){
	if (a.first.first/bsize < b.first.first/bsize)
		return true;
	if (b.first.first/bsize < a.first.first/bsize)
		return false;
	return a.first.second < b.first.second;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	bsize = sqrt(N);
	for (int i=1; i<=N; ++i){
		cin >> a[i];
	}
	cin >> Q;
	for (int i=0; i<Q; ++i){
		cin >> q[i].first.first >> q[i].first.second;
		q[i].second = i;
	}
	sort(q, q + Q, cmp);
	int L = 1, R = 1, curans = 0;
	cur[a[1]]++;
	for (int i=0; i<Q; ++i){
		int lef = q[i].first.first, rig = q[i].first.second, p = q[i].second;
		// cout << lef << " " << rig << endl;
		while (R < rig){
			++R;
			cur[a[R]]++;
			if (cur[a[R]] % 2 == 1 && cur[a[R]] != 1)
				curans--;
			if (cur[a[R]] % 2 == 0)
				curans++;
		}
		while (lef < L){
			--L;
			cur[a[L]]++;
			if (cur[a[L]] % 2 == 1 && cur[a[L]] != 1)
				curans--;
			if (cur[a[L]] % 2 == 0)
				curans++;
		}
		while (L < lef){
			cur[a[L]]--;
			if (cur[a[L]] % 2 == 1)
				curans--;
			if (cur[a[L]] % 2 == 0 && cur[a[L]] != 0)
				curans++;
			++L;
		}
		while (rig < R){
			cur[a[R]]--;
			if (cur[a[R]] % 2 == 1)
				curans--;
			if (cur[a[R]] % 2 == 0 && cur[a[R]] != 0)
				curans++;
			--R;
		}
		ans[p] = curans;
	}
	for (int i=0; i<Q; ++i){
		cout << ans[i] << "\n";
	}

	return 0;
}