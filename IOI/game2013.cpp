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
	if (QL2 <= L && R <= QR2) return rt->gcd;
	lint ret = 0;
	if (QL2 <= (L+R)/2 && rt->lef){
		ret = GCD(ret, query2(rt->lef, L, (L+R)/2, QL2, QR2));
	}
	if ((L+R)/2+1 <= QR2 && rt->rig){
		ret = GCD(ret, query2(rt->rig, (L+R)/2+1, R, QL2, QR2));
	}
	return ret;
}

lint query1(Node *rt, lint L, lint R, lint QL, lint QR, lint QL2, lint QR2){
	if (QL <= L && R <= QR){
		if (rt->nxt) return query2(rt->nxt, 0, nc-1, QL2, QR2);
		return 0;
	}
	lint ret = 0;
	if (QL <= (L+R)/2 && rt->lef){
		ret = GCD(ret, query1(rt->lef, L, (L+R)/2, QL, QR, QL2, QR2));
	}
	if ((L+R)/2+1 <= QR && rt->rig){
		ret = GCD(ret, query1(rt->rig, (L+R)/2+1, R, QL, QR, QL2, QR2));
	}
	return ret;
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
	lint newgcd = 0;
	if (rt->lef) newgcd = GCD(newgcd, rt->lef->gcd);
	if (rt->rig) newgcd = GCD(newgcd, rt->rig->gcd);
	rt->gcd = newgcd;
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
	lint newgcd = 0;
	if (rt->lef){
		newgcd = GCD(newgcd, query2(rt->lef->nxt, 0, nc-1, p2, p2));
	}
	if (rt->rig){
		newgcd = GCD(newgcd, query2(rt->rig->nxt, 0, nc-1, p2, p2));
	}
	update2(rt->nxt, 0, nc-1, p2, newgcd);
}


Node *root;

void init(int a, int b){
	nr = a, nc = b;
	root = new Node();
}
void update(int r, int c, lint val){
	update1(root, 0, nr-1, r, c, val);
}
lint calculate(int r1, int c1, int r2, int c2){
	return query1(root, 0, nr-1, r1, r2, c1, c2);
}
