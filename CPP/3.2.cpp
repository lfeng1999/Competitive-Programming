#include <bits/stdc++.h>

using namespace std;

struct Classroom{
	int p;
	vector<int> students;
	bool operator < (const Classroom &a){
		return p < a.p;
	}
} classes[510];

map<int,int> compress;
map<int,int> period_ans;
map<int,int> passes_ans;

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	int N;
	cin >> N;

	int CSID, GID;
	cin >> CSID >> GID;

	for (int i=0; i<N; ++i){
		int p, s;
		cin >> p >> s;
		classes[i].p = p;
		for (int j=0; j<s; ++j){
			int st;
			cin >> st;
			classes[i].students.push_back(st);
		}
	}
	period_ans[CSID] = 0;
	passes_ans[CSID] = 0;

	sort(classes, classes + N);

	for (int i=0; i<N; ++i){
		int min_pass = 1e9, cur_period = classes[i].p;

		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];

			if (passes_ans.count(st))
				min_pass = min(min_pass, passes_ans[st]);
		}
		// cout << endl;
		// cout << min_pass << endl;
		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];
			// cout << st << " ";
			if ((passes_ans.count(st) && passes_ans[st] > min_pass+1) || !passes_ans.count(st)){
				passes_ans[st] = min_pass + 1;
				period_ans[st] = cur_period;
			}
		}
		// cout << endl;
		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];
			// cout << passes_ans[st] << " ";
		}
	}


	if (passes_ans[GID] >= 1e9 || !passes_ans.count(GID)){
		cout << "delivery failure";
	}
	else{
		cout << passes_ans[GID] << endl << period_ans[GID];
	}






	return 0;
}