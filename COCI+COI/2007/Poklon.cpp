#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

struct Interval{
    int L, R, how = -1, val = 0;

    bool operator < (const Interval &a) const{
        if (L != a.L) return L < a.L;
        return R > a.R;
    }
} interval[100010];

const int MAXN = 1000010;
int bit[1000010], N;

int query(int i){
    int best = -1;

    for (; i > 0; i -= i&(-i)){
        if (bit[i] == -1) continue;
        if (best == -1){
            best = bit[i];
            continue;
        }
        if (interval[bit[i]].val > interval[best].val) best = bit[i];
    }

    return best;
}

void update(int i, int pos){

    for (; i < MAXN; i += i&(-i)){
        if (bit[i] == -1){
            bit[i] = pos;
            continue;
        }
        if (interval[pos].val > interval[bit[i]].val)
            bit[i] = pos;
    }
}

int main(){
//    freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(bit, -1, sizeof(bit));

    cin >> N;
    for (int i=0; i<N; ++i){
        cin >> interval[i].L >> interval[i].R;
    }
    sort(interval, interval + N);

    for (int i = N - 1; i>=0; --i){
        interval[i].how = query(interval[i].R);
        if (interval[i].how != -1)
            interval[i].val = interval[interval[i].how].val + 1;

        update(interval[i].R, i);
    }
    int best_pos = query(MAXN);
    cout << interval[best_pos].val + 1 << endl;
    while (best_pos != -1){
        cout << interval[best_pos].L << " " << interval[best_pos].R << endl;
        best_pos = interval[best_pos].how;
    }

    return 0;
}
