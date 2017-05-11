#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define long long long
#define f1(i,n) for (int i=1; i<=n; i++)
#define f0(i,n) for (int i=0; i<n; i++)

#define N 1000006
int Peak=2, Head=1, Tail=2;
int Next[20][N], Prev[20][N];
int Sum[N], Count[N], Level[N];
#define k(u) Next[k][u]

void init(){
	Level[Head]=Level[Tail]=20;
	Count[Tail]=1; Sum[Head]=0;
	f0(k,20) Next[k][Head]=Tail;
	f0(k,20) Prev[k][Tail]=Head;
}

int parent(int u)
	{ return Next[Level[u]-1][u]; }
	
int create(int Value){
	int u=++Peak;
	do { Level[u]++; } while (rand()&1 && Level[u]<20);
	Sum[u]=Value; Count[u]=1;
	return u;
}

void assume(int u, int DSum, int DCount){
	for (int i=parent(u); i; i=parent(i))
	{ Sum[i]+=DSum, Count[i]+=DCount; }
}

void connect(int x, int y, int z, int k){
	Next[k][x]=y; Prev[k][y]=x;
	Next[k][y]=z; Prev[k][z]=y;
}

int at(int x, int Last[20]=NULL) {
	int u=Head, OldX=x; bool Changed=false;
	for (int k=19; k>=0; k--) {
		while (k(u) && Count[k(u)]<=x) { u=k(u); Changed=true; }
		if (Changed) { x-=Count[u]; Changed=false; }
		if (Last) Last[k]=u;
	}
	return u;
}

void insert(int x, int Value){
	int Last[20]={}, u=at(x-1, Last);
	int v=create(Value);
	#define lk Last[k]
	f0(k,Level[v]) if (k==Level[lk]-1) assume(lk, -Sum[lk], -Count[lk]);
	f0(k,Level[v]) connect(lk, v, k(lk), k);
	f0(k,Level[v]) if (k==Level[lk]-1) assume(lk, Sum[lk], Count[lk]);
	assume(v, Value, 1);
}

int sum_range(int x){
	int Last[20]={}, OldLast=-1, Total=0;
	at(x, Last);
	f0(k,20) if (Last[k]!=OldLast) 
	{ Total+=Sum[Last[k]]; OldLast=Last[k]; }
	return Total;
}

int sum_range(int x, int y)
	{ return sum_range(y) - sum_range(x-1); }

main(){
	init();
	int c, x, y;
	while (cin >> c >> x >> y) {
		if (c==1) insert(x, y);
		if (c==2) cout << sum_range(x,y) << endl;
	}
}