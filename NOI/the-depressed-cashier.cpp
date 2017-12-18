#include <bits/stdc++.h>

using namespace std;
#define debug(x) cout << '>' << #x << " : " << x << endl
struct SegmentTree{
	int on[270010];
	bool lazy[270010];
	void push_lazy(int v){
		if (!lazy[v]) return;
		on[v] = 0;
		if (v*2 < 270000){
			lazy[v*2] = lazy[v*2+1] = true;
		}
		lazy[v] = false;
	}
	void turnon(int v, int L, int R, int p){
		push_lazy(v);
		if (L == R){
			on[v]++;
			return;
		}
		if (p <= (L+R)/2) turnon(v*2, L, (L+R)/2, p);
		else turnon(v*2+1, (L+R)/2+1, R, p);
		push_lazy(v*2); push_lazy(v*2+1);
		on[v] = on[v*2] + on[v*2+1];
	}
	void turnoff(int v, int L, int R, int UL, int UR){
		push_lazy(v);
		if (UL <= L && R <= UR){
			lazy[v] = true;
			push_lazy(v);
			return;
		}
		if (UL <= (L+R)/2) turnoff(v*2, L, (L+R)/2, UL, UR);
		if ((L+R)/2+1 <= UR) turnoff(v*2+1, (L+R)/2+1, R, UL, UR);
		push_lazy(v*2); push_lazy(v*2+1);
		on[v] = on[v*2] + on[v*2+1];
	}
	int query(int v, int L, int R, int amt){
		push_lazy(v);
		if (L == R) return L;
		push_lazy(v*2); push_lazy(v*2+1);
		if (amt <= on[v*2+1]) return query(v*2+1, (L+R)/2+1, R, amt);
		else return query(v*2, L, (L+R)/2, amt - on[v*2+1]);
	}
	void display(int v, int L, int R){
		push_lazy(v);
		if (L == R){
			cout << L << " : " << on[v] << endl;
			return;
		}
		display(v*2, L, (L+R)/2);
		display(v*2+1, (L+R)/2+1, R);
	}
}seg;

int qs[250010][2], n, nq, minwage;
map<int,int> comp, decomp;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nq >> minwage;
	int shift = 0;
	n = 0;
	vector<int> xs;
	int totemp = 0;
	for (int i=0; i<nq; ++i){
		char cmd; int x; cin >> cmd >> x;
		if (cmd == 'I'){
			xs.push_back(x-shift);
			totemp++;
			qs[i][0] = 0;
		}
		else if (cmd  == 'A'){
			shift += x;
			qs[i][0] = 1;
		}
		else if (cmd == 'S'){
			shift -= x;
			qs[i][0] = 2;
		}
		else if (cmd == 'F'){
			qs[i][0] = 3;
		}
		qs[i][1] = x;
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	for (auto x : xs){
		comp[x] = n;
		decomp[n] = x;
		++n;
	}
	shift = 0;
	int nleft = 0;
	for (int i=0; i<nq; ++i){
		int typ  = qs[i][0], x = qs[i][1];
		if (typ == 0){
			if (x < minwage) continue;
			seg.turnon(1, 0, n-1, comp[x - shift]);
		}
		else if (typ == 1){
			shift += x;
		}
		else if (typ == 2){
			shift -= x;
		}
		else if (typ == 3){
			if (x > seg.on[1]){
				cout << -1 << '\n';
			}
			else{
				int id = seg.query(1, 0, n-1, x);				
				int wage = decomp[id]+shift;
				cout << wage << '\n';
			}
		}
		if (typ < 3){
			int mwage = minwage - 1 - shift;
			int idx = upper_bound(xs.begin(), xs.end(), mwage) - xs.begin() - 1;
			int lol = seg.on[1];
			if (idx < 0) continue;
			seg.turnoff(1, 0, n-1, 0, idx);
			lol -= seg.on[1];
			nleft += lol;
		}
	}
	cout << nleft << '\n';

	return 0;
}