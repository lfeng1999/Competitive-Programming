#include <bits/stdc++.h>

using namespace std;

map<vector<int>, vector<int>> M;
int k, n;
string s[11];
int bits[11][100010];

int query(int *bit, int i){
	i += 50000;
	int ret = 0;
	for (; i > 0; i -= i&(-i))
		ret = max(ret, bit[i]);
	return ret;
}
void update(int *bit, int i, int val){
	i += 50000;
	for (; i < 100010; i += i&(-i))
		bit[i] = max(bit[i], val);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("cbs.in","r",stdin);
	freopen("cbs.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> k >> n;
	for (int i=0; i<k; ++i){
		cin >> s[i];
	}
	vector<int> cur(k, 0);
	int ans = 0;
	for (int i=0; i<n; ++i){
		bool alllef = true, allrig = true;
		for (int j=0; j<k; ++j){
			if (s[j][i] == '(') allrig = false;
			if (s[j][i] == ')') alllef = false;
		}
		for (int j=0; j<k; ++j){
			update(bits[j], cur[j], i);
		}
		if (alllef){
			M[cur].push_back(i);
		}
		for (int j=0; j<k; ++j){
			cur[j] += (s[j][i] == '('?1:-1);
		}
		if (allrig){
			int pos = 0;
			for (int j=0; j<k; ++j){ 
				pos = max(pos, query(bits[j], cur[j] - 1));
			}
			ans += M[cur].size() - (upper_bound(M[cur].begin(), M[cur].end(), pos) - M[cur].begin());
		}
	}
	cout << ans;
	return 0;
}