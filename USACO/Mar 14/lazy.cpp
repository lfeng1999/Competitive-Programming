#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;

struct Update{
	int y, x1, x2, val;
	bool operator < (const Update &a) const{
		return y < a.y;
	}
};

map<int,int> compx, compy;
int n, k;

int seg[8000010], lazy[8000010];

void push_lazy(int v){
	seg[v] += lazy[v];
	if (v*2 < 8000010){
		lazy[v*2] += lazy[v];
		lazy[v*2+1] += lazy[v];
	}
	lazy[v] = 0;
}

void update(int v, int L, int R, int UL, int UR, int val){
	push_lazy(v);
	if (R < UL || UR < L) return;
	if (UL <= L && R <= UR){
		lazy[v] += val;
		push_lazy(v);
		return;
	}
	int mid = (L+R)/2;
	update(v*2, L, mid, UL, UR, val);
	update(v*2+1, mid+1, R, UL, UR, val);
	seg[v] = max(seg[v*2], seg[v*2+1]);
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("lazy.in","r",stdin);
	freopen("lazy.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	vector<Update> us;
	for (int qq=0; qq<n; ++qq){
		int g, x, y; cin >> g >> x >> y;
		us.push_back(Update({x+y-k, max(x-y+MAXN-k, 0), min(x-y+MAXN+k, (int)2e6), g}));
		us.push_back(Update({x+y+k + 1, max(x-y+MAXN-k, 0), min(x-y+MAXN+k, (int)2e6), -g}));
	}
	sort(us.begin(), us.end());
	int ans = 0;
	for (int i=0; i<2*n; ++i){
		int j = i;
		while (j < 2*n && us[j].y == us[i].y){
			update(1, 0, 2*MAXN, us[j].x1, us[j].x2, us[j].val);
			++j;
		}
		--j;
		i = j;
		ans = max(ans, seg[1]);
	}
	cout << ans;
	return 0;
}