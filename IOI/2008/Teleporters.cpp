#include <bits/stdc++.h>

using namespace std;

int to[2000010];
int N, M, path_length = 0, cyc_length[1000010], nCycle = 0;
pair<int,int> teleporters[2000010];
int compress[2000010];

bool past[2000010], to_comp[2000010];

int main()
{
	// freopen("IOI.in","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;

	for (int i=0; i<N; ++i){
		int L, R;
		cin >> L >> R;
		teleporters[i] = make_pair(L, R);
		to_comp[L] = to_comp[R] = true;
	}
	int cnt = 0;
	compress[0] = cnt++;
	for (int i=1; i< 2000010; ++i){
        if (to_comp[i])
            compress[i] = cnt++;
	}
	for (int i=0; i<N; ++i){
		int v = compress[teleporters[i].first] - 1, u = compress[teleporters[i].second];
		to[v] = u;
		v = compress[teleporters[i].second] - 1, u = compress[teleporters[i].first];
		to[v] = u;
	}

	N = cnt - 1;


	int v = 0;
	while (v != N){
		past[v] = true;
		path_length++;
		v = to[v];
	}

	for (int i=1; i<N; ++i){
		v = i;
		if (past[v]) continue;

		while (!past[v]){
			past[v] = true;
			cyc_length[nCycle]++;
			v = to[v];
		}

		nCycle++;
	}
	sort(cyc_length, cyc_length + nCycle);
	reverse(cyc_length, cyc_length + nCycle);

	for (int i=0; i<nCycle && M; ++i){
		path_length += 2 + cyc_length[i];
		M--;
	}

	path_length += 4 * (int)(M/2);
	if (M&1) path_length++;

	cout << path_length;


}
