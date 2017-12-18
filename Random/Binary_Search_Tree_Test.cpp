#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<pair<int,int>> S;
map<int,vector<int>> M;
int N, QQ;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> QQ;
	for (int i=1; i<=N; ++i){
		int x; cin >> x;
		M[x].push_back(i);
		S.insert(make_pair(x, i));
		// cout << x << " " << i << endl;
		// cout << M[2].size() << endl;
	}
	int prev = 0;
	for (int i=1; i<=QQ; ++i){
		char ch; int x;
		cin >> ch >> x;
		x ^= prev;
		if (ch == 'I'){
			S.insert(make_pair(x, N+i));
			M[x].push_back(N+i);
		}
		else if (ch == 'R'){
			if (M[x].size() != 0){
				S.erase(make_pair(x, M[x].back()));
				M[x].pop_back();
			}
		}
		else if (ch == 'S'){
			prev = (*S.find_by_order(x-1)).first;
			cout << prev << '\n';
		}
		else if (ch == 'L'){
			// cout << x << " ONONO" << endl;
			if (M[x].size() == 0){
				prev = -1;
			}
			else{
				prev = S.order_of_key(make_pair(x, M[x][0] + 1));
			}
			cout << prev << '\n';
		}
	}
	for (pair<int,int> x : S){
		cout << x.first << " ";
	}
	return 0;
}