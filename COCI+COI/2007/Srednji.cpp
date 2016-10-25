#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MIDDLE = 100000;
int N, B, arr[100010], lef[200010], rig[200010];

int main()
{
    //freopen("COCI.in","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> N >> B;

    for (int i=0; i < N; ++i){
        cin >> arr[i];
    }
    int pos = find(arr, arr + N, B) - arr;

    int cur = 0;
    for (int i = pos; i >= 0; --i){
        if (arr[i] < B) cur--;
        else if (arr[i] == B) cur = cur;
        else if (arr[i] > B) cur++;
        lef[MIDDLE + cur]++;
    }
    cur = 0;
    for (int i = pos; i < N; ++i){
        if (arr[i] < B) cur--;
        else if (arr[i] == B) cur = cur;
        else if (arr[i] > B) cur++;
        rig[MIDDLE + cur]++;
    }

    ll ans = 0;
    for (int i = -N; i <= N; i++){
        ans += lef[MIDDLE + i] * rig[MIDDLE - i];
    }
    cout << ans;



    return 0;
}
