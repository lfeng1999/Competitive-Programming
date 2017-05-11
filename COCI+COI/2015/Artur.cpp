#include <bits/stdc++.h>

using namespace std;

vector<int> graph[5010];

struct Line{
	int x1, y1, x2, y2;
	double a, b;
	Line(){}
	Line(int _x1, int _y1, int _x2, int _y2){
		x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
		if (x1 == x2){ //vertical
			a = (double) (y1 - y2) / (x1 - x2);
		}
		else{
			a = 0;
		}
		b = y1 - a*x1;
	}
	double get_y(int x){
		return a*x + b;
	}
} lines[5010];

int N;
const double eps = 1e-10;

bool is_greater(double y1, double y2){
	return y1 - y2 > eps;
}

stack<int> stk;

bool past[5010];

void dfs(int v){
	past[v] = true;
	for (int u : graph[v]){
		if (!past[u])
			dfs(u);
	}
	stk.push(v);
}

int main(){
	freopen("artur.in.1a","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	cin >> N;
	for (int i=0; i<N; ++i){
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2){
			swap(x1, x2);
			swap(y1, y2);
		}
		lines[i] = Line(x1, y1, x2, y2);
	}

	for (int i=0; i<N; ++i){
		for (int j=0; j<N; ++j){
			if (i == j) continue;
			int max_x1 = max(lines[i].x1, lines[j].x1), min_x2 = min(lines[i].x2, lines[j].x2);
			if (min_x2 >= max_x1){ //There's overlap
				if (is_greater(lines[i].get_y(max_x1), lines[j].get_y(max_x1))){
					graph[j].push_back(i);
					// cout << j + 1 << " " << i + 1 << endl;
				}
			}
		}
	}
	for (int i=0; i<N; ++i){
		if (!past[i])
			dfs(i);
	}

	while (!stk.empty()){
		cout << stk.top() + 1 << " ";
		stk.pop();
	}


	return 0;
}