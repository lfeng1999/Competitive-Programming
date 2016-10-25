#include <bits/stdc++.h>

using namespace std;

multiset<int> S;

int main()
{
//    freopen("Challenges.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;

    for (int i=0; i<N; ++i){
        int x; cin >> x;
        S.insert(x);
        auto it = S.find(x);
        if (++it!=S.end()){
            S.erase(it);
        }
    }
    cout << S.size() << '\n';
    return 0;
}
