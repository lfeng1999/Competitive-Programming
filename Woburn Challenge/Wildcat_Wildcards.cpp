#include <bits/stdc++.h>

using namespace std;

int cons[6], vow[2], let[8];
int wild[3];

void addcons(){
    if (wild[1] >= cons[1] - cons[0]){
        wild[1]-=cons[1]-cons[0];
        cons[0]+=cons[1]-cons[0];
    }
    else {cons[0]+=wild[1]; wild[1] = 0; return;}
    for (int i=2; i<6; ++i){
        if (wild[1] >= i*(cons[i]-cons[i-1])){
            wild[1] -= i*(cons[i]-cons[i-1]);
            for (int j=0; j<i; ++j){
                cons[j]+=cons[i]-cons[i-1];
            }
        }
        else{
            for (int j=0; j<i; ++j){
                cons[j]+= wild[1]/i;
            }
            wild[1]-= i*(int)(wild[1]/i);
            for (int j=0; j<wild[1]; ++j){
                cons[j]++;
            }
            wild[1] = 0;
            return;
        }
    }
    if (wild[1]){
        for (int i=0; i<6; ++i){
            cons[i] += wild[1]/6;
        }
        wild[1]-=6*((int)wild[1]/6);
        for (int i=0; i<wild[1]; ++i) cons[i]++;
    }
}
void addlet(){
    if (wild[2] >= let[1] - let[0]){
        wild[2]-=let[1]-let[0];
        let[0]+=let[1]-let[0];
    }
    else {let[0]+=wild[2]; wild[2] = 0; return;}
    for (int i=2; i<8; ++i){
        if (wild[2] >= i*(let[i]-let[i-1])){
            wild[2] -= i*(let[i]-let[i-1]);
            for (int j=0; j<i; ++j){
                let[j]+=let[i]-let[i-1];
            }
        }
        else{
            for (int j=0; j<i; ++j){
                let[j]+= wild[2]/i;
            }
            wild[2]-= i*(int)(wild[2]/i);
            for (int j=0; j<wild[2]; ++j){
                let[j]++;
            }
            wild[2] = 0;
            return;
        }
    }
    if (wild[2]){
        for (int i=0; i<8; ++i){
            let[i] += wild[2]/8;
        }
        wild[2]-=8*((int)wild[2]/8);
        for (int i=0; i<wild[2]; ++i) let[i]++;
    }
}

int main()
{
    //freopen("WoburnChallenge.txt","r",stdin);
    cin.sync_with_stdio(0); cin.tie(0);
    int cnt = 0,cnt2 = 0;
    for (int i=0; i<8; ++i) {
        if (i!=1 && i!=5)cin >> cons[cnt2++];
        else cin >> vow[cnt++];
    }
    for (int i=0; i<3; ++i) cin >> wild[i];
    sort(vow, vow+2);
    sort(cons,cons+6);
    if (wild[0] >= vow[1]-vow[0]){
        wild[0]-=vow[1]-vow[0];
        vow[0]+=vow[1]-vow[0];
        vow[0]+= wild[0]/2;
        vow[1]+=wild[0] - wild[0]/2;
    }
    else {vow[0]+=wild[0]; wild[0] = 0;}
    if (wild[0]){
        for (int i=0; i<2; ++i){
            let[i] += wild[0]/2;
        }
        wild[0]-=2*((int)wild[0]/2);
        for (int i=0; i<wild[0]; ++i) vow[i]++;
    }
    addcons();
    for (int i=0; i<6; ++i) let[i] = cons[i];
    for (int i=0; i<3; ++i) let[i+6] = vow[i];
    //for (int i=0; i<6; ++i) cout << cons[i] << endl;
    sort(let, let+8);
    addlet();
    cout << *min_element(let, let+8);
    return 0;
}
