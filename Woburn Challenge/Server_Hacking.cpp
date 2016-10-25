#include <bits/stdc++.h>

using namespace std;

bool isprime[31623];
int primes[4000], nprime, value[100010];

vector<int> factorize(int idx){
    int v = value[idx];
    vector<int> V;
    for (int i=0; i<nprime; ++i){
        int nprime = 0;
        while (v % primes[i] == 0){
            v/=primes[i];
            nprime++;
        }
        if (nprime != 0){
            V.push_back(primes[i]);
            V.push_back(nprime);
        }
    }
    if (v != 1){
        V.push_back(v);
        V.push_back(1);
    }
    return V;
}


int main()
{
//    freopen("CCO.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    memset(isprime, true, sizeof(isprime));

    isprime[0] = isprime[1] = false;

    for (int i=2; i<31623; ++i){
        if (isprime[i]){
            for (int j = i; i*j < 31623; ++j){
                isprime[i*j] = false;
            }
        }
    }
    for (int i = 0; i < 31623; ++i){
        if (isprime[i]){
            primes[nprime++] = i;
        }
    }

    int N;
    cin >> N;

    for (int i=0; i<N; ++i){
        cin >> value[i];
    }

    int L = 0, R = N - 1;

    while (L < R){
        int mid = (L+R)/2;
        if (factorize(mid) < factorize(mid+1)){
            R = mid;
        }
        else{
            L = mid + 1;
        }
    }
    cout << L + 1;


    return 0;
}
