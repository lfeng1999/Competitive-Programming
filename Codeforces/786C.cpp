#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 17) + 10;
int bit[MAXN];
vector<int> queries[MAXN];
int ans[MAXN], N, nxt[MAXN];
map<int,int> last;

void update(int i, int val){
	for (; i<MAXN; i += i&(-i))
		bit[i] += val;
}

int query(int val){
	int ret = 0;
	for (int i = 16; i>=0; --i){
		int shift = 1 << i;
		if (bit[ret + shift] <= val){
			val -= bit[ret + shift];
			ret += shift;
		}
	}
	return ret;
}
int a[MAXN];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=1; i<=N; ++i){
		cin >> a[i];
	}
	for (int i=1; i<=N; ++i){
		queries[1].push_back(i);
	}
	for (int i=N; i>=1; --i){
		if (last.count(a[i])){
			nxt[i] = last[a[i]];
		}
		else{
			nxt[i] = -1;
		}
		last[a[i]] = i;
	}
	for (auto it = last.begin(); it != last.end(); ++it){
		update(it->second, 1);
	}
	for (int i=1; i<=N; ++i){
		for (int len : queries[i]){
			int np = query(len);
			queries[np+1].push_back(len);
			ans[len]++;
		}
		update(i, -1);
		if (nxt[i] == -1) continue;
		update(nxt[i], 1);
	}
	for (int i=1; i<=N; ++i){
		cout << ans[i] << " ";
	}

	return 0;
}