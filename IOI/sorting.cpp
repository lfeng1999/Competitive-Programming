#include <bits/stdc++.h>

using namespace std;

int n, m, arr[200010], s[600010][2], ip[200010], vp[200010];
int cur[200010], to[200010];

bool past[200010];
bool valid(int len){
	for (int i=0; i<n; ++i){
		cur[i] = i;
	}
	for (int i=len; i>=1; --i){
		swap(cur[s[i][0]], cur[s[i][1]]);
	}
	for (int i=0; i<n; ++i){
		to[ip[cur[i]]] = i;
	}
	int ret = 0;
	memset(past, false, sizeof(past));
	for (int i=0; i<n; ++i){
		if (past[i]) continue;
		int rt = i;
		while (!past[rt]){
			past[rt] = true;
			rt = to[rt];
			ret++;
		}
		ret--;
	}
	return ret <= len;
}

void doswap(int i1, int i2, int toprint){
	if (toprint){
		cout << i1 << " " << i2 << '\n';
	}
	swap(ip[arr[i1]], ip[arr[i2]]);
	swap(arr[i1], arr[i2]);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i){
		cin >> arr[i];
		ip[arr[i]] = i;
		vp[i] = arr[i];
	}
	cin >> m;
	for (int i=1; i<=m; ++i){
		cin >> s[i][0] >> s[i][1];
	}
	int L = 0, R = m;
	while (L < R){
		int mid = (L+R)/2;
		if (valid(mid)) R = mid;
		else L = mid + 1;
	}
	cout << L << '\n';
	vector<pair<int,int>> toswap;
	for (int i=0; i<n; ++i) cur[i] = i;
	for (int i=L; i>=1; --i){
		swap(cur[s[i][0]], cur[s[i][1]]);
	}
	for (int i=0; i<n; ++i){
		to[ip[cur[i]]] = i;
	}
	memset(past, false, sizeof(past));
	for (int i=0; i<n; ++i){
		if (past[i]) continue;
		int rt = i;
		while (!past[rt]){
			past[rt] = true;
			toswap.push_back(make_pair(cur[ip[cur[rt]]], cur[rt]));
			rt = to[rt];
		}
		toswap.pop_back();
	}
	for (int i=1; i<=toswap.size(); ++i){
		int a = toswap[i-1].first, b = toswap[i-1].second;
		doswap(ip[arr[s[i][0]]], ip[arr[s[i][1]]], 0);
		doswap(ip[a], ip[b], 1);
	}
	for (int i=toswap.size()+1; i<=L; ++i){
		cout << 0 << " " << 0 << '\n';
	}



	return 0;
}