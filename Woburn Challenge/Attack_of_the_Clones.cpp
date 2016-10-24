#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;

struct Attack{
    int S, A;
    bool operator < (const Attack &x) const{
        if (S < x.S) return true;
        else if (S == x.S && S%2 == 1){
            return A < x.A;
        }
        else if (S == x.S && S%2 == 0){
            return x.A < A;
        }
        return false;
    }
};

int N, M, R, C;
set<Attack> pos;


int main()
{
    //freopen("Woburn.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> N;
    Attack start;
    start.S = 1; start.A = 1;
    pos.insert(start);
    int tm = 0;
    for (int i=0; i<N; ++i){

        Attack x;
        cin >> x.S >> x.A;
        pos.insert(x);
        auto it = pos.find(x);

        if (it == --pos.end()){
            auto it2 = it;
            --it2;
            Attack x1 = (*it2);
            tm+= abs(x1.S - x.S) + abs(x1.A - x.A);
        }
        else{
            auto it2 = it, it3 = it;
            --it2; ++it3;
            Attack x1 = (*it2), x2 = (*it3);

            bool flag = false;
            if (x1.A <= x.A && x.A <= x2.A){
                flag = false;
            }
            else if (x2.A <= x.A && x.A <= x1.A){
                flag = false;
            }
            else{
                tm+= min(2*abs(x.A - x2.A), 2*abs(x.A - x1.A));
            }
        }
        cout << tm << endl;
    }



    return 0;
}
