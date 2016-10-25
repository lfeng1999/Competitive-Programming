#include <bits/stdc++.h>

using namespace std;

struct Candidate{
    double s, q, r;
    int id;
    bool operator < (const Candidate &a){
        return r < a.r;
    }
} workers[500010];

int N;
double W;

int main()
{
    //freopen("IOI.txt", "r", stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N >> W;

    for (int i=0; i<N; ++i){
        cin >> workers[i].s >> workers[i].q;
        workers[i].r = workers[i].s / workers[i].q;
        workers[i].id = i + 1;
    }
    sort(workers, workers+N);

    vector<double> V;
    double bestcost = 0, curqual = 0;
    int bestidx = 0, bestpeople = 0;


    for (int i=0; i<N; ++i){
        V.push_back(workers[i].q);
        push_heap(V.begin(), V.end());
        curqual += workers[i].q;

        while (curqual * workers[i].r > W){
            curqual -= V[0];
            pop_heap(V.begin(), V.end());
            V.pop_back();
        }
        if (V.size() > bestpeople){
            bestpeople = V.size();
            bestcost = curqual * workers[i].r;
            bestidx = i;
        }
        else if (V.size() == bestpeople && bestcost > curqual * workers[i].r){
            bestcost = curqual * workers[i].r;
            bestidx = i;
        }
    }

    vector<pair<double,int>> V2;

    for (int i=0; i<=bestidx; ++i){
        V2.push_back(make_pair(workers[i].q, workers[i].id));
        push_heap(V2.begin(), V2.end());
    }
    while (V2.size() != bestpeople){
        pop_heap(V2.begin(), V2.end());
        V2.pop_back();
    }
    printf("%d\n", bestpeople);

    for (int i=0; i<V2.size(); ++i){
        printf("%d\n", V2[i].second);
    }





    return 0;
}
