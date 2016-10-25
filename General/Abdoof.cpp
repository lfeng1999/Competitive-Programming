#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> B{"a","e","i","oo"}, A{"ch","t","m","d","bd","b","r"}, C{"n", "v", "f"};
string ss;
int nptr = 0;

string nextstr(){
    string x = "";
    int sptr = nptr;
    for (; sptr < ss.length(); ++sptr){
        if (ss[sptr] == ' '){
            sptr++;
            break;
        }
        x+=tolower(ss[sptr]);
    }
    nptr = sptr;
    return x;
}

bool is_possible_B(string x);
bool is_possible_C(string x){
    for (string y : C){
        if (x == y){
            return true;
        }
    }
    return false;
}

bool is_possible_A(string x){
    if (x.length() == 1){
        bool flag = is_possible_C(x);
        if (flag) return true;
        for (string y : A){
            if (y.length() == x.length() && x.substr(0, y.length()) == y){
                return true;
            }
        }
        return false;
    }
    else if (x.length() == 2){
        if  (x == "bd" || x == "ch") return true;
    }
    for (string y : A){
        if (x.substr(0, y.length()) == y){
            return is_possible_B(x.substr(y.length(), x.length()));
        }
    }
    return false;
}
bool is_possible_B(string x){
    if (x.length() == 1) return is_possible_C(x);
    for (string y : B){
        if (x.substr(0, y.length()) == y){
            return is_possible_A(x.substr(y.length(), x.length()));
        }
    }
    return false;
}

int main()
{
//    freopen("Mac.txt","r",stdin);
    getline(cin, ss);
    bool flag = true;
    int cnt = 0;
    while (true){
        cnt++;
        string x = nextstr();
        if (x.length() < 2){
            flag = false;
            break;
        }
        flag = (is_possible_A(x) || is_possible_B(x));
        if (!flag || nptr == ss.length()) break;
    }

    if (!flag || cnt < 2){
        printf("invalid\n");
    }
    else{
        printf("valid\n");
    }
    return 0;
}