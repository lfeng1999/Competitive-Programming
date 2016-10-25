#include <bits/stdc++.h>

using namespace std;

int main()
{
    //freopen("CCC.txt","r",stdin);
    int QQ;
    cin >> QQ;
    while (QQ--){
        string S;
        cin >> S;
        cout << S;
        int tot = 0;
        int i = 0;
        while (S[i]!='='){
            char c1 = S[i], c2 = S[i+1];

            if (c1 == 'M') tot+=1000;
            else if (c1 == 'D') tot+=500;
            else if (c1 == 'C' && c2 == 'M'){
                tot += 900;
                i++;
            }
            else if (c1 == 'C' && c2 == 'D'){
                tot += 400;
                i++;
            }
            else if (c1 == 'C') tot += 100;
            else if (c1 == 'X' && c2 == 'C'){
                tot += 90;
                i++;
            }
            else if (c1 == 'L') tot += 50;
            else if (c1 == 'X' && c2 == 'L'){
                tot += 40;
                i++;
            }
            else if (c1 == 'X') tot += 10;
            else if (c1 == 'V') tot += 5;
            else if (c1 == 'I' && c2 == 'X'){
                tot+=9;
                i++;
            }
            else if (c1 == 'I' && c2 == 'V'){
                tot+=4;
                i++;
            }
            else if (c1 == 'I') tot += 1;

            i++;
        }
        if (tot > 1000){
            cout << "CONCORDIA CUM VERITATE\n";
            continue;
        }
        while (tot > 0){
            if (tot >= 1000){
                cout << "M";
                tot-=1000;
            }
            else if (tot >= 900){
                cout << "CM";
                tot-=900;
            }
            else if (tot >= 500){
                cout << "C";
                tot-=500;
            }
            else if (tot >= 400){
                cout << "CD";
                tot-=400;
            }
            else if (tot >= 100){
                cout << "C";
                tot-=100;
            }
            else if (tot >= 90){
                cout << "XC";
                tot-=90;
            }
            else if (tot >= 50){
                cout << "L";
                tot-=50;
            }
            else if (tot >= 40){
                cout << "XL";
                tot-=40;
            }
            else if (tot >= 10){
                cout << "X";
                tot-=10;
            }
            else if (tot >= 9){
                cout << "IX";
                tot-=9;
            }
            else if (tot >= 5){
                cout << "V";
                tot-=5;
            }
            else if (tot >=4){
                cout << "IV";
                tot-=4;
            }
            else if (tot >= 1){
                cout << "I";
                tot-=1;
            }
        }
        cout << "\n";
    }

    return 0;
}
