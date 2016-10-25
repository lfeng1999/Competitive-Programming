#include <bits/stdc++.h>

using namespace std;

typedef pair<long long,long long> pii;
long long K, N, QQ, Y1[2010], Y2[2010], fac[2010], sfac[2010], seg[4020];
double X;
pii Q[800010];
vector<pii> sortq;
map<pii, long long> mymap;
vector<pair<double,long long>> inter;

void build_tree(int node, int L, int R){
    if (L == R){
        seg[node] = inter[L].second;
        return;
    }
    build_tree(node*2,L,(L+R)/2);
    build_tree(node*2+1,(L+R)/2+1,R);
    seg[node] = max(seg[node*2], seg[node*2+1]);
}

long long query(int node, int L, int R, int LL, int RR){
    if (L > RR || R < LL) return 0;
    if (LL <= L && R <= RR) return seg[node];
    int mid = (L+R)/2;
    if (RR <= mid) return query(node*2,L,mid,LL,RR);
    else if (mid < LL) return query(node*2+1,mid+1,R,LL,RR);
    else{
        return max(query(node*2,L,mid,LL,RR), query(node*2+1,mid+1,R,LL,RR));
    }
}

int main()
{
    //freopen("solar-1a.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(NULL);
    cin >> X >> K >> N >> QQ;
    for (int i=0; i!=N; ++i)
        cin >> Y1[i] >> Y2[i] >> fac[i];
    for (int i=0; i!=QQ; ++i){
        cin >> Q[i].first >> Q[i].second;
        Q[i].first--;
        sortq.push_back(Q[i]);
    }
    sort(sortq.begin(), sortq.end());

    int cnt = 0;
    for (int f1 = 0; f1!=N; ++f1){
        if (sortq[cnt].first!=f1 || cnt == sortq.size()) continue;
        long long factor = 0;
        for (int f2=0; f2!=N; ++f2)
            if (Y1[f2] > Y1[f1])
                factor+=fac[f2];
        inter.clear();
        inter.push_back(make_pair(0,factor));
        for (int f2 = 0; f2!=N; ++f2){
            if (f1 == f2) continue;
            if (!((Y1[f1] > Y1[f2] && Y2[f1] < Y2[f2]) || (Y1[f1] < Y1[f2] && Y2[f1] > Y2[f2]))) continue;
            double m1,m2,b1,b2,x, xInter;
            m1 = (Y2[f1] - Y1[f1])/X; b1 = Y1[f1];
            m2 = (Y2[f2] - Y1[f2])/X; b2 = Y1[f2];
            if (m1 == m2) continue;
            xInter = (b2-b1)/(m1-m2);
            inter.push_back(make_pair(xInter, f2));
        }
        sort(inter.begin(), inter.end());
        unordered_map<double, long long> fmlMap;
        for (int i=0; i!=inter.size(); ++i){
            long long mFact = inter[i].second;
            if (i == 0) {fmlMap[inter[i].first] = factor; continue;}
            if (Y1[f1] > Y1[mFact])
                factor+=fac[mFact];
            else
                factor-=fac[mFact];
            fmlMap[inter[i].first] = factor;
        }
        inter.clear();
        for (auto x : fmlMap){
            inter.push_back(x);
        }
        sort(inter.begin(), inter.end());
        build_tree(1,0,inter.size()-1);
        while(cnt < sortq.size() && sortq[cnt].first == f1){
            double xval = (double)sortq[cnt].second;
            int Lpos = lower_bound(inter.begin(), inter.end(), make_pair(xval,(long long)-1e10)) - inter.begin();
            int Rpos = upper_bound(inter.begin(), inter.end(), make_pair(xval + K - 0.0000000001,(long long)-1e10)) - inter.begin();
            if (inter[Lpos].first!=xval) Lpos--;
            Rpos--;
            mymap[sortq[cnt]] = query(1,0, inter.size()-1, Lpos, Rpos);
            cnt++;
        }
    }
    for (int i=0; i!=QQ; ++i)
        printf("%lld\n",mymap[Q[i]]);
    return 0;
}
