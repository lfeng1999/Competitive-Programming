#include <bits/stdc++.h>

using namespace std;

typedef long long lint;
const lint ha = 1000007, hm = 1000000007;
lint n;
string S;

lint convert(lint h, lint x){
	return (h*ha + x) % hm;
}

int main(){
	// freopen("test.txt","r",stdin);
	freopen("censor.in","r",stdin);
	freopen("censor.out","w",stdout);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> S >> n;
	unordered_map<lint, unordered_map<lint,vector<string>>> M; //saves collisions
	for (lint i=0; i<n; ++i){
		string tmp; cin >> tmp;
		lint hsh = 0;
		for (lint i=0; i<tmp.length(); ++i){
			hsh = convert(hsh, tmp[i] - 'a');
		}
		M[tmp.length()][hsh].push_back(tmp); //collisions
	}
	string cur = "";
	vector<lint> curhash(1, 0);
	vector<lint> mult(1, 1);

	for (lint i=0; i<S.length(); ++i){
		cur += S[i];
		curhash.push_back(convert(curhash.back(), S[i] - 'a'));
		mult.push_back((mult.back()*ha)%hm);
		// cout << curhash.back() << endl;
		bool toDelete = false;
		lint bestlen = 0;
		for (auto &it : M){
			lint len = it.first;
			if (len > cur.length()) continue;
			lint thishash = (curhash.back() - curhash[curhash.size()-1-len]*mult[len] + hm*hm)%hm;
			auto pos = it.second.find(thishash);
			if (pos != it.second.end()){
				for (auto &st : pos->second){
					if (st == cur.substr(cur.length()-len, len)){
						toDelete = true;
						bestlen = max(bestlen, len);
						break;
					}
				}
			}
		}
		if (toDelete){
			curhash.resize(curhash.size() - bestlen);
			mult.resize(mult.size() - bestlen);
			cur.resize(cur.size() - bestlen);
		}
	}
	cout << cur;
	return 0;
}