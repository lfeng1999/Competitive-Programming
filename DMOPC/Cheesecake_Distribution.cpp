#include <bits/stdc++.h>

using namespace std;

long long arr[100010];

int main()
{
    //freopen("DMOPC.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int N;
    cin >> N;
    long long tot = 0;
    for (int i=0; i<N; ++i){
        cin >> arr[i];
        tot+=arr[i];
    }
    if (tot%N != 0){
        cout << "Impossible";
        return 0;
    }
    long long avg = tot/N;
    long long diff = 0;
    for (int i=0; i<N; ++i){
        diff+= abs(arr[i]-avg);
    }
    cout << diff/2;

    return 0;
}
