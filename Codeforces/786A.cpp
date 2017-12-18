#include <bits/stdc++.h>

using namespace std;

int N, k1, k2;
int mv1[7010], mv2[7010], w1[7010], w2[7010], l1[7010], l2[7010], end1[7010], end2[7010];
bool past1[7010], past2[7010];
const int WIN = 1, LOSE = 2;

void setwin(int p, int typ){
	if (typ == 1){
		for (int i=0; i<k2; ++i){
			int np = (p - mv2[i] + N)%N;

			l2[np]++; //you're fucked
		}
	}
	else if (typ == 2){
		for (int i=0; i<k1; ++i){
			int np = (p - mv1[i] + N)%N;
			l1[np]++; //you're fucked LMAO
		}
	}
}

void setlose(int p, int typ){ //p is lose position for typ person
	if (typ == 1){
		end1[p] = LOSE; //lost
		for (int i=0; i<k2; ++i){
			int np = (p - mv2[i] + N)%N;
			if (end2[np] != 0) continue;
			setwin(np, 2);
			end2[np] = WIN; //win for p2
		}
	}
	else if (typ == 2){
		end2[p] = LOSE; //lost
		for (int i=0; i<k1; ++i){
			int np = (p - mv1[i] + N)%N;
			if (end1[np] != 0) continue;
			setwin(np, 1);
			end1[np] = WIN; //win for p1
		}
	}
}

int main(){
	freopen("test.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> N;
	cin >> k1;
	for (int i=0; i<k1; ++i){
		cin >> mv1[i];
	}
	cin >> k2;
	for (int i=0; i<k2; ++i){
		cin >> mv2[i];
	}
	setlose(0, 1);
	setlose(0, 2);

	for (int qq=0; qq<N; ++qq){
		for (int i=1; i<N; ++i){
			if (end1[i] == 0 && l1[i] == k1){
				setlose(i, 1);
			}
		}
		for (int i=1; i<N; ++i){
			if (end2[i] == 0 && l2[i] == k2){
				setlose(i, 2);
			}
		}
	}
	// cout << l2[3] << " " << k2 << endl;
	for (int i=1; i<N; ++i){
		if (end1[i] == 0){
			cout << "Loop ";
		}
		else if (end1[i] == 1){
			cout << "Win ";
		}
		else if (end1[i] == 2){
			cout << "Lose ";
		}
	}
	cout << '\n';
	for (int i=1; i<N; ++i){
		if (end2[i] == 0){
			cout << "Loop ";
		}
		else if (end2[i] == 1){
			cout << "Win ";
		}
		else if (end2[i] == 2){
			cout << "Lose ";
		}
	}
	cout << '\n';


	return 0;
}