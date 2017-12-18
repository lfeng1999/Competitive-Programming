#include <bits/stdc++.h>

using namespace std;

struct Elephant{
	int pos, nxt, cnt;
	bool operator < (const Elephant &a) const{
		return pos < a.pos;
	}
};

Elephant buckets[400][900];
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
void add_bucket(int i, int pos){
	int fnd = -1;
	for (int j=0; j<size[i]; ++j){
		if (buckets[i][j].pos <= pos) fnd = j;
	}
	++fnd;
	for (int j=size[i] + 1; j > fnd; --j){
		buckets[i][j] = buckets[i][j-1];
	}
	size[i]++;
	buckets[i][fnd].pos = pos;
	bucket_setup(i);
	//bucket #, index, and pos/val
}
void rem_bucket(int i, int pos){
	int fnd = 0;
	for (int j=0; j<size[i]; ++j){
		if (buckets[i][j].pos == pos) fnd = j;
	}
	for (int j=fnd; j<size[i]; ++j) buckets[i][j] = buckets[i][j+1];
	size[i]--;
	bucket_setup(i);
	//bucket #, index
}
int find_bucket(int pos){
	for (int i=0; i<nblocks; ++i){
		if (size[i] == 0) continue;
		// cout << i << " " << size[i] << endl;
		if (buckets[i][0].pos <= pos && pos <= buckets[i][size[i] - 1].pos) return i;
	}
	for (int i=0; i<nblocks; ++i){
		if (size[i] == 0) continue;
		if (buckets[i][0].pos > pos) return i;
	}
	for (int i = nblocks - 1; i >= 0; --i){
		if (size[i] == 0) continue;
		return i;
	}
}

int query(){
	int cur;
	for (int i=0; i<nblocks; ++i){
		if (size[i] != 0){
			cur = buckets[i][0].pos;
			break;
		}
	}
	int ret = 0;
	for (int i=0; i<nblocks; ++i){
		if (size[i] == 0) continue;
		Elephant tmp = {cur + clen, 0, 0};
		int np = upper_bound(buckets[i], buckets[i] + size[i] + 1, tmp) - buckets[i];
		if (np == size[i]) continue;
		ret++;
		ret += buckets[i][np].cnt;
		cur = buckets[i][np].pos;
		if (buckets[i][np].nxt != size[i])
			cur = buckets[i][buckets[i][np].nxt].pos;
	}
	return ret + 1;
}
void update(int i, int pos){
	int oid = find_bucket(ele[i]);
	rem_bucket(oid, ele[i]);
	ele[i] = pos;
	int nid = find_bucket(ele[i]);
	add_bucket(nid, ele[i]);
	qcnt--;
}

void trace(){
	for (int i=0; i<nblocks; ++i){
		cout << "BLOCK #" << i << ": ";
		for (int j=0; j<size[i]; ++j){
			cout << buckets[i][j].pos << ", ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	// freopen("test2.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
	cin >> n >> clen >> m;
	bsize = sqrt(n);
	nblocks = (n-1)/bsize + 1;

	for (int i=0; i<n; ++i){
		cin >> ele[i];
		arr[i] = ele[i];
	}
	set_buckets();
	bucket_clear();
	qcnt = sqrt(m);
	for (int qq=0; qq<m; ++qq){ //fix it for sqrt(n) later.
		int i, pos; cin >> i >> pos;

		if (qcnt == 0){
			bucket_clear();
			qcnt = sqrt(m);
		}
		update(i, pos);

		cout << query() << '\n';
	}
	return 0;
}