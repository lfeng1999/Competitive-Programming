#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.sync_with_stdio(0); cin.tie(0);
    int a,b;
    cin >> a >> b;
    pair<int,int> p = make_pair(a,b);
    pair<int,int> d = make_pair(2,18);
    if (p == d)
        cout << "Special";
    else if (p < d)
        cout << "Before";
    else
        cout << "After";
    return 0;
}
