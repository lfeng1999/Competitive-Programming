#include <bits/stdc++.h>

using namespace std;

struct Classroom{
	int p;
	vector<int> students;
	bool operator < (const Classroom &a){
		return p < a.p;
	}
} classes[510];

vector<int> students[250010], ending_class;
map<int,int> compress;
int N, CSID, GID, passes[510];
bool inq[510];


void bfs(int start){
	memset(passes, -1, sizeof(passes));
	queue<int> Q;

	for (int i=0; i<students[start].size(); ++i){
		Q.push(students[start][i]);
		passes[students[start][i]] = 1;
	}
	while (!students[start].empty()){
		students[start].pop_back();
	}

	while (!Q.empty()){
		int v = Q.front(); Q.pop();

		for (int i=0; i<classes[v].students.size(); ++i){
			int st = classes[v].students[i];
			while (!students[st].empty() && classes[students[st].back()].p > classes[v].p){

				int u = students[st].back();
				students[st].pop_back();

				if (passes[u] < 0){
					passes[u] = passes[v] + 1;
					Q.push(u);

				}
			}
		}
	}
}


int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> CSID >> GID;


	set<int> STID;
	for (int i=0; i<N; ++i){
		int p, s;
		cin >> p >> s;
		classes[i].p = p;
		for (int j=0; j<s; ++j){
			int st; cin >> st;
			classes[i].students.push_back(st);
			STID.insert(st);
		}
	}
	sort(classes, classes + N);

	int comp_cnt = 0;
	for (set<int>::const_iterator it = STID.begin(); it != STID.end(); ++it){
		compress[*it] = comp_cnt++;
	}
	CSID = compress[CSID];
	GID = compress[GID];

	for (int i=0; i<N; ++i){
		for (int j=0; j<classes[i].students.size(); ++j){
			classes[i].students[j] = compress[classes[i].students[j]];
		}
		sort(classes[i].students.begin(), classes[i].students.end());

		for (int j=0; j<classes[i].students.size(); ++j){
			int st = classes[i].students[j];
			students[st].push_back(i);
		}
	}

	for (int i=0; i<students[GID].size(); ++i){
		ending_class.push_back(students[GID][i]);
	}

	bfs(CSID);

	int pass_ans = 1e9, period_ans = 1e9;
	for (int qq=0; qq<ending_class.size(); ++qq){
		int i = ending_class[qq];

		if (passes[i] > 0 ){
			if (passes[i] < pass_ans){
				pass_ans = passes[i];
				period_ans = classes[i].p;
			}
			else if (passes[i] == pass_ans){
				period_ans = min(classes[i].p, period_ans);
			}
		}
	}
	if (pass_ans == 1e9){
		cout << "delivery failure";
	}
	else{
		cout << pass_ans << endl << period_ans;
	}

	return 0;
}