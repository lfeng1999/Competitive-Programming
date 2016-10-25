#include <bits/stdc++.h>

using namespace std;

vector<string> subjects, verbs, objects;

int main()
{
    //freopen("CCC.txt","r",stdin);
    int QQ;
    cin >> QQ;
    while (QQ--){
        subjects.clear();
        verbs.clear();
        objects.clear();
        int S, V, Ob;
        cin >> S >> V >> Ob;
        cin.ignore();
        for (int i=0; i<S; ++i){
            string s;
            getline(cin, s);
            subjects.push_back(s);
        }
        for (int i=0; i<V; ++i){
            string s;
            getline(cin, s);
            verbs.push_back(s);
        }
        for (int i=0; i<Ob; ++i){
            string s;
            getline(cin, s);
            objects.push_back(s);
        }
        for (string subject : subjects){
            for (string verb : verbs){
                for (string object : objects){
                    printf("%s %s %s.\n", subject.c_str(), verb.c_str(), object.c_str());
                }
            }
        }
        printf("\n");
    }
    return 0;
}
