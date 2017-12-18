#include <bits/stdc++.h>

using namespace std;

int rekt = -1;
int maxtot = 0;
vector<int> ask(int i);
vector<int> ans = {0, 0};
int minL = 0, maxR = 200000;

void solve(int L, int R, vector<int> l1, vector<int> r2){
	if (L+1 >= R) return;
	if (rekt != -1) return;
	if (R < minL || maxR < L) return; 
	if (L + 2 == R){
		for (int i=L+1; i<R; ++i){
			vector<int> cur = ask(i);
			if (cur == ans){
				rekt = i;
				return;
			}
			if (cur[0] == 0){
				minL = L+1;
			}
			if (cur[1] == 0){
				maxR = L+1;
			}
		}
		return;
	}
	int mid1 = (L+R)/2-1, mid2 = (L+R)/2; //random #s
	vector<int> l2;
	bool valid1 = true;
	bool valid2 = true;
	for (; mid1 > L; --mid1){
		vector<int> cur = ask(mid1);
		l2 = cur;
		if (cur == ans){
			rekt = mid1;
			return;
		}
		if (cur[1] == 0){
			valid2 = false;
			maxR = min(maxR, mid1);
		}
		if (cur[0] == 0){
			valid1 = false;
			minL = max(minL, mid1);
			break;
		}
		if (cur[0] + cur[1] == maxtot) break;
	}
	vector<int> r1;
	for (; mid2 < R; ++mid2){
		if (!valid2) break;
		vector<int> cur = ask(mid2);
		r1 = cur;
		if (cur == ans){
			rekt = mid2;
			return;
		}
		if (cur[0] == 0){
			valid1 = false;
			minL = max(minL, mid2);
		}
		if (cur[1] == 0){
			valid2 = false;
			maxR = min(maxR, mid2);
			break;
		}
		if (cur[0] + cur[1] == maxtot) break;
	}
	if ((rand()%2) == 0){
		if (valid1 && l2.size() >= 2 && l1[1] != l2[1])
			solve(L, mid1, l1, l2);
		if (valid2 && r1.size() >= 2 && r1[1] != r2[1])
			solve(mid2, R, r1, r2);
	}
	else{
		if (valid2 && r1.size() >= 2 && r1[1] != r2[1])
			solve(mid2, R, r1, r2);
		if (valid1 && l2.size() >= 2 && l1[1] != l2[1])
			solve(L, mid1, l1, l2);
	}
}

int find_best(int n) {
	srand(1000000007);
	for (int i=0; i<600; ++i){
		vector<int> cur = ask(i);
		if (cur == ans) return i;
		maxtot = max(maxtot, cur[0] + cur[1]);
	}
	int st = 0, ed = n-1;
	vector<int> cur2, cur3;
	for (; st<n; ++st){
		cur2 = ask(st);
		if (cur2 == ans) return st;
		if (cur2[0] + cur2[1] == maxtot) break;
	}
	for (; ed >= 0; --ed){
		cur3 = ask(ed);
		if (cur3 == ans) return ed;
		if (cur3[0] + cur3[1] == maxtot) break;
	}
	solve(st, ed, cur2, cur3);

	return rekt;
}