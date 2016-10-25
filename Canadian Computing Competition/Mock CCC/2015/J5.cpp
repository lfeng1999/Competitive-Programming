#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIPII;
#define INF 1 << 30
#define INF2 0x3f3f3f3f
#define INF3 0x7fffffff
#define mp make_pair
#define pb push_back
#define MOD 1000000007]
#define mset(a) memset(a,0,sizeof(a))
#define mset2(a) memset(a,INF2,sizeof(a))
#define rint(x) scanf("%d",&x)
#define rchar(x) scanf(" %c",&x)
#define rll(x) scanf("%lld",&x)
#define ssort(x) sort(x.begin(),x.end())

PII bd[200001], walk[200001];
vector<int> Pxs, Pys, bx[200001], by[200001];
unordered_set<int> Xs, Ys;
map<int, int> cx, cy;
int N, x, y, M;

int hori(int ay, int ax, int ax2)
{
	int ny = cy[ay];
	return upper_bound(by[ny].begin(), by[ny].end(), ax2) - lower_bound(by[ny].begin(), by[ny].end(), ax);
}

int vert(int ax, int ay,int ay2)
{
	int nx = cx[ax];
	return upper_bound(bx[nx].begin(), bx[nx].end(), ay2) - lower_bound(bx[nx].begin(), bx[nx].end(), ay);;
}



int main()
{
	//ifstream file("MockCCCJ5.txt");
	cin.sync_with_stdio(0);cin.tie(0);
	cin >> N;
	for (int i = 0; i != N; ++i)
	{
	    cin >> x >> y;
		Xs.insert(x);
		Ys.insert(y);
		bd[i] = mp(x, y);
	}
	cin >> M;
	for (int i = 0; i != M; ++i)
	{
	    cin >> x >> y;
		Xs.insert(x);
		Ys.insert(y);
		walk[i] = mp(x, y);
	}
	int counter = 1;
	for (int i : Xs)
	{
		cx[i] = counter;
		++counter;
	}
	counter = 1;
	for (int i : Ys)
	{
		cy[i] = counter;
		++counter;
	}
	for (int j=0; j!=N; ++j)
	{
	    PII &i = bd[j];
		bx[cx[i.first]].pb(i.second);
		by[cy[i.second]].pb(i.first);
	}
	for (int i=0; i!=200001; ++i){
        sort(bx[i].begin(), bx[i].end());
        sort(by[i].begin(), by[i].end());
	}
	long long collide = 0;
	for (int i = 1; i != M; ++i)
	{
		int sx = walk[i - 1].first, sy = walk[i - 1].second, ex = walk[i].first, ey = walk[i].second;
		if (sx == ex)
			collide += vert(sx,min(sy,ey),max(sy,ey));
		else
			collide += hori(sy,min(sx,ex),max(sx,ex));
	}

	cout << collide;
	return 0;
}
