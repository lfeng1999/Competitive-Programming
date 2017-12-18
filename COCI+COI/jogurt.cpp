#include <bits/stdc++.h>

using namespace std;

int n;
int tree[16][100010];


void copytree(int v1, int v2, int L, int R, int i){
	tree[i][v2] = 2*tree[i-1][v1];
	if (L == R) return;
	copytree(v1*2, v2*2, L, (L+R)/2, i);
	copytree(v1*2+1, v2*2+1, (L+R)/2+1, R, i);
}
void flood(int v, int L, int R, int i){
	tree[i][v]++;
	if (L == R) return;
	flood(v*2, L, (L+R)/2, i);
	flood(v*2+1, (L+R)/2+1, R, i);
}
void solve(int v, int L, int R, int i){
	cout << tree[i][v] << " ";
	if (L == R) return;
	solve(v*2, L, (L+R)/2, i);
	solve(v*2+1, (L+R)/2+1, R, i);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	tree[1][1] = 1;
	for (int i=2; i<16; ++i){
		tree[i][1] = 1;
		copytree(1, 2, 1, (1 << (i-2)), i);
		copytree(1, 3, 1, (1 << (i-2)), i);
		for (int j=(1 << (i - 2)); j<(1 << (i-1)); ++j){
			tree[i][j + (1 << (i-1))]++;
		}
		if (i-2 >= 1)
			flood(2, 1, (1 << (i-3)), i);
	}
	solve(1, 1, (1 << (n-1)), n);
	return 0;
}