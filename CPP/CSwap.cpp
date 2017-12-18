#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int N, K, lights[100010], nred[100010], nblue[100010];

vector<int> psumblue, psumred, distblue, distred;

bool validblue(int L, int R){
	int mid = (L+R)/2;

	int dist = distblue[mid]*(mid-L+1) - (psumblue[mid] - psumblue[L-1]);

	dist += distblue[R]*(R-mid+1) - (psumblue[R] - psumblue[mid-1]);
	return dist <= K;	
}

bool validred(int L, int R){
	int mid = (L+R)/2;

	int dist = distred[mid]*(mid-L+1) - (psumred[mid] - psumred[L-1]);

	dist += distred[R]*(R-mid+1) - (psumred[R] - psumred[mid-1]);
	return dist <= K;	
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N >> K;
	psumblue.push_back(0);
	psumred.push_back(0);
	distblue.push_back(0);
	distred.push_back(0);
	for (int i=1; i<=N; ++i){
		char ch; cin >> ch;
		lights[i] = (ch == '1')?1:0;
		if (lights[i] == 1){
			nblue[i]++;
		}
		else if (lights[i] == 0){
			nred[i]++;
		}
		nblue[i] += nblue[i-1];
		nred[i] += nred[i-1];

		if (lights[i] == 1){
			psumblue.push_back(nred[i] + psumblue[psumblue.size()-1]);
			distblue.push_back(nred[i]);
		}
		else if (lights[i] == 0){
			psumred.push_back(nblue[i] + psumred[psumred.size()-1]);
			distred.push_back(nblue[i]);
		}
	}
	int bestblue = 0, bestred = 0;
	int L = 1, R = 1;

	while (R < psumblue.size()){
		while (R < psumblue.size() && validblue(L, R))
			R++;
		bestblue = max(bestblue, (R - 1) - L + 1);
		L++;
	}
	L = 1, R = 1;

	while (R < psumred.size()){
		while (R < psumred.size() && validred(L, R))
			R++;
		bestred = max(bestred, (R - 1) - L + 1);
		L++;
	}
	// for (int i=0; i<psumblue.size(); ++i)
	// 	cout << psumblue[i] << " " << distblue[i] << endl;

	cout << bestblue << " " << bestred;

	return 0;
}