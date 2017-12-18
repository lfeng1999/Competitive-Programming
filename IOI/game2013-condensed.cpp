#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

lint GCD(lint X, lint Y) {
    if (Y > X) swap(X, Y);
    lint tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

struct Node2{
	Node2 *lef, *rig;
	lint gcd = 0;
};

struct Node{
	Node2 *nxt;
	Node *lef, *rig;
};

lint nr, nc, nq;

lint query2(Node2 *rt, lint L, lint R, lint QL2, lint QR2){
	if (rt == nullptr || QR2 < L || R < QL2) return 0;
	if (QL2 <= L && R <= QR2) return rt->gcd;
	return GCD(query2(rt->lef, L, (L+R)/2, QL2, QR2), query2(rt->rig, (L+R)/2+1, R, QL2, QR2));
}

lint query1(Node *rt, lint L, lint R, lint QL, lint QR, lint QL2, lint QR2){
	if (rt == nullptr || R < QL || QR < L) return 0;
	if (QL <= L && R <= QR) return query2(rt->nxt, 0, nc-1, QL2, QR2);
	return GCD(query1(rt->lef, L, (L+R)/2, QL, QR, QL2, QR2), query1(rt->rig, (L+R)/2+1, R, QL, QR, QL2, QR2));
}
void update2(Node2 *rt, lint L, lint R, lint p2, lint val){
	if (L == R){
		rt->gcd = val;
		return;
	}
	if (p2 <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node2();
		update2(rt->lef, L, (L+R)/2, p2, val);
	}
	else{
		if (!rt->rig) rt->rig = new Node2();
		update2(rt->rig, (L+R)/2+1, R, p2, val);
	}
	rt->gcd = GCD(rt->lef?rt->lef->gcd:0, rt->rig?rt->rig->gcd:0);
}

void update1(Node *rt, lint L, lint R, lint p1, lint p2, lint val){
	
	if (!rt->nxt) rt->nxt = new Node2();

	if (L == R){
		update2(rt->nxt, 0, nc-1, p2, val);
		return;
	}
	if (p1 <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node();
		update1(rt->lef, L, (L+R)/2, p1, p2, val);
	}
	else{
		if (!rt->rig) rt->rig = new Node();
		update1(rt->rig, (L+R)/2+1, R, p1, p2, val);
	}
	update2(rt->nxt, 0, nc-1, p2, GCD(rt->lef?query2(rt->lef->nxt, 0, nc-1, p2, p2):0, rt->rig?query2(rt->rig->nxt, 0, nc-1, p2, p2):0));
}

Node *root;

int main(){
	// freopen("test.txt","r",stdin);
	// freopen("test2.txt","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nr >> nc >> nq;
	root = new Node();
	for (lint qq=0; qq<nq; ++qq){
		lint typ; cin >> typ;
		if (typ == 1){
			lint r, c; lint val;
			cin >> r >> c >> val;
			update1(root, 0, nr-1, r, c, val);
		}
		else{
			lint r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			cout << query1(root, 0, nr-1, r1, r2, c1, c2) << '\n';
		}
	}
	return 0;
}