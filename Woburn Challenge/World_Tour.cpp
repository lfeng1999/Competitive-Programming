#include <bits/stdc++.h>

using namespace std;

int N, dest[500010], cur_cycle = 0, cur_begin, cycle_size[500010], time_found[500010], my_cycle[500010], cdist[500010];
bool past[500010];

void make_cycle(int v, int cur){

    if (past[v]){
        cur_begin = time_found[v];
        return;
    }

    past[v] = true;
    time_found[v] = cur;

    make_cycle(dest[v], cur + 1);

    if (cur >= cur_begin){
        cycle_size[cur_cycle]++;
        my_cycle[v] = cur_cycle;
    }

    time_found[v] = 1e9;
}

void dfs(int v){
    if (past[v] || my_cycle[v] != -1){
        return;
    }
    past[v] = true;
    dfs(dest[v]);
//    cout << v << " " << dest[v] << endl;
    cdist[v] = cdist[dest[v]] + 1;

}


int main()
{
//    freopen("WoburnChallenge.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    memset(my_cycle, -1, sizeof(my_cycle));
    cin >> N;
    for (int i=0; i<N; ++i){
        int v; cin >> v; v--;
        dest[i] = v;
    }

    for (int i = 0; i < N; ++i){
        cur_begin = 1e9;
        if (!past[i]){
            make_cycle(i, 0);
            cur_cycle++;
        }
    }
    memset(past, false, sizeof(past));

    for (int i = 0; i < N; ++i){
        if (my_cycle[i] != -1){
//            cout << i << " " << my_cycle[i] << endl;
            cdist[i] = cycle_size[my_cycle[i]];
        }
    }
    for (int i = 0; i < N; ++i){
        dfs(i);
        cout << cdist[i] << "\n";
    }

    return 0;
}
