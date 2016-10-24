#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("Jumpscotch.txt","r",stdin);
    cin.sync_with_stdio(1);
    cin.tie(0);
    deque<pair<int,int>> Q;
    int N,D,n;
    cin >> N >> D >> n;
    Q.push_back(make_pair(n,0));
    for (int i=1; i!=N; ++i)
    {
        cin >> n;
        while (Q.size() && Q.front().second < i - D)
            Q.pop_front();
        int mval = n + Q.front().first;
        while (Q.size() && Q.back().first >= mval)
            Q.pop_back();
        Q.push_back((make_pair(mval,i)));
    }
    cout << Q.back().first;
}
