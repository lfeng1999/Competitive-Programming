#include <bits/stdc++.h>

//https://www.reddit.com/r/usaco/comments/39qrta/string_hashing/

using namespace std;

const int hm = 1000000007, ha = 100000007;
int hext(int h, int x){
	return (h*ha + x)%hm;
}

vector<string> mystrings;
vector<vector<int>> hashes;
int id[100010], n;

bool mycmp(int a, int b){ //how do i compare the strings?
	//I look at the first # where the hashes are different
	//The first # or character that's diff will tell me which string is smaller or larger

	//chance of it being wrong is miniscule depending on the hash. 

	if (hashes[a].size() == hashes[b].size() && hashes[a].back() == hashes[b].back()){
		return true; //checks equality
	}

	if (hashes[a].size() > hashes[b].size()){ //checks if the first character diff is after the length of the shortest string
		if (hashes[b].back() == hashes[a][hashes[b].size()-1]) return true;
	}
	else if (hashes[a].size() < hashes[b].size()){
		if (hashes[a].back() == hashes[b][hashes[a].size()-1]) return false;
	}
	//the first character diff is in the string
	int L = 0, R = min(hashes[a].size(), hashes[b].size()) - 1; //somewhere in the string

	while (L < R){
		int mid = (L+R)/2;
		if (hashes[a][mid] == hashes[b][mid]){
			L = mid+1;
		}
		else{
			R = mid;
		}
	} //found first character diff
	return mystrings[a][L] < mystrings[b][L]; //done. 
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	for (int i=0; i<n; ++i){
		string S = mystrings[i];
		vector<int> cur;
		int ch = 0;
		for (int j=0; j<S.length(); ++j){
			ch = hext(ch, S[j] - 'a');
			cur.push_back(ch);
		}
		hashes.push_back(cur);
	}
	sort(id, id + n, mycmp); //now sortings string. fast sorting
	return 0;
}