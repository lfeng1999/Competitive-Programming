#include <bits/stdc++.h>

using namespace std;

unordered_map<char,int> mmap;
string a,b;

int main()
{
    cin >> a >> b;
    for (int i=0; i!=a.length(); ++i)
        mmap[a[i]]++;
    for (int i=0; i!=b.length(); ++i)
        mmap[b[i]]++;
    for (auto x : mmap)
    if (x.second%2 == 1)
    {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;

}
