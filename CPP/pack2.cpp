#include <bits/stdc++.h>

using namespace std;

vector<int> col[10010], row[10010];
int R, C, N;
set<pair<int,int>> S;

int graph[1010][1010], graph2[1010][1010];

struct Node{
	int sum = 0, lazy = 0;
} seg[600010];

void push_lazy(int v, int L, int R){
	// seg[v].sum += seg[v].lazy*(R-L+1);
	seg[v].sum += seg[v].lazy*(L+R)*(R-L+1)/2;
	if (v*2 < 600000){
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
	}
	seg[v].lazy = 0;
}

int query(int v, int L, int R, int p){
	push_lazy(v, L, R);
	if (R <= p){
		return seg[v].sum;
	}
	int mid = (L+R)/2;
	int ret = query(v*2, L, mid, p);
	if (mid+1 <= p)
		ret += query(v*2+1, mid+1, R, p);
	return ret;
}

void update(int v, int L, int R, int p, int val){
	push_lazy(v, L, R);
	if (R <= p){
		// seg[v].sum += (R-L+1)*val;
		seg[v].sum += (L+R)*(R-L+1)*val/2;
		if (v*2 < 600000){
			seg[v*2].lazy += val;
			seg[v*2+1].lazy += val;
		}
		return;
	}
	int mid = (L+R)/2;
	update(v*2, L, mid, p, val);
	if (mid+1 <= p)
		update(v*2+1, mid+1, R, p, val);
	push_lazy(v*2, L, mid);
	push_lazy(v*2+1, mid+1, R);
	seg[v].sum = seg[v*2].sum + seg[v*2+1].sum;
}





int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> R >> C;
	cin >> N;
	// cout << R << " " << C << " " << N << endl;
	for (int i=1;i<1010; ++i)
		fill(graph[i], graph[i] + 1010, 1);
	for (int i=0; i<N; ++i){
		int r, c; cin >> r >> c;
		// cout << r << " " << c << endl;
		graph[r][c] = 0;
		row[r].push_back(c);
		col[c].push_back(r);
		S.insert(make_pair(r, c));
	}
	for (int i=1; i<=R; ++i){
		row[i].push_back(0);
		row[i].push_back(C+1);
		sort(row[i].begin(), row[i].end());
	}
	for (int i=1; i<=C; ++i){
		col[i].push_back(0);
		col[i].push_back(R+1);
		sort(col[i].begin(), col[i].end());
	}

	vector<int> V;
	int ans = 0;

	for (int j=1; j<=C; ++j){
		V.clear();
		for (int i=1; i<=R; ++i){
			if (S.count(make_pair(i, j))){
				V.push_back(0);
				continue;
			}
			int p = upper_bound(row[i].begin(), row[i].end(), j) - row[i].begin();
			V.push_back(min(row[i][p] - j, j - row[i][p-1]));
			// graph2[i][j] = min(row[i][p] - j, j - row[i][p-1]);
		}
		V.push_back(0);
		int beg = 0, ed = 0;
		for (int i=0; i<=R; ++i){
			if (V[i] == 0){
				ed = i-1;
				if (ed - beg >= 4){
					//I CAN DO SHITT
					// cout << j << " " << beg << " " << ed << endl;
					// cout << V[1]-1 << endl;

					for (int k=beg+3; k<=ed-1; ++k){
						if (V[k-2] != 1)
							update(1, 1, C/2 + 1, V[k-2]-1, k - beg - 3 + 1);
						if (V[k] >= 3){
							ans += query(1, 1, C/2+1, V[k]-2)*(ed-k);
							// cout << V[k] - 2 << " " << ed-k << " " << query(1, 1, C/2+1, V[k]-2)*(ed-k) << endl;
						}
					}
					for (int k=beg+3; k<=ed-1; ++k){
						if (V[k-2] != 1)
							update(1, 1, C/2 + 1, V[k-2]-1, (k - beg - 3 + 1)*(-1));
					}


					// cout << ans << endl;




				}
				beg = i+1;
			}
		}
	}
	cout << ans;
	// update(1, 1, R, 3, 2);
	// update(1, 1, R, 5, 1);
	// for (int i=1; i<=R; ++i){
	// 	cout << query(1, 1, R, i) << endl;
	// }






	for (int i=1; i<=R; ++i){
		for (int j=1; j<=C; ++j){
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	// cout << endl;
	// for (int i=1; i<=R; ++i){
	// 	for (int j=1; j<=C; ++j){
	// 		cout << graph2[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;


	return 0;
}