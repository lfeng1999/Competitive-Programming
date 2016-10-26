#include <bits/stdc++.h>

using namespace std;

map<int,int> counter;

int GCD(int a, int b){
    if (b == 0){
        return a;
    }
    return GCD(b, a%b);
}

int main()
{
//    freopen("IOI.txt","r",stdin);
    int N;
    cin >> N;
    for (int i=0; i!=N*N; ++i){
        int a;
        cin >> a;
        counter[a]++;
    }
    vector<int> nm;
    map<int,int>::reverse_iterator iter = counter.rbegin();
    for (; iter!=counter.rend(); ++iter){
        if (iter->second == 0){
            continue;
        }
        int cnt = 0, add = 1;
        while (iter->second){
            iter->second-=add;
            add+=2;
            for (int x : nm){
                counter[GCD(x,iter->first)] -= 2;
            }
            cnt++;
        }
        for (int i=0; i!=cnt; ++i){
            nm.push_back(iter->first);
        }
    }
    for (int x : nm){
        cout << x  << " ";
    }
    return 0;
}