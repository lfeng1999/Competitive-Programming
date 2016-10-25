#include <bits/stdc++.h>

using namespace std;

int my_exp[10];
map<pair<int,int>, int> M;
unordered_map<int,int> M2;

int fsolve(int n, int v);

int csolve(int n){
    if (n == 0) return 0;
    if (M2.count(n)) return M2[n];
    int logn = log10(n);
    int dig = n/my_exp[logn];
    int ans = csolve(my_exp[logn]-1); //abcd -> 999

    if (dig == 9){
        ans += n - dig*my_exp[logn]+1; //a0000 -> abcde
    }

    ans+=(dig-1)*fsolve(my_exp[logn], 9);

    int newn = n - dig*my_exp[logn];
    return M2[n] = ans + csolve(newn);
}

int rsolve(int n, int v){
    if (n == 0) return 0;
    if (M.count(make_pair(n,v))) return M[make_pair(n,v)];
    int logn = log10(n);
    int dig = n/my_exp[logn];
    int ans = csolve(my_exp[logn]-1); //abcd -> 999

    if (dig > v){
        ans += my_exp[logn]; //abcdeg > f00000
    }
    else if (dig == v){
        ans += n - dig*my_exp[logn]+1; //a0000 -> abcde
    }

    ans+=(dig-1)*fsolve(my_exp[logn], v);

    int newn = n - dig*my_exp[logn];
    return M[make_pair(n,v)] = ans + rsolve(newn, v);
}

int fsolve(int n, int v){
    int LOGN = log10(n);
    int ans = LOGN*my_exp[LOGN]/10;
    return ans;
}

int digitcount(int n){
    if (n == 0) return 0;
    int LOGN = log10(n);
    int ans = 0;
    for (int i=LOGN; i>=0; --i){
        int idigitnumbers = n-my_exp[i]+1;
        ans += (i+1)*idigitnumbers;
        n-=idigitnumbers;
    }
    return ans;
}

int main()
{
//    freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    my_exp[0] = 1;
    for (int i=1; i<10; ++i) my_exp[i] = my_exp[i-1]*10;
    int R, L;
    while (T--){
        cin >> L >> R;
        int ans[10], tot;
        for (int i=1; i<10; ++i){
            ans[i] = rsolve(R,i) - rsolve(L-1,i);
        }
        tot = digitcount(R) - digitcount(L-1);
        for (int i=1; i<10; ++i) tot -= ans[i];
        cout << tot << ' ';
        for (int i=1; i<10; ++i){
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}