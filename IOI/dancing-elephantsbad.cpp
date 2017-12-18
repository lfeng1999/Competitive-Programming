#include <bits/stdc++.h>

using namespace std;

struct Elephant{
	int pos, nxt, cnt;
	bool operator < (const Elephant &a) const{
		return pos < a.pos;
	}
};

Elephant buckets[400][800];
int bsize, nblocks, size[400];
int n, clen, m, arr[150010], ele[150010], qcnt;

void bucket_setup(int i){
	for (int j=0; j<size[i]; ++j){
		buckets[i][j].nxt = size[i];
	}
	buckets[i][size[i]].pos = 1e9 + 10;
	buckets[i][size[i]].cnt = -1; //count of amount of
	buckets[i][size[i]].nxt = size[i]; 
	int r = size[i] - 1;
	for (int l = size[i]-1; l >= 0; --l){
		while (buckets[i][r].pos - buckets[i][l].pos > clen) r--;
		buckets[i][l].cnt = buckets[i][r+1].cnt + 1;


		if (buckets[i][r+1].nxt != size[i])
			buckets[i][l].nxt = buckets[i][r+1].nxt;
		else
			buckets[i][l].nxt = r+1;
	}
}

void set_buckets(){
	int cur = 0;
	for (int i=0; i<nblocks; ++i){
		size[i] = min(bsize, n-i*bsize);
		for (int qq=0; qq<size[i]; ++qq){
			buckets[i][qq].pos = arr[cur++];
		}
	}
}
void bucket_clear(){
	int cur = 0;
	for (int i=0; i<nblocks; ++i){
		for (int j=0; j<size[i]; ++j){
			arr[cur++] = buckets[i][j].pos;
		}
	}
	set_buckets();
	for (int i=0; i<nblocks; ++i){
		bucket_setup(i);
	}
}
void add_bucket(int id, int pos){
	//bucket #, index, and pos/val
}
void rem_bucket(int id, int pos){
	//bucket #, index
}
int find_bucket(int pos){

}

int query(){
	int cur = buckets[0][0].pos;
	int ret = 0;
	for (int i=0; i<nblocks; ++i){
		Elephant tmp = {cur + clen, 0, 0};
		int np = upper_bound(buckets[i], buckets[i] + size[i] + 1, tmp) - buckets[i];
		if (np == size[i]) continue;
		ret++;
		cur = buckets[i][np].pos;
		if (buckets[i][np].cnt == 0) continue;
		ret += buckets[i][np].cnt;
		cur = buckets[i][np].nxt;
	}
	return ret + 1;
}

int main(){
	freopen("test2.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> clen >> m;
	bsize = sqrt(n);
	bsize = 400;
	nblocks = (n-1)/bsize + 1;

	for (int i=0; i<n; ++i){
		cin >> ele[i];
		arr[i] = ele[i];
	}
	set_buckets();
	bucket_clear();
	qcnt = sqrt(m);
	// qcnt = 400;
	for (int qq=0; qq<m; ++qq){ //fix it for sqrt(n) later.
		int i, pos; cin >> i >> pos;



		ele[i] = pos;
		for (int j=0; j<n; ++j){
			arr[j] = ele[j];
		}
		sort(arr, arr + n);
		set_buckets();
		bucket_clear();
		//this shit needs fixing LOL
		// rem_bucket(find_bucket(ele[i]), ele[i]);
		// add_bucket(find_bucket(ele[i]), ele[i]);

		cout << query() << '\n';
	}
	return 0;
}