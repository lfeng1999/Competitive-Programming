#include <bits/stdc++.h>

using namespace std;

inline double EQ(double a, double b){return fabs(a - b) < 1e-15;}

int x = 0;
struct Hill{
	int x1, y1, x2, y2, id;
	double slope;
	bool operator < (const Hill &b) const{
		double py1 = y1 + (x - x1)*slope, py2 = b.y1 + (x - b.x1)*b.slope;
		if (!EQ(py1, py2)) return py1 < py2;
		return id < b.id;
	}
};

vector<Hill> hs;
set<Hill> shs;
int n;

int main(){
	// freopen("test.txt","r",stdin);
	freopen("hillwalk.in","r",stdin);
	freopen("hillwalk.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int id = 0;
	vector<pair<int,pair<int,int>>> es; //removal first, add second
	for (int i=0; i<n; ++i){
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == 0 && y1 == 0) id = i;
		hs.push_back({x1, y1, x2, y2, i, (double)(y2-y1)/(x2-x1)});
		es.push_back(make_pair(x1, make_pair(1, i))); //add
		es.push_back(make_pair(x2, make_pair(-1, i))); //remove
	}
	sort(es.begin(), es.end());
	int ans = 1;
	for (int i=0; i<es.size(); ++i){
		int j = i;
		bool fall = false;
		x = es[i].first;
		while (j < es.size() && es[j].first == es[i].first){
			int typ = es[j].second.first, cid = es[j].second.second;
			if (typ == 1){
				shs.insert(hs[cid]);
			}
			else{
				if (cid == id) 
					fall = true;
				shs.erase(hs[cid]);
			}
			++j;
		}
		if (fall){
			auto it = shs.upper_bound(hs[id]);
			if (it == shs.begin()) break;
			ans++;
			id = (*--it).id;
		}
		i = j-1;
	}
	cout << ans;
	return 0;
}