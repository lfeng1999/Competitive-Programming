#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
struct Node{
	Node *lef = nullptr, *rig = nullptr;
	int sum = 0;
};
Node *roots[200010];
Node* build_tree(int L, int R){
	Node *ret = new Node();
	if (L == R)
		return ret;
	int mid = (L+R)/2;
	ret->lef = build_tree(L, mid);
	ret->rig = build_tree(mid+1, R);
	return ret;
}

Node *update(Node *root, int L, int R, int p, int val){
	Node *ret = new Node();
	if (L == R){
		ret->sum = root->sum + val;
		return ret;
	}
	int mid = (L+R)/2;
	ret->lef = root->lef;
	ret->rig = root->rig;

	if (p <= mid){
		ret->lef = update(root->lef, L, mid, p, val);
	}
	else{
		ret->rig = update(root->rig, mid+1, R, p, val);
	}
	ret->sum = ret->lef->sum + ret->rig->sum;
	return ret;
}

int besty[3];

void query(Node *lef, Node *rig, int L, int R, int minval){
	if (L == R){
		besty[2] = rig->sum - lef->sum;
		for (int i=1; i>=0; --i){
			if (besty[i+1] > besty[i])
				swap(besty[i+1], besty[i]);
		}
		return;
	}
	int mid = (L+R)/2;
	int lsum = rig->lef->sum - lef->lef->sum, rsum = rig->rig->sum - lef->rig->sum;
	if (lsum >= minval)
		query(lef->lef, rig->lef, L, mid, minval);
	if (rsum >= minval)
		query(lef->rig, rig->rig, mid+1, R, minval);
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	roots[0] = build_tree(1, M);

	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		roots[i] = update(roots[i-1], 1, M, x, 1);
	}

	cin >> Q;
	for (int i=1; i<=Q; ++i){
		int L, R; cin >> L >> R;
		for (int j=0; j<4; ++j)
			besty[j] = 0;
		query(roots[L-1], roots[R], 1, M, (R - L)/3 + 1);
		double minval = (double)(R-L+1)/3;
		if ((double)besty[0] >= minval && (double)besty[1] >= minval){
			cout << "YES\n";
		}
		else if ((double)besty[0]/2.0 >= minval){
			cout << "YES\n";
		}
		else{
			cout << "NO\n";
		}
	}




	return 0;
}