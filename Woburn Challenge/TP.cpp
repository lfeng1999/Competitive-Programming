#include <bits/stdc++.h>

using namespace std;

double prob[2010][4010];

int main(){
    //freopen("WC.txt","r",stdin);
    int N, M;
    cin >> N >> M;
    //npasses, nhouses
    prob[1][2] = 1;

    for (int i=2; i<=M; ++i){
        for (int j=2; j<=min(N, 4005); ++j){
            double to_calc = j*(j-1)/(double)N;
            to_calc /= (double)(N-1);
            to_calc *= prob[i-1][j];
//            cout << to_calc << endl;
            prob[i][j] += to_calc;

            to_calc = (j-1)/(double)N * 2;
            to_calc *= ((N-j+1)/(double)(N-1));
            to_calc *= prob[i-1][j - 1];

            prob[i][j] += to_calc;


            to_calc = (N-j+2)/(double)N;
            to_calc *= ((N-j+1)/(double)(N-1));
            to_calc *= prob[i-1][j - 2];

            prob[i][j] += to_calc;

//            cout << prob[2][3] << endl;

        }
    }
//    cout << prob[2][2] << " " << prob[2][3] << endl;
    double ans = 0;
    for (int i=2; i<=min(N, 4005); ++i){
        ans += prob[M][i]*i;
    }
//    for (int i=0; i<=M; ++i){
//        for (int j=0; j<=N; ++j){
//            cout << setw(15) << prob[i][j];
//        }
//        cout << endl;
//    }
//    cout << ans;
    printf("%.7f", ans);

    return 0;
}
