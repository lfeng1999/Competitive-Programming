#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct Line{
    int M, B;
    int idx;
    bool operator < (const Line &x) const{
        if (M < x.M) return true;
        else if (M == x.M && B > x.B) return true;
        return false;
    }
}lines[100010];
vector<Line> L;
int ans[500010];
bool past_slopes[1010];

bool bad(int l1, int l2, int l3){
    return (L[l1].B-L[l3].B)*(L[l2].M - L[l1].M) < (L[l1].B-L[l2].B)*(L[l3].M-L[l1].M);
}

void add(Line &x){
    L.push_back(x);
    while (L.size() >= 3 && bad(L.size()-3, L.size()-2, L.size()-1)){
        L.erase(L.end()-2);
    }
}

int main()
{
    //freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N, QQ;
    cin >> N >> QQ;
    for (int i=0; i<N; ++i){
        cin >> lines[i].B >> lines[i].M;
        lines[i].idx = i;
    }
    sort(lines, lines+N);

    for (int i=0; i<N; ++i){
        if (past_slopes[lines[i].M]) continue;
        add(lines[i]);
        past_slopes[lines[i].M] = true;
    }
    int pos = L[0].idx, ptr = 0;
    for (int x=0; x <= 500000; ++x){
        if (ptr > 0 && L[ptr].M*x + L[ptr].B != L[ptr-1].M*x + L[ptr-1].B){
            pos = L[ptr].idx;
        }
        while (ptr < L.size()-1 && L[ptr].M*x + L[ptr].B <= L[ptr+1].M*x + L[ptr+1].B){
            if (L[ptr].M*x + L[ptr].B == L[ptr+1].M*x + L[ptr+1].B){
                pos = min(pos, L[ptr+1].idx);
            }
            else{
                pos = L[ptr+1].idx;
            }
            ptr++;
        }
        ans[x] = pos;
    }

    for (int i=0; i<QQ; ++i){
        int Q;
        cin >> Q;
        printf("%d\n",ans[Q]);
    }

    return 0;
}
