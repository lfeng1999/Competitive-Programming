#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010;
int N, bit[MAX_N], nQueries;

void update(int i, int val){
	for (; i < MAX_N; i += i&(-i))
		bit[i] += val;
}

int query(int i){
	int tot = 0;

	for (; i > 0; i -= i&(-i))
		tot += bit[i];

	return tot;
}
map<int,int> ANSWER;

int trees[MAX_N], answers[MAX_N];

typedef pair<int,int> pii;
priority_queue<pii, vector<pii>, greater<pii> > Q;

struct Query{
	int i, a, b, q;
	bool operator < (const Query &a){
		return q < a.q;
	}

} queries[MAX_N];

int main(){
	// freopen("test.txt","r",stdin);

	cin >> N;

	int tot_mass = 0;
	for (int i=1; i<=N; ++i){
		cin >> trees[i];
		Q.push(make_pair(trees[i], i));
		update(i, trees[i]);
	}
	cin >> nQueries;

	for (int i=0; i<nQueries; ++i){
		cin >> queries[i].a >> queries[i].b >> queries[i].q;
		queries[i].a += 1;
		queries[i].b += 1;
		queries[i].i = i;
	}
	sort(queries, queries + nQueries);
	printf("\n");
	for (int i=0; i<nQueries; ++i){
		int min_mass = queries[i].q;

		while (!Q.empty() && Q.top().first < min_mass){
			update(Q.top().second, -Q.top().first);
			Q.pop();
		}
		answers[queries[i].i] = query(queries[i].b) - query(queries[i].a - 1);
	}
	for (int i=0; i<nQueries; ++i){
		cout << answers[i] << '\n';
	}


	return 0;
}