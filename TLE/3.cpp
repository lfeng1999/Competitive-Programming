#include <bits/stdc++.h>

using namespace std;

struct Classroom{
	int p;
	vector<int> students;
	bool operator < (const Classroom &a){
		return p < a.p;
	}
} classes[510000];

int N, ans[510000][2];
map<int,int> compress;

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	for (int i=0; i<510000; ++i){
		for (int j=0; j<2; ++j){
			ans[i][j] = 1e9;
		}
	}

	cin >> N;

	int CSID, GID;
	cin >> CSID >> GID;

	set<int> IDs;

	for (int i=0; i<N; ++i){
		int p, s;
		cin >> p >> s;
		classes[i].p = p;
		for (int j=0; j<s; ++j){
			int st;
			cin >> st;
			classes[i].students.push_back(st);
			IDs.insert(st);
		}
	}

	int comp_val = 1;
	for (set<int>::const_iterator it = IDs.begin(); it != IDs.end(); ++it){
		compress[*it] = comp_val;
		comp_val++;
	}

	for (int i=0; i<N; ++i){
		for (int j=0; j<classes[i].students.size(); ++j){
			classes[i].students[j] = compress[classes[i].students[j]];
		}
	}
	CSID = compress[CSID];
	ans[CSID][0] = ans[CSID][1] = 0;
	GID = compress[GID];

	sort(classes, classes + N);



	for (int i=0; i<N; ++i){
		int min_pass = 1e9, cur_period = classes[i].p;

		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];

			min_pass = min(min_pass, ans[st][0]);
		}

		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];

			if (ans[st][0] > min_pass+1){
				ans[st][0] = min_pass + 1;
				ans[st][1] = cur_period;
			}
		}
	}


	if (ans[GID][0] == 1e9){
		cout << "delivery failure";
	}
	else{
		cout << ans[GID][0] << endl << ans[GID][1];
	}






	return 0;
}