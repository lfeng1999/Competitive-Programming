#include <bits/stdc++.h>

using namespace std;

int N,M, pos[2010], ppos[2010];

struct Row{
    int row[5010];
    bool operator <(const Row &a) const{
        return lexicographical_compare(row, row+M, a.row, a.row+M);
    }
};

vector<Row> graph;

bool psort(int &a, int &b){
    return (graph[a] < graph[b]);
}

int main()
{
    //freopen("SAO.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i=0; i!=N; ++i){
        graph.push_back(Row());
        ppos[i] = pos[i] = i;
        for (int j=0; j!=M; ++j){
            char a;
            cin >> a;
            graph[i].row[j] = a-48;
        }
    }
    sort(pos, pos+N, psort);
    sort(graph.begin(), graph.end());
    for (int i=0; i!=N; ++i){
        ppos[pos[i]] = i;
    }
    int nQ;
    cin >> nQ;
    for (int qq=0; qq!=nQ; ++qq){
        int L, R, minp = 100000, maxp = 0;
        cin >> L >> R;
        L--;
        R--;
        for (int i=L; i<=R; ++i){
            minp = min(minp, ppos[i]);
            maxp = max(maxp, ppos[i]);
        }
        int maxr = 0;
        for (; maxr < M; ++maxr){
            if (graph[minp].row[maxr]!=graph[maxp].row[maxr])
                break;
        }
        swap(pos[ppos[L]], pos[ppos[R]]);
        swap(ppos[L], ppos[R]);
        printf("%d\n",maxr*(R-L+1));
    }
    return 0;
}
