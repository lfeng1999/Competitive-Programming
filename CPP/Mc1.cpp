#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30010, MAX_Q = 200010, MAX_VAL = 1000010;
int bit[MAX_N], N, ans[MAX_Q], nums[MAX_N];
vector<pair<pair<int,int>, int>> queries;

int pos[MAX_VAL];

int query(int i){
	int tot = 0;
	for (; i > 0; i -= i&(-i))
		tot += bit[i];
	return tot;
}
void update(int i, int val){
	for (; i < N + 10; i += i&(-i))
		bit[i] += val;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N;
	for (int i=1; i<=N; ++i)
	{
		cin >> nums[i];
	}
	int nQueries;
	cin >> nQueries;
	for (int i=0; i<nQueries; ++i)
	{
		int L, R; cin >> L >> R;
		queries.push_back(make_pair(make_pair(R, L), i));
	}
	sort(queries.begin(), queries.end());
	fill(pos, pos+MAX_VAL, -1);
	int idx = 1;
	for (int i=0; i<nQueries; ++i)
	{
		int R = queries[i].first.first, L = queries[i].first.second, query_i = queries[i].second;

		while (idx <= R)
		{
			if (pos[nums[idx]] != -1){
				update(pos[nums[idx]], -1);
			}
			update(idx, 1);
			pos[nums[idx]] = idx;
			idx++;
		}
		ans[query_i] = query(R) - query(L-1);
	}
	// for (int i=1;i<=N; ++i){
	// 	cout << query(i) << endl;
	// }
	// cout << endl;
	for (int i=0; i<nQueries; ++i){
		cout << ans[i] << '\n';
	}

	return 0;
}