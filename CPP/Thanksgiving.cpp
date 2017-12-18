#include <bits/stdc++.h>


using namespace std;

int MAX_N = 100005;
vector<int> graph[200010];// 1..MAX_N is people, MAX_N+1.... MAX_N*2 is dishes
bool past[200010];
int N, people_ans[100010], dishes_ans[100010], p_cnt = 1, d_cnt = 1;
int people[200010], p_left = MAX_N, p_right = MAX_N+1;
int dishes[200010], d_left = MAX_N, d_right = MAX_N+1;

bool solve(int v, int p, int dir){

	if (past[v]) return false;
	//cout << v << " " << p << " " << dir << endl;

	if (dir == 0){ //0 is left
		if (v >= MAX_N) dishes[d_left--] = v - MAX_N;
		else people[p_left--] = v;
	}
	else{ //1 is right
		if (v >= MAX_N) dishes[d_right++] = v - MAX_N;
		else people[p_right++] = v;
	}

	past[v] = true;

	int testedge = 0;
	for (int u : graph[v]){
		if (graph[u].size() >= 2){
			testedge++;
		}
	}
	if (testedge > 2) return false;

	for (int u : graph[v]){
		if (past[u]) continue;
		if (graph[u].size() == 1){
			if (!solve(u, v, dir)){
				return false;
			}
		}
	}

	bool is_first = true;
	for (int u : graph[v]){
		if (graph[u].size() > 1 && u != p){
			if (is_first){
				if (!solve(u, v, dir)){
					return false;
				}
				is_first = false;
			}
			else{
				if (!solve(u, v, 1^dir)){
					return false;
				}
			}
		}
	}
	return true;
}


bool visited[200010];
bool is_cycle(int v, int p){
	if (visited[v]) return true;
	visited[v] = true;

	for (int u : graph[v]){
		if (u == p) continue;
		if (is_cycle(u, v))
			return true;
	}
	return false;
}

int main(){
	// freopen("TLE.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N;

	for (int i=1; i<=N; ++i){
		int d;
		cin >> d;
		for (int qq=0; qq<d; ++qq){
			int di; cin >> di;
			graph[di+MAX_N].push_back(i);
			graph[i].push_back(di+MAX_N);
		}
	}
	for (int i=1; i<=N; ++i){
		if (visited[i]) continue;
		if (is_cycle(i, -1)){
			cout << "every man for himself!";
			return 0;
		}
	}
	for (int k=1; k<=2*MAX_N; ++k){
		if (past[k] || graph[k].size() != 1) continue;

		if (k % MAX_N > N) continue;

		if (!solve(k, -1, 1)){
			cout << "every man for himself!";
			return 0;

		}

		for (int i=p_left+1; i<p_right; ++i){
			people_ans[p_cnt++] = people[i];
		}
		p_left = MAX_N; p_right = MAX_N+1;
		for (int i=d_left+1; i<d_right; ++i){
			dishes_ans[d_cnt++] = dishes[i];
		}
		d_left = MAX_N; d_right = MAX_N+1;
	}
	for (int i=1; i<=N; ++i){
		if (graph[i].size() == 0){
			people_ans[p_cnt++] = i;
			past[i] = true;
		}
		if (graph[i+MAX_N].size() == 0){
			dishes_ans[d_cnt++] = i;
			past[i+MAX_N] = true;
		}
		if (!past[i] || !past[i+MAX_N]){
			cout << "every man for himself!";
			return 0;
		}
	}
	for (int i=1; i<=N; ++i){
		cout << people_ans[i] << " ";
	}


	cout << endl;
	for (int i=1; i<=N; ++i){
		cout << dishes_ans[i] << " ";
	}
	cout << endl;



	return 0;
}