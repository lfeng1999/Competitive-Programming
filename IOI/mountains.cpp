#include <bits/stdc++.h>

using namespace std;

typedef pair<pair<int,int>, int> ppiii;

struct Node{
	Node *lef, *rig;
	int val = 0, lazy = 0;
};

int n;
Node *root;

void push_lazy(Node *rt){
	if (!rt->lazy) return;
	rt->val += rt->lazy;
	if (!rt->lef) rt->lef = new Node();
	if (!rt->rig) rt->rig = new Node();
	rt->lef->lazy += rt->lazy;
	rt->rig->lazy += rt->lazy;
	rt->lazy = 0;
}

pair<int,int> query(Node *rt, int L, int R, int val){ //find first position with value greater or equal to it
	push_lazy(rt);
	if (L == R) return {L, rt->val};
	if (rt->lef)
		push_lazy(rt->lef);
	if (rt->lef && rt->lef->val >= val)
		return query(rt->lef, L, (L+R)/2, val);
	else if (rt->rig) return query(rt->rig, (L+R)/2+1, R, val);
	else return {0, -0};
}

void update(Node *rt, int L, int R, int UL, int UR, int val){
	// cout << val << endl;
	push_lazy(rt);
	if (UL <= L && R <= UR){
		rt->lazy += val;
		push_lazy(rt);
		return;
	}
	if (UL <= (L+R)/2){
		if (!rt->lef) rt->lef = new Node();
		update(rt->lef, L, (L+R)/2, UL, UR, val);
	}
	if ((L+R)/2 + 1 <= UR){
		if (!rt->rig) rt->rig = new Node();
		update(rt->rig, (L+R)/2+1, R, UL, UR, val);
	}
	if (rt->lef) push_lazy(rt->lef);
	if (rt->rig) push_lazy(rt->rig);
	rt->val = max(rt->lef?rt->lef->val:0, rt->rig?rt->rig->val:0);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	root = new Node();
	set<pair<pair<int,int>,int>> S; //range, increment amount
	S.insert({{0, n+1}, 0});
	while (true){
		char typ; cin >> typ;
		if (typ == 'E') break;
		else if (typ == 'I'){
			int l, r, inc; cin >> l >> r >> inc;
			int ll, rr, val;
			while (true){ //Case #1
				auto it = S.lower_bound({{l, -1e9}, -1e9});
				if (it == S.end() || it->first.second > r) break;
				ll = it->first.first, rr = it->first.second, val = it->second;
				update(root, 0, n+1, rr, n+1, -val*(rr - ll + 1));
				S.erase(it);
			}
			//Case #2
			auto it = S.lower_bound({{l, -1e9}, -1e9});
			if (it != S.end()){
				ll = it->first.first, rr = it->first.second, val = it->second;
				if (l <= ll && ll <= r){
					update(root, 0, n+1, rr, n+1, -val*(r - ll + 1));
					ppiii toadd = *it;
					toadd.first.first = r+1;
					S.erase(it);
					S.insert(toadd);
				}
			}

			//Case #3

			it = S.lower_bound({{l, -1e9}, -1e9});
			--it;
			ll = it->first.first, rr = it->first.second, val = it->second;
			if (l <= rr && rr <= r){
				update(root, 0, n+1, rr, n+1, -val*(rr - ll + 1));
				update(root, 0, n+1, l-1, n+1, val*((l-1) - ll + 1));
				ppiii toadd = *it;
				toadd.first.second = l-1;
				S.erase(it);
				S.insert(toadd);
			}

			//Case #4

			it = --S.lower_bound({{l, 1e9}, -1e9});
			
			ll = it->first.first, rr = it->first.second, val = it->second;
			if (ll <= l && r <= rr){
				update(root, 0, n+1, rr, n+1, -val*(r - ll + 1));
				update(root, 0, n+1, l-1, n+1, val*((l-1) - ll + 1));
				// cout << "LOL";
				ppiii toadd1 = *it;
				toadd1.first.second = l-1;
				ppiii toadd2 = *it;
				toadd2.first.first = r+1;
				S.erase(it);
				S.insert(toadd1);
				S.insert(toadd2);
			}

			ppiii toadd = make_pair(make_pair(l, r), inc);
			update(root, 0, n+1, r, n+1, inc*(r-l+1));
			
			S.insert(toadd);
		}
		else if (typ == 'Q'){
			int h; cin >> h;
			if (root->val <= h){
				cout << n << '\n';
			}
			else{
				pair<int,int> loc = query(root, 0, n+1, h+1); //first pos with value >= h+1

				auto it = --S.lower_bound({{loc.first+1, loc.first}, -1});
				int inc = it->second;
				if (it->second == 0){
					cout << 0 << '\n';
				}
				else
					cout << (loc.first - ((loc.second - h - 1)/inc + 1)) << '\n';
			}
		}
	}

	return 0;
}