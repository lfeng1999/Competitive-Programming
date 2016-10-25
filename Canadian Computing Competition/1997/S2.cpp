#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("CCC.txt","r",stdin);
    int QQ;
    cin >> QQ;
    while (QQ--){
        int N;
        cin >> N;
        vector<pair<int,int>> facts;
        for (int i=1; i<=sqrt(N); ++i){
            if (N%i == 0){
                facts.push_back(make_pair(i, N/i));
            }
        }
        bool flag = false;
        for (int i=0; i<facts.size(); ++i){
            for (int j=0; j<facts.size(); ++j){
                if (facts[i].first + facts[i].second == facts[j].second - facts[j].first){
                    flag = true;
                }
                if (facts[i].second - facts[i].first == facts[j].first + facts[j].second){
                    flag = true;
                }
            }
        }
        if (flag){
            printf("%d is nasty\n", N);
        }
        else{
            printf("%d is not nasty\n", N);
        }
    }
    return 0;
}
