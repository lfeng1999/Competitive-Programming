#include <bits/stdc++.h>

using namespace std;

int n1, n2, a1[510], a2[510];
int best[1010], back[1010];


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	fill(back, back+1010, -1);
	cin >> n1;
	for (int i=1; i<=n1; ++i){
		cin >> a1[i]; 
	}
	cin >> n2;
	for (int i=1; i<=n2; ++i){
		cin >> a2[i]; 
	}
	for (int i=1; i<=n1; ++i){
		int len = 0, p = -1;
		for (int j=1; j<=n2; ++j){
			if (a1[i] == a2[j]){
				if (best[j] < len + 1){
					best[j] = len + 1;
					back[j] = p;
				}
			}
			if (a1[i] > a2[j]){
				if (best[j] > len){
					len = best[j];
					p = j;
				}
			}
		}
	}
	int bval = 0, id = -1;
	for (int i=1; i<=n2; ++i){
		if (best[i] > bval){
			bval = best[i];
			id = i;
		}
	}
	cout << bval << endl;
	vector<int> seq;
	while (id != -1){
		// cout << a2[id] << " ";
		seq.push_back(a2[id]);
		id = back[id];
	}
	for (int i=seq.size()-1; i>=0; --i){
		cout << seq[i] << " ";
	}

	return 0;
}