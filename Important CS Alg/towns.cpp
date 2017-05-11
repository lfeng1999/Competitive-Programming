#include <bits/stdc++.h>

using namespace std;

int d1[110], d2[110], d3[110], nodes[3], branch[110], group[110], gcnt[110];
int fk = 0;
// int getDistance(int i, int j){
// 	return 0;
// }

int hubDistance(int N, int sub){
	// fk++;
	// if (fk < 10)
	// 	return 0;
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	memset(d3, 0, sizeof(d3));
	memset(branch, 0, sizeof(branch));
	memset(group, 0, sizeof(group));
	memset(gcnt, 0, sizeof(gcnt));
	memset(nodes, 0, sizeof(nodes));

	int st = 0, v = 0, u = 0, furthest = -1e9;
	for (int i=0; i<N; ++i){
		if (i == st){
			d1[i] = 0;
			continue;
		}
		d1[i] = getDistance(i, st);
		if (furthest < d1[i]){
			furthest = d1[i];
			v = i;
		}		
	}
	furthest = -1e9;
	for (int i=0; i<N; ++i){
		if (i == v){
			d2[i] = 0;
			continue;
		}
		d2[i] = getDistance(i, v);
		if (furthest < d2[i]){
			furthest = d2[i];
			u = i;
		}		
	} //found furthest again... lol
	branch[st] = (d1[v] + d1[u] - furthest)/2;
	sub = 1e9;
	map<int,vector<int>> M;
	for (int i=0; i<N; ++i){
		branch[i] = (d1[i] + d2[i] - d1[v])/2; //This is a partial branch off of the path of st -> v
		M[d2[i] - branch[i]].push_back(i);
	}
	int lsum = 0, rsum = N;
	vector<int> calc;
	for (auto x : M){
		sub = min(sub, max(x.first, furthest - x.first));
	}
	int nfailed = 0, ntot = 0;
	for (auto x : M){
		rsum -= x.second.size(); // If x is the current hub... I can subtract temp
		if (max(x.first, furthest - x.first) == sub){ //There's up to 2 possible hubs with R length... One of them is going to be unbalanced for sure
			//How do I check possible...
			if (lsum <= N/2 && rsum <= N/2){ 
				calc = x.second; //check this one
			}
			else{
				nfailed++;
			}
			ntot++;
		}
		lsum += x.second.size();
	}
	if (ntot == nfailed) //If the number there are is same as failed. must be unbalanced hub
		return -sub;
	//Otherwise 3n/2 to check if there's majority...

	stack<int> l, b;
	for (int x : calc){
		if (l.empty()){
			l.push(x);
			continue;
		}
		if (getDistance(l.top(), x) == branch[l.top()] + branch[x]){ //separate hurrah....
			l.push(x); //insert it in
			if (!b.empty()){ //check if there's dupes
				l.push(b.top());
				b.pop();
			}
		}
		else{ //same, push it in 
			b.push(x);
		}
	}
	int possible = l.top(), ncnt = 0;
	ncnt = b.size() + 1;
	l.pop();
	if (!l.empty())
		l.pop();
	while (!l.empty()){ //fix base case
		if (getDistance(l.top(), possible) != branch[l.top()] + branch[possible]){ //oh cool. they belong to same branch right...
			l.pop(); //remove it
			ncnt++;
			if (l.empty()) //remove it again
				break;
			l.pop();
		}
		else{ //remove from b and remove from l... oh... well rip it's not possible :#
			if (b.empty()) //oops there's no more... omg fuck this is where it breaks.... 
				break; //If it's empty then what happens o n o.... OH WAIT IDC UNLESS THERE'S MORE THAN N/2 LOOOOOL
			b.pop();
			l.pop();
		}
	}
	if (ncnt > N/2)
		return -sub;

	return sub;
}


int main(){
	// freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);

	return 0;
}