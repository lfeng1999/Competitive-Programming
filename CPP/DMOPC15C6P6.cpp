#include <bits/stdc++.h>

using namespace std;


vector<int> graph[1510];
int N, M, K;
bool past[1510][1510];

struct Node{
	int arr[6], i = 0;
	Node(){memset(arr, 0, sizeof(arr));}
};
Node Nodecopy(Node x){
	Node y;
	for (int i=0; i<6; ++i) y.arr[i] = x.arr[i];
	y.i = x.i;
	return y;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K;
	for (int i=0;i<M; ++i){
		int a, b; cin >> a >> b;
		graph[a].push_back(b); graph[b].push_back(a);
	}
	for (int i=1; i<=N; ++i)
		past[i][i] = true;
	for (int st=1; st<=N; ++st){
		queue<Node> Q;
		Node cur; cur.arr[0] = st;
		Q.push(cur);
		while (!Q.empty()){
			cur = Q.front(); Q.pop();
			// cur.display(); cout << endl;
			// if (Q.size() > 1000) break;
			int arr[6];
			for (int i=0; i<6; ++i) arr[i] = cur.arr[i];
			int v = cur.arr[cur.i];
			int i = cur.i;

			for (int u : graph[v]){
				bool flag = true;
				for (int j=0; j<K; ++j){
					if (!past[arr[(i+6-j)%6]][u])
						flag = false;
				}
				if (flag) continue;
				i = (i+1)%6;
				arr[i] = u;

				for (int j=1; j<=K; ++j){
					past[arr[(i+6-j)%6]][u] = true;
				}
				Node y;
				for (int j=0; j<6; ++j)
					y.arr[j] = arr[j];
				y.i = i;
				Q.push(y);
				i = (i + 5) % 6;
			}
		}
	}
	for (int st=1; st<=N; ++st){
		int ans = 0;
		for (int ed=1; ed<=N; ++ed){
			ans+=past[st][ed];
		}
		cout << ans << '\n';
	}
	return 0;
}