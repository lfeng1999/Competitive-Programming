#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
typedef long double ldouble;

long long modinv(long long a, long long b){ //a mod b's inverse
	if (a == 0) return 0;
	if (a == 1)
		return 1;
	return b - modinv(b%a, a)*b/a;
}
int gcd(int a, int b){
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a%b);
}


int n, m;
vector<int> graph[200010], ps;
int dp[200010], pre[200010], val[200010];
bool primes[200010];
vector<int> pfactor;
vector<int> nodes;
bool past[200010];
bool invalid[200010];
int maxfactor[200010];

void setup(int v){
	if (past[v]) return;
	nodes.push_back(v);
	past[v] = true;
	for (int x : pfactor){
		int tmp = v*x;
		if (n%tmp == 0 && n >= tmp){
			setup(tmp);
			graph[v].push_back(tmp);
		}
	}
}
stack<int> stk;
void dfs(int v){
	past[v] = true;
	for (int u : graph[v]){
		if (!past[u])
			dfs(u);
	}
	stk.push(v);
}

int arr[200010];
vector<int> lol[200010];

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	memset(primes, true, sizeof(primes)); primes[0] = primes[1] = false;
	for (int i=2; i<=sqrt(n); ++i){
		if (!primes[i]) continue;
		for (int p = i*i; p <= sqrt(n); p += i){
			primes[p] = false;
		}
		ps.push_back(i);
	}
	int tmp = n;
	for (int p : ps){
		if (n % p != 0) continue;
		while (tmp % p == 0){
			tmp /= p;
		}
		pfactor.push_back(p);
	}
	if (tmp != 1) pfactor.push_back(tmp);
	setup(1);
	for (int qq=0; qq<m; ++qq){
		int x; cin >> x;
		invalid[x] = true;
		if (x == 0) invalid[n] = true;
	}
	for (int i=1; i<=n; ++i){
		if (invalid[i]) continue;
		int tmp = i, mult = gcd(n, i);
		val[mult]++;
		maxfactor[i] = mult;
	}
	memset(past, false, sizeof(past));
	dfs(1);
	dp[1] = val[1];
	pre[n] = 1;
	while (!stk.empty()){
		int v = stk.top(); stk.pop();
		for (int u : graph[v]){
			if (dp[v] + val[u] >= dp[u]){
				dp[u] = dp[v] + val[u];
				pre[u] = v;
			}
		}
	}
	stack<int> ord;
	int v = n;
	while (v != 1){
		ord.push(v);
		v = pre[v];
	}
	ord.push(1);
	for (int i=1; i<=n; ++i){
		if (i == n){
			if (!invalid[n] && !invalid[0]){
				lol[maxfactor[i]].push_back(0);
			}
			continue;
		}
		if (!invalid[i]){
			lol[maxfactor[i]].push_back(i);
		}
	}
	//now how do i reconstruct this? LOL
	int id = 0;
	while (!ord.empty()){
		int v = ord.top(); ord.pop();
		for (int x : lol[v]){
			arr[++id] = x;
		}
	}
	cout << id << '\n';
	int beg = 1;
	memset(past, false, sizeof(past));
	for (int i=1; i<=id; ++i){
		int tmpgcd = gcd(n, beg);
		int tmp1 = beg/tmpgcd, tmp2 = arr[i]/tmpgcd, tmpn = n/tmpgcd;
		int mult = (modinv(tmp1, tmpn)*tmp2)%n;
		cout << mult << " ";
		beg = arr[i];
	}

	return 0;
}