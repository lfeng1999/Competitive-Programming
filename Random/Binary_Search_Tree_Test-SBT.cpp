#include <bits/stdc++.h>

using namespace std;

struct node{
	node *left, *right;
	int size, value;
	node(int x) : size(1), value(x), left(0), right(0) {}
} *root;

int size(node *rt){
	return rt?rt->size:0;
}

void resize(node *&rt){
	if (!rt) return;
	rt->size = size(rt->left) + size(rt->right) + 1;
}

void rotate_right(node *&rt){
	node *tmp = rt->left;
	rt->left = tmp->right;
	tmp->right = rt;
	rt = tmp;
	resize(rt->right);
	resize(rt);
}

void rotate_left(node *&rt){
	node *tmp = rt->right;
	rt->right = tmp->left;
	tmp->left = rt;
	rt = tmp;
	resize(rt->left);
	resize(rt);
}

void maintain(node *&rt){
	if (!rt) return;
	bool updated = false;
	if (rt->right){
		if (size(rt->right->left) > size(rt->left)){
			rotate_right(rt->right);
			rotate_left(rt);
			updated = true;
		}
		else if (size(rt->right->right) > size(rt->left)){
			rotate_left(rt);
			updated = true;
		}
	}
	if (rt->left){
		if (size(rt->left->left) > size(rt->right)){
			rotate_right(rt);
			updated = true;
		}
		else if (size(rt->left->right) > size(rt->right)){
			rotate_left(rt->left);
			rotate_right(rt);
			updated = true;
		}
	}
	if (updated){
		maintain(rt->left); maintain(rt->right); 
		maintain(rt);
	}
}

void insert(node *&rt, int x){
	if (!rt){
		rt = new node(x);
		return;
	}
	if (x < rt->value){
		insert(rt->left, x);
	}
	else{
		insert(rt->right, x);
	}
	resize(rt);
	maintain(rt);
}

void erase(node *&rt, int x){
	if (!rt) return;
	if (rt->value == x){
		if (!rt->left || !rt->right){
			node *nxt;
			if (rt->left) nxt = rt->left;
			else nxt = rt->right;
			delete rt;
			rt = nxt;
		}
		else{
			node *nxt = rt->right;
			while (nxt->left) nxt = nxt->left;
			rt->value = nxt->value;
			erase(rt->right, rt->value);
		}
	}
	else if (rt->value < x){
		erase(rt->right, x);
	}
	else if (rt->value > x){
		erase(rt->left, x);
	}
	resize(rt);
}

int getkth(node *&rt, int k){
	if (size(rt->left) >= k){
		return getkth(rt->left, k);
	}
	else if (size(rt->left) + 1 == k){
		return rt->value;
	}
	else{
		return getkth(rt->right, k - size(rt->left) - 1);
	}
}

int ans = 1e9;
void find(node *&rt, int x, int distl){
	if (!rt) return;
	if (rt->value == x){
		ans = min(ans, distl + size(rt->left) + 1);
	}
	if (rt->value < x){
		find(rt->right, x, distl + size(rt->left) + 1);
	}
	else if (rt->value >= x){
		find(rt->left, x, distl);
	}
}
int getidx(int x){
	ans = 1e9;
	find(root, x, 0);
	int ret = ans;
	if (ans == 1e9) ret = -1;
	return ret;
}

void display(node *rt){
	if (!rt) return;
	display(rt->left);
	cout << rt->value << " ";
	display(rt->right);
}
int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int n, nq; cin >> n >> nq;
	for (int i=0; i<n; ++i){
		int x; cin >> x;
		insert(root, x);
	}
	int prev = 0;
	for (int i=0; i<nq; ++i){
		char cmd; int x;
		cin >> cmd >> x;
		x ^= prev;
		if (cmd == 'I'){
			insert(root, x);
		}
		else if (cmd == 'R'){
			erase(root, x);
		}
		else if (cmd == 'S'){
			prev = getkth(root, x);
			cout << prev << '\n';
		}
		else if (cmd == 'L'){
			prev = getidx(x);
			cout << prev << '\n';
		}
	}
	display(root);
	return 0;
}