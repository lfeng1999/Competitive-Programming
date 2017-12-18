#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double ldouble;

const int SEGMAX = 2000010;
const int SEGMAX2 = 4000010;
int R, C;
int lef[SEGMAX];
int rig[SEGMAX];
int vcnt1 = 1;

lint seg2[SEGMAX2];
int lef2[SEGMAX2];
int rig2[SEGMAX2];
int vcnt2 = SEGMAX;

lint gcd(lint a, lint b){
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a%b);
}

void init(int _R, int _C){ R = _R, C = _C; }

void update2(int v, int L, int R, int c, lint val){
	if (L == R){ //This might be a column rectangle...
		seg2[v] = val;
		return;
	}
	int mid = (L+R)/2;
	if (c <= mid){
		if (lef2[v] == 0) lef2[v] = ++vcnt2;
		update2(lef2[v], L, mid, c, val);
	}
	else{
		if (rig2[v] == 0) rig2[v] = ++vcnt2;
		update2(rig2[v], mid+1, R, c, val);
	}
	seg2[v] = gcd(seg2[lef2[v]], seg2[rig2[v]]);
}

void update1(int v, int L, int R, int r, int c, lint val){
	update2(v, 0, C-1, c, val);
	if (L == R){
		return;
	}
	int mid = (L+R)/2;
	if (r <= mid){
		if (lef[v] == 0) lef[v] = ++vcnt1;
		update1(lef[v], L, mid, r, c, val);
	}
	else{
		if (rig[v] == 0) rig[v] = ++vcnt1;
		update1(rig[v], mid+1, R, r, c, val);
	}
}

lint ans = 0;
void update(int r, int c, lint val){
	update1(1, 0, R-1, r, c, val);
}

void query2(int v, int L, int R, int QL, int QR){
	if (QL <= L && R <= QR){
		ans = gcd(ans, seg2[v]);
		return;
	}
	int mid = (L+R)/2;
	if (QL <= mid){
		if (lef2[v] != 0)
			query2(lef2[v], L, mid, QL, QR);
	}
	if (mid+1 <= QR){
		if (rig2[v] != 0)
			query2(rig2[v], mid+1, R, QL, QR);
	}
	return;
}

void query1(int v, int L, int R, int QL, int QR, int QL2, int QR2){
	if (QL <= L && R <= QR){
		query2(v, 0, C-1, QL2, QR2);
		return;
	}
	int mid = (L+R)/2;
	if (QL <= mid){
		if (lef[v] != 0)
			query1(lef[v], L, mid, QL, QR, QL2, QR2);
	}
	if (mid+1 <= QR){
		if (rig[v] != 0);
			query1(rig[v], mid+1, R, QL, QR, QL2, QR2);
	}
	return;
}

lint calculate(int r1, int c1, int r2, int c2){
	ans = 0;
	query1(1, 0, R-1, r1, r2, c1, c2);
	return ans;
}


int main(){
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	int RR, CC, QQ;
	cin >> RR >> CC >> QQ;
	init(RR, CC);
	int qcnt = 0;
	for (int qq=0; qq<120; ++qq){
		int typ;
		cin >> typ;
		if (typ == 1){
			int r, c; lint val;
			cin >> r >> c >> val;
			update(r, c, val);
		}
		else{
			int r1, c1, r2, c2; 
			cin >> r1 >> c1 >> r2 >> c2;
			cout << calculate(r1, c1, r2, c2) << endl;
			qcnt++;
		}
	}


	return 0;
}