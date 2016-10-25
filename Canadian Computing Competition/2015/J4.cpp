#include <bits/stdc++.h>

using namespace std;

map<int,int> wt;
int tim[110];

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int M, cur = 0;
    cin >> M;
    for (int i=0; i<M; ++i){
        char ch; int x; cin >> ch >> x;
        if (wt.count(x) == 0 && ch!='W') wt[x] = 0;
        if (ch == 'R'){
            tim[x] = ++cur;
        }
        else if (ch == 'S'){
            wt[x] += ++cur - tim[x];
            tim[x] = 0;
        }
        else{
            cur+=x-1;
        }
    }
    for (auto pii : wt){
        if (pii.second && !tim[pii.first])
            cout << pii.first << " " << pii.second << endl;
        else
            cout << pii.first << " -1" << endl;
    }
    return 0;
}
