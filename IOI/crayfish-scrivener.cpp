#include <bits/stdc++.h>

using namespace std;

struct Node{
	Node *par[22];
	int len = -1;
	char ch = '.';
	Node(){
		for (int i=0; i<22; ++i){
			par[i] = this;
		}
	}
};
Node *root[1000010];
int nq, curroot = 0;

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> nq;
	root[0] = new Node();
	for (int qq=0; qq<nq; ++qq){
		char cmd; cin >> cmd;
		if (cmd == 'P'){
			int x; cin >> x;
			int dif = root[curroot]->len - x;
			Node *cur = root[curroot];
			for (int i=21; i>=0; --i){
				if (dif >= (1 << i)){
					dif -= (1 << i);
					cur = cur->par[i];
				}
			}
			cout << cur->ch << '\n';
			continue;
		}
		++curroot;
		if (cmd == 'T'){
			char x; cin >> x;
			root[curroot] = new Node();
			root[curroot]->ch = x;
			root[curroot]->par[0] = root[curroot-1];
			root[curroot]->len = root[curroot-1]->len + 1;
			for (int i=1; i<22; ++i){
				root[curroot]->par[i] = root[curroot]->par[i-1]->par[i-1];
			}
		}
		else if (cmd == 'U'){
			int x; cin >> x;
			root[curroot] = root[curroot - x - 1];
		}
	}
	return 0;
}