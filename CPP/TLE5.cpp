#include <bits/stdc++.h>

using namespace std;

struct Node{
	int sz = 0;
	double val = 0;
} seg[800010];
double r;
int N;
int p[200010], segpos[100010], curpos[100010];
double vals[200010], curval[200010], myexp[200010];
map<int,int> M;
vector<pair<int, pair<int, double>>> updates;

void update(int v, int L, int R, int p, double val){

	if (L == R){
		seg[v].val += val;
		if (val > 0)
			seg[v].sz++;
		else
			seg[v].sz--;
		return;
	}
	int mid = (L+R)/2;

	if (p <= mid)
		update(v*2, L, mid, p, val);
	else
		update(v*2+1, mid+1, R, p, val);
	seg[v].val = seg[v*2].val + seg[v*2+1].val * myexp[seg[v*2].sz];
	seg[v].sz = seg[v*2].sz + seg[v*2+1].sz;
}

bool msort(pair<int, pair<int, double>> &a, pair<int, pair<int, double>> &b){
	return a.second.second > b.second.second;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> r >> N;
	fill(segpos, segpos + 100010, -1);
	fill(curpos, curpos + 100010, -1);
	for (int i=0; i<N; ++i){
		cin >> p[i] >> vals[i];
		updates.push_back(make_pair(i, make_pair(p[i], vals[i])));
	}
	myexp[0] = 1;
	for (int i=1; i<=N; ++i){
		myexp[i] = myexp[i-1]*r;
	}
	sort(updates.begin(), updates.end(), msort);
	for (int i=0; i<updates.size(); ++i){
		segpos[updates[i].first] = i+1;
	}
	sort(updates.begin(), updates.end());
	for (int i=0; i<N; ++i){
		int p = segpos[updates[i].first], pid = updates[i].second.first;
		double val = updates[i].second.second;
		if (val > curval[pid]){
			if (curpos[pid] != -1)
				update(1, 1, N, curpos[pid], -curval[pid]);
			update(1, 1, N, p, val);

			curpos[pid] = p;
			curval[pid] = val;
		}
		printf("%.9f\n", seg[1].val);
	}
	return 0;
}