#include <bits/stdc++.h>

using namespace std;

struct Student{
	int A, B;
	int id, sorted_id;
} stu[200010];
struct Update{
	int stu_id, type;
} U[200010];

bool sortsmart(const Student &a, const Student &b){
	if (a.A != b.A)
		return a.A < b.A;
	return a.B < b.B;
}
bool sortid(const Student &a, const Student &b){
	return a.id < b.id;
}

int vmax[600010], cnt[600010], revsort_id[200010];
int upd[200010][3], N, pos[200010], revpos[600010];

void build_tree(int v, int L, int R){
	if (L == R){
		pos[L] = v;
		revpos[v] = L;
		return;
	}
	int mid = (L+R)/2;
	build_tree(v*2, L, mid);
	build_tree(v*2+1, mid+1, R);
}
void update(int p, int val){
	p = pos[p];
	vmax[p] = val;
	p/=2;
	while (p != 0){
		vmax[p] = max(vmax[p*2], vmax[p*2+1]);
		p/=2;
	}
}

int query(int v, int L, int R, int p, int val){
	if (R < p)
		return -1;
	if (vmax[v] < val)
		return -1;
	if (L == R)
		return revpos[v];
	int mid = (L+R)/2;
	int ret = query(v*2, L, mid, p, val);
	if (ret != -1)
		return ret;
	return query(v*2+1, mid+1, R, p, val);
}

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	int scnt = 0;
	for (int i=1; i<=N; ++i){
		char ch;
		cin >> ch;
		if (ch == 'D'){
			scnt++;
			U[i].type = 1;
			U[i].stu_id = scnt;
			stu[scnt].id = scnt;
			cin >> stu[scnt].A >> stu[scnt].B;
			swap(stu[scnt].A, stu[scnt].B);
		}
		else{
			U[i].type = 2;
			cin >> U[i].stu_id;
		}
	}
	build_tree(1, 1, scnt);
	sort(stu+1, stu+1+scnt, sortsmart);
	for (int i=1; i<=scnt; ++i){
		stu[i].sorted_id = i;
		revsort_id[i] = stu[i].id;
	}
	sort(stu+1, stu+1+scnt, sortid);

	for (int i=1; i<=N; ++i){
		if (U[i].type == 1){
			update(stu[U[i].stu_id].sorted_id, stu[U[i].stu_id].B);
		}
		else{
			int x = query(1, 1, scnt, stu[U[i].stu_id].sorted_id + 1, stu[U[i].stu_id].B);

			if (x != -1)
				cout << revsort_id[x] << '\n';
			else{
				cout << "NE\n";
			}
		}
	}

	return 0;
}