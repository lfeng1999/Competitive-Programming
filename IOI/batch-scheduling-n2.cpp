#include <bits/stdc++.h>

using namespace std;

int n, S;
vector<pair<int,pair<int,int>>> qs[10010];
int idx[10010], T[10010], sumT[10010], F[10010], sumF[10010];

int intersect(pair<int,int> l1, pair<int,int> l2){
	double ret = (double)(l1.first - l2.first)/(double)(l2.second - l1.second);
	return (int)(ret + 1.0 - 1e-9);
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> S;
	qs[0].push_back({0, {0, 0}});
	for (int i=1; i<=n; ++i){
		cin >> T[i] >> F[i];
		sumT[i] = T[i] + sumT[i-1];
		sumF[i] = F[i] + sumF[i-1];

		//time to solve
		int finans = 2e9;
		for (int j=i-1; j>=0; --j){
			while ((idx[j] + 1 < qs[j].size()) && (qs[j][idx[j]+1].first <= sumT[i])){
				++idx[j];
			}
			int ans = qs[j][idx[j]].second.first + (j+1)*S*sumF[i] + sumF[i]*sumT[i] - sumT[i]*sumF[qs[j][idx[j]].second.second];
			finans = min(finans, ans);

			ans -= (j+2)*S*sumF[i];

			pair<int,int> chk = {ans, -sumF[i]};
			while (qs[j+1].size() >= 2){
				int id1 = qs[j+1][qs[j+1].size()-2].second.second;
				int sum1 = qs[j+1][qs[j+1].size()-2].second.first;
				pair<int,int> pair1 = {sum1, -sumF[id1]};


				if (intersect(pair1, chk) <= qs[j+1][qs[j+1].size()-1].first){
					qs[j+1].pop_back();
				}
				else{
					break;
				}
			}
			int ix = 0;
			if (qs[j+1].size() > 0){
				int id2 = qs[j+1][qs[j+1].size()-1].second.second;
				int sum2 = qs[j+1][qs[j+1].size()-1].second.first;
				pair<int,int> pair2 = {sum2, -sumF[id2]};
				ix = intersect(pair2, chk);
			}
			qs[j+1].push_back({ix, {ans, i}});

			idx[j+1] = min(idx[j+1], (int)qs[j+1].size()-1);
		}

		if (i == n){
			cout << finans;
		}
	}
	return 0;
}