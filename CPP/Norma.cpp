#include <bits/stdc++.h>

using namespace std;

struct Node{
	int smin = 0, smax = 0, sl = 0, lazymax = 1e9, lazymin = -1e9, lazyl = 0;
	int smaxmin = 0, smaxl = 0, sminl = 0, smaxminl = 0;
	int L, R;
	int vmax=1e9, vmin=-1e9;
	Node *lef = nullptr, Node * rig = nullptr;

	void build_tree(int _L, int _R){
		L = _L, R = _R;
		if (L == R)
			return;
		int mid = (L+R)/2;
		lef = new Node();
		rig = new Node();
		lef->build_tree(L, mid);
		rig->build_tree(mid+1, R);
	}

	void push_max(){
		if (lazymax == 0)
			return;
		smax = lazymax*(R-L+1);
		smaxmin = lazymax*smin;
		smaxl = lazymax*sl;
		smaxminl = lazymax*sminl;
		vmax = lazymax;

		lazymax = 0;
	}

	void push_min(){
		if (lazymin == 1e9)
			return;
		smin = lazymin*(R-L+1);
		smaxmin = lazymin*smax;
		sminl = lazymin*sl;
		smaxminl = lazymin*smaxl;
		vmin = lazymin;

		lazymin = 1e9;
	}

	void push_l(){
		if (lazyl == 0)
			return;
		sl = sl + (R-L+1)*lazyl;
		smaxl = smaxl + smax*lazyl;
		sminl = sminl + smin*lazyl;
		smaxminl = smaxminl + smaxmin*lazyl;

		lazyl = 0;
	}

	void push_lazy(){
		push_max();
		push_min();
		push_l();
	}

	void updatep(){
		smaxminl = lef->smaxminl + rig->smaxminl;
		smaxl = lef->smaxl + rig->smaxl;
		sminl = lef->sminl + rig->sminl;
		smaxmin = lef->smaxmin + rig->smaxmin;
		smax = lef->smax + rig->smax;
		smin = lef->smin + rig->smin;
		sl = lef->sl + rig->sl;

		vmax = min(lef->vmax, rig->vmax);
		vmin = max(lef->vmin, rig->vmin);
	}

	void updatemin(int UL, int UR, int val){
		push_lazy();
		if (R < UL || UR < L)
			return;
		if (UL <= L && R <= UR){
			lazymin = val;
			push_lazy();
			return;
		}
		lef->updatemin(UL, UR, val);
		rig->updatemin(UL, UR, val);
		updatep();
	}
	void updatemax(int UL, int UR, int val){
		push_lazy();
		if (R < UL || UR < L)
			return;
		if (UL <= L && R <= UR){
			lazymax = val;
			return;
		}
		lef->updatemax(UL, UR, val);
		rig->updatemax(UL, UR, val);
		updatep();
	}
	void updateL(int UL, int UR, int val){
		push_lazy();
		if (R < UL || UR < L)
			return;
		if (UL <= L && R <= UR){
			lazyl += val;
			return;
		}
		lef->updateL(UL, UR, val);
		rig->updateL(UL, UR, val);
		updatep();
	}
	int queryminp(int val){
		if (L == R)
			return L;
		if (rig->vmin >= val)
			return rig->queryminp(val);
		else
			return lef->queryminp(val);
	}
	int querymaxp(int val){

	}
};



int N;




int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	Node *root = new Node();


	return 0;
}