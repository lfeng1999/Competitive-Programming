#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000010;
int N, P;
int dolls[MAX_N];
map<int,int> M;
int pos_bit[MAX_N], neg_bit[MAX_N], n_zero = 1;

int query(int *bit, int i){
	int tot = 0;
	for (; i > 0; i -= i&(-i)){
		tot += bit[i];
	}
	return tot;
}
void update(int *bit, int i){
	for (; i < MAX_N; i += i&(-i)){
		bit[i] ++;
	}
}


int main(){
	freopen("vudu.in.9","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i=0; i<N; ++i){
		cin >> dolls[i];
	}
	cin >> P;
	set<int> S;
	for (int i=0; i<N; ++i){
		dolls[i] -= P;
		if (i != 0)
			dolls[i] += dolls[i-1];
		S.insert(abs(dolls[i]));
	}
	int new_val = 1;
	for (int s : S){
		M[s] = new_val++;
	}
	long long ans = 0;
	for (int i=0; i<N; ++i){
		if (dolls[i] != 0)
			dolls[i] = dolls[i]/abs(dolls[i])*M[abs(dolls[i])];
		if (dolls[i] < 0){
			ans += query(neg_bit, MAX_N-1) - query(neg_bit, abs(dolls[i]) - 1);
			update(neg_bit, abs(dolls[i]));
		}
		else if (dolls[i] > 0){
			ans += n_zero;
			ans += query(pos_bit, dolls[i]);
			ans += query(neg_bit, MAX_N - 1);
			update(pos_bit, dolls[i]);
		}
		else{ // == 0
			ans += n_zero;
			ans += query(neg_bit, MAX_N-1);
			n_zero++;
		}
	} //The new compressed version
	cout << ans;




	return 0;
}