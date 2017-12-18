#include <bits/stdc++.h>

using namespace std;

struct Node{
	int cnt = 0;
	Node *lef, *rig;
};

Node *root;
int getcnt(Node *v){return v?v->cnt:0;}

void update(Node *rt, int L, int R, int val, int uval){
	if (L == R){
		rt->cnt = max(0, rt->cnt + uval);
		return;
	}
	if (val <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node();
		update(rt->lef, L, (L+R)/2, val, uval);
	}
	else{
		if (!rt->rig) rt->rig = new Node();
		update(rt->rig, (L+R)/2+1, R, val, uval);
	}
	rt->cnt = getcnt(rt->lef) + getcnt(rt->rig);
}

int getidx(Node *rt, int L, int R, int val){
	if (!rt) return -1e9;
	if (L == R){
		return rt->cnt?1:-1e9;
	}
	if (val <= (L+R)/2){
		return getidx(rt->lef, L, (L+R)/2, val);
	}
	else{
		return getcnt(rt->lef) + getidx(rt->rig, (L+R)/2+1, R, val);
	}
}

int getvth(Node *rt, int L, int R, int cnt){
	if (L == R) return L;
	if (getcnt(rt->lef) >= cnt){
		return getvth(rt->lef, L, (L+R)/2, cnt);
	}
	else{
		return getvth(rt->rig, (L+R)/2+1, R, cnt - getcnt(rt->lef));
	}
}

void expand(Node *rt, int L, int R){
	if (!rt || rt->cnt == 0) return;
	if (L == R){
		for (int qq=0; qq<rt->cnt; ++qq){
			cout << L << " ";
		}
		return;
	}
	expand(rt->lef, L, (L+R)/2);
	expand(rt->rig, (L+R)/2+1, R);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	root = new Node();
	int n, nq; cin >> n >> nq;
	for (int qq=0; qq<n; ++qq){
		int x; cin >> x;
		update(root, 1, 1e9, x, 1);
	}
	int prev = 0;
	for (int qq=0; qq<nq; ++qq){
		char cmd; cin >> cmd;
		int x; cin >> x;
		x ^= prev;
		if (cmd == 'I'){
			update(root, 1, 1e9, x, 1);
		}
		else if (cmd == 'R'){
			update(root, 1, 1e9, x, -1);
		}
		else if (cmd == 'S'){
			int ans = getvth(root, 1, 1e9, x);
			prev = ans;
			cout << ans << '\n';
		}
		else if (cmd == 'L'){
			int ans = getidx(root, 1, 1e9, x);
			if (ans < 0) ans = -1;
			prev = ans;
			cout << ans << '\n';
		}
	}
	expand(root, 1, 1e9);

	return 0;
}