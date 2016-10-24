#include <bits/stdc++.h>

using namespace std;

const int MAX_TOY = 1000010, MAX_R = 50010;
pair<int,int> toys[MAX_TOY];
int wtorder[MAX_TOY], szorder[MAX_TOY], wtrobot[MAX_R], szrobot[MAX_R], A, B, T;
bool used[MAX_TOY];

bool szsort(const int &a, const int &b){
    return (toys[a].second < toys[b].second);
}

bool wtsort(const int &a, const int &b){
    return (toys[a].first < toys[b].first);
}

bool valid(int mtime){
    memset(used,false,T);
    priority_queue<pair<int,int>> Q;

    int qq = 0;
    for (int i=0; i!=A; ++i){
        for (; qq < T && toys[wtorder[qq]].first < wtrobot[i]; ++qq){
            Q.push(make_pair(toys[wtorder[qq]].second, wtorder[qq]));
        }
        for (int j=0; j < mtime && !Q.empty(); ++j){
            Q.pop();
        }
    }
    for (; qq < T; ++qq){
        Q.push(make_pair(toys[wtorder[qq]].second, wtorder[qq]));
    }
    for (int i=B-1; i>=0; --i){
        for (int j=0; j < mtime && !Q.empty() && Q.top().first < szrobot[i]; ++j){
            Q.pop();
        }
    }
    if (!Q.empty()){
        return false;
    }
    return true;
}

int bin_search(){
    int L = 0, R = MAX_TOY;
    while (L < R){
        int mid = (L+R)/2;
        if (valid(mid)){
            R = mid;
        }
        else{
            L = mid+1;
        }
    }
    return (L < MAX_TOY)?L:-1;
}


int main()
{
    //freopen("IOI.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> A >> B >> T;
    for (int i=0; i!=A; ++i){
        cin >> wtrobot[i];
    }
    for (int i=0; i!=B; ++i){
        cin >> szrobot[i];
    }
    sort(wtrobot, wtrobot+A);
    sort(szrobot, szrobot+B);
    for (int i=0; i!=T; ++i){
        int w,s;
        cin >> w >> s;
        toys[i] = make_pair(w,s);
        wtorder[i]=i;
        szorder[i]=i;
    }
    sort(wtorder, wtorder+T, wtsort);
    sort(szorder, szorder+T, szsort);
//    for (int i=0; i!=T; ++i){
//        cout << wtorder[i] << " " << szorder[i] << endl;
//    }
    cout << bin_search();
    return 0;
}
