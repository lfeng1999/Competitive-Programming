#include <bits/stdc++.h>

using namespace std;

long long fib[51];

void recur(long long cnt, int fibn, int add)
{
    if (cnt < 0){
        return;
    }
    if (cnt == 1){
        for (; add!=fibn; ++add){
            cout << add+1 << " ";
        }
        return;
    }
    if (cnt <= fib[fibn-add-1]){
        cout << add+1 << " ";
        recur(cnt,fibn,add+1);
    }
    else{
        cout << add+2 << " " << add+1 << " ";
        recur(cnt-fib[fibn-add-1],fibn,add+2);
    }
}

int main()
{
    fib[0] = fib[1] = 1;
    for (int i=2; i!=51; ++i){
        fib[i] = fib[i-1] + fib[i-2];
    }
    long long n, k;
    cin >> n >> k;
    recur(k,n,0);
    return 0;
}