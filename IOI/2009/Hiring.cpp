#include <bits/stdc++.h>

using namespace std;

struct candidate
{
    double s, q, r;
    int id;
    bool operator <(const candidate &a) const{
        return r < a.r;
    }
}C[500010];
int N,W;


int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> W;
    for (int i=0; i!=N; ++i){
        cin >> C[i].s >> C[i].q;
        C[i].r = C[i].s/C[i].q;
        C[i].id = i+1;
    }
    sort(C,C+N);
    double totalQ = 0, bestCost;
    int lim = 0, bestsz = 0, bestIndex;
    vector<int> Q;
    for (int i=0; i!=N; ++i){
        Q.push_back(C[i].q);
        push_heap(Q.begin(),Q.end());
        totalQ+=C[i].q;
        double maxQ = W/C[i].r;
        while (totalQ > maxQ){
            totalQ -= Q[0];
            pop_heap(Q.begin(),Q.end());
            Q.pop_back();
        }
        int sz = Q.size();
        double totalCost = totalQ*C[i].r;
        if (sz > bestsz || (sz == bestsz && totalCost < bestCost)){
            bestIndex = i;
            bestCost = totalCost;
            bestsz = sz;
        }
    }

    vector<pair<double,int>> Q2;
    for (int i=0; i<=bestIndex; ++i){
        Q2.push_back(make_pair(C[i].q, C[i].id));
        push_heap(Q2.begin(),Q2.end());
    }
    while (Q2.size()!=bestsz){
        pop_heap(Q2.begin(),Q2.end());
        Q2.pop_back();
    }
    printf("%d\n",Q2.size());
    for (int i=0; i!=Q2.size(); ++i){
        printf("%d\n",Q2[i].second);
    }


    return 0;
}
