#include <bits/stdc++.h>
//Online Mountain Solution - better

using namespace std;

const int inf = 2e9;

struct Node{
	int L, R, maxh = 0, toth = 0, slope = 0, lazy = inf;
	Node *lef, *rig;
};
Node *makeNode(int L, int R){
	Node *ret = new Node(); ret->L = L; ret->R = R;
	return ret;
}

void push_lazy(Node *rt){
	if (!rt) return;
	if (rt->lazy == inf) return;
	int L = rt->L, R = rt->R;
	rt->toth = rt->maxh = rt->lazy*(R - L + 1);
	rt->slope = rt->lazy;
	if (L != R){
		if (!rt->lef) rt->lef = makeNode(L, (L+R)/2);
		if (!rt->rig) rt->rig = makeNode((L+R)/2+1, R);
		
		rt->lef->lazy = rt->lazy;
		rt->rig->lazy = rt->lazy;
	}

	rt->lazy = inf;
}

void update(Node *rt, int UL, int UR, int slope){
	int L = rt->L, R = rt->R;
	push_lazy(rt);
	if (UL <= L && R <= UR){
		rt->lazy = slope;
		return;
	}
	if (UL <= (L+R)/2){
		if (!rt->lef) rt->lef = makeNode(L, (L+R)/2);
		update(rt->lef, UL, UR, slope);
	}
	if ((L+R)/2+1 <= UR){
		if (!rt->rig) rt->rig = makeNode((L+R)/2+1, R);
		update(rt->rig, UL, UR, slope);
	}
	if (rt->lef) push_lazy(rt->lef);
	if (rt->rig) push_lazy(rt->rig);
	rt->toth = (rt->lef?rt->lef->toth:0) + (rt->rig?rt->rig->toth:0);
	rt->maxh = max(rt->lef?rt->lef->maxh:0, (rt->lef?rt->lef->toth:0) + (rt->rig?rt->rig->maxh:0));
}

int nodetot = 0;

Node* query(Node *rt, int val){ //find first node where it's value is greater or equal to val
	push_lazy(rt);
	int L = rt->L, R = rt->R;
	if (L == R){
		nodetot += rt->toth - val;
		return rt;
	}
	if (rt->lef) push_lazy(rt->lef);
	if (rt->rig) push_lazy(rt->rig);
	if (rt->lef && rt->lef->maxh >= val) return query(rt->lef, val);
	else return query(rt->rig, val - (rt->lef?rt->lef->toth:0));
}

int n;
Node *root;

int main(){
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	root = makeNode(0, n+1);
	while (true){
		char typ; cin >> typ;
		if (typ == 'E') break;
		else if (typ == 'I'){
			int l, r, dif; cin >> l >> r >> dif;
			update(root, l, r, dif);
		}
		else if (typ == 'Q'){
			int h; cin >> h;
			if (h >= root->maxh){
				cout << n << '\n';
			}
			else{
				nodetot = h + 1;
				Node *cur = query(root, h+1);
				int nd = (nodetot - h - 1)/cur->slope + 1;
				int ans = cur->L - nd;
				cout << ans << '\n';
			}
		}
	}
	return 0;
}