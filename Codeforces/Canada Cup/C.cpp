#include <bits/stdc++.h>

using namespace std;

int used[26];
char grid[2][14];

int main(){
	//freopen("CF.txt","r",stdin);
	cin.sync_with_stdio(0); cin.tie(0);
    string S;
    cin >> S;
    for (int i=0; i<S.length(); ++i){
        used[S[i] - 'A']++;
    }
    char dupe;
    for (int i=0; i<26; ++i){
        if (used[i] == 2){
            dupe = (i+'A');
        }
    }
    int dupepos = S.find(dupe);
    string nS = S.substr(dupepos, 27 - dupepos) + S.substr(0, dupepos);

    int mlen = 0;
    for (int i=1; i<S.length(); ++i){
        if (nS[i] == dupe){
            mlen = i - 1;
        }
    }
    if (nS[0] == nS[1]){
        cout << "Impossible";
        return 0;
    }
    if (mlen%2 == 1){
        grid[0][(mlen+1)/2] = dupe;
        int j = 1;
        for (int i = (mlen+1)/2 - 1; i >= 1; --i){
            grid[0][i] = nS[j];
            j++;
        }
        for (int i = 1; i <= (mlen+1)/2; ++i){
            grid[1][i] = nS[j];
            j++;
        }
        j++;
        for (int i = (mlen+1)/2+1; i <= 13; ++i){
            grid[0][i] = nS[j];
            j++;
        }
        for (int i = 13; i >= (mlen+1)/2+1; --i){
            grid[1][i] = nS[j];
            j++;
        }
    }
    else{
        grid[0][mlen/2 + 1] = dupe;
        int j = 1;


        for (int i = mlen/2; i >= 1; --i){
            grid[0][i] = nS[j];
            j++;
        }
        for (int i = 1; i <= mlen/2; ++i){
            grid[1][i] = nS[j];
            j++;
        }
        j++;
        for (int i = mlen/2+2; i <= 13; ++i){
            grid[0][i] = nS[j];
            j++;
        }
        for (int i = 13; i >= mlen/2+1; --i){
            grid[1][i] = nS[j];
            j++;
        }
    }


    for (int i=1; i<=13; ++i){
        cout << grid[0][i];
    }
    cout << '\n';
    for (int i=1; i<=13; ++i){
        cout << grid[1][i];
    }

	return 0;
}