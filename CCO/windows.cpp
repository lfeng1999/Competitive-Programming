#include <bits/stdc++.h>

using namespace std;

int nr, nc, n, id[100010], nid = 0;

struct Rect{
	int r1, c1, r2, c2, val;
} rs[100010];

struct Node2{
	int val = 0;
	Node2 *lef, *rig;	
};

struct Node1{
	Node2 *nxt;
	Node1 *lef, *rig;
};

void update2(Node2 *rt, int L, int R, int id){
	int UL = rs[id].c1, UR = rs[id].c2;
	if (rt->val != 0){
		if (!rt->lef) rt->lef = new Node2();
		if (!rt->rig) rt->rig = new Node2();
		rt->lef->val = rt->val;
		rt->rig->val = rt->val;
	}
	rt->val = 0;
	if (UL <= L && R <= UR){
		rt->val = rs[id].val;
		return;
	}
	if (UL <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node2();
		update2(rt->lef, L, (L+R)/2, id);
	}
	if ((L+R)/2+1 <= UR){
		if (!rt->rig) rt->rig = new Node2();
		update2(rt->rig, (L+R)/2+1,R, id);
	}
}
void update1(Node1 *rt, int L, int R, int id){
	int UL = rs[id].r1, UR = rs[id].r2;
	if (UL <= L && R <= UR){
		if (!rt->nxt) rt->nxt = new Node2();
		update2(rt->nxt, 1, nc, id);
		return;
	}
	if (UL <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node1();
		update1(rt->lef, L, (L+R)/2, id);
	}
	if ((L+R)/2+1 <= UR){
		if (!rt->rig) rt->rig = new Node1();
		update1(rt->rig, (L+R)/2+1, R, id);
	}
}

int query2(Node2 *rt, int L, int R, int p){
	if (rt->val) return rt->val;
	if (L == R) return 0;
	if (p <= (L+R)/2 && rt->lef) return query2(rt->lef, L, (L+R)/2, p);
	else if (p > (L+R)/2 && rt->rig) return query2(rt->rig, (L+R)/2+1, R, p);
	return 0;
}

int query1(Node1 *rt, int L, int R, int p1, int p2){
	int ret = 0;
	if (rt->nxt) ret = query2(rt->nxt, 1, nc, p2);
	if (L == R) return ret;
	if (p1 <= (L+R)/2 && rt->lef) ret = max(ret, query1(rt->lef, L, (L+R)/2, p1, p2));
	else if (p1 > (L+R)/2 && rt->rig) ret = max(ret, query1(rt->rig, (L+R)/2+1, R, p1, p2));
	return ret;
}

Node1 *root;

int main(){
	// freopen("test.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nc >> nr >> n;
	root = new Node1();
	for (int i=1; i<=n; ++i){
		id[i] = i; //val to rect id
		int r1, c1, r2, c2;
		cin >> c1 >> r1 >> c2 >> r2;
		if (r1 > r2) swap(r1, r2);
		if (c1 > c2) swap(c1, c2);
		rs[i] = {r1, c1, r2, c2, i};
		update1(root, 1, nr, i);
	}
	int nq;
	cin >> nq;
	int newval = n;
	for (int qq=0; qq<nq; ++qq){
		int r, c; cin >> c >> r;
		int rval = query1(root, 1, nr, r, c); //it finds rectangle
		cout << id[rval] << '\n';
		if (id[rval] == 0) continue;
		rs[id[rval]].val = ++newval;
		id[newval] = id[rval];
		update1(root, 1, nr, id[newval]);
	}

	return 0;
}