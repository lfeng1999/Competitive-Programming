#include <bits/stdc++.h>

using namespace std;

string S;
int cnt[100010][3];
bool exist0 = false;

string fix(string S){
	int L = 0;
	while (L < S.length() && S[L] == '0'){
		L++;
	}
	return S.substr(L, S.length()-L);
}
void bad(){
	if (exist0) cout << 0;
	else cout << -1;
}

int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> S;
	int sum = 0;
	for (int i=0; i<S.length(); ++i){
		sum += S[i] - '0';
		if (S[i] == '0')
			exist0 = true;
	}
	string S1 = "IMPOSSIBLE", S2 = "IMPOSSIBLE";
	if (sum%3 == 0){
		cout << S;
		return 0;
	}
	else if (sum%3 == 1){
		int id = -1;
		for (int i=S.length()-1; i>=0; --i){
			if ((S[i] - '0')%3 == 1){
				id = i;
				break;
			}
		}
		if (id != -1){
			S1 = S.substr(0, id) + S.substr(id+1, S.length()-id-1);
		}
		vector<int> l;
		for (int i=S.length()-1; i>=0; --i){
			if ((S[i] - '0')%3 == 2){
				l.push_back(i);
			}
			if (l.size()==2) break;
		}
		if (l.size() >= 2){
			swap(l[0], l[1]);
			S2 = S.substr(0, l[0]) + S.substr(l[0]+1, l[1]-l[0]-1) + S.substr(l[1]+1, S.length()-l[1]-1);
		}
		//remove 2 digits 10 or 2___2
	}
	else if (sum%3 == 2){
		int id = -1;
		for (int i=S.length()-1; i>=0; --i){
			if ((S[i] - '0')%3 == 2){
				id = i;
				break;
			}
		}
		if (id != -1){
			S2 = S.substr(0, id) + S.substr(id+1, S.length()-id-1);
		}
		vector<int> l;
		for (int i=S.length()-1; i>=0; --i){
			if ((S[i] - '0')%3 == 1){
				l.push_back(i);
			}
			if (l.size()==2) break;
		}
		if (l.size() >= 2){
			swap(l[0], l[1]);
			S1 = S.substr(0, l[0]) + S.substr(l[0]+1, l[1]-l[0]-1) + S.substr(l[1]+1, S.length()-l[1]-1);
		}
	}
	S1 = fix(S1); S2 = fix(S2);
	if (S1 == "IMPOSSIBLE" && S2 == "IMPOSSIBLE"){
		bad(); return 0;
	}
	else if (S1 == "IMPOSSIBLE"){
		if (S2.length() == 0){
			bad();
		}
		else{
			cout << S2;
		}
	}
	else if (S2 == "IMPOSSIBLE"){
		if (S1.length() == 0){
			bad();
		}
		else{
			cout << S1;
		}
	}
	else{
		if (S1.length() < S2.length()) swap(S1, S2);
		cout << S1;
	}
	return 0;
}