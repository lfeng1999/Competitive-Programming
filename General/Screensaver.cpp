#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

int R, C, T, t, sr, sc;
char grid[110][110];

bool first_time = true;

bool finished(int r, int c){
    //cout << r << " " << c << endl;
    if (t < 0){
        printf("The observer stays within the grid.");
        return true;
    }
    if (r < 0 || r >= R || c < 0 || c >= C){
        printf("The observer leaves the grid after %d tick(s).", T - t);
        return true;
    }
    return false;
}
void rotate_cell(int r, int c){
    if (grid[r][c] == '-') grid[r][c] = '|';
    else if (grid[r][c] == '|') grid[r][c] = '-';
    else if (grid[r][c] == '/') grid[r][c] = '\\';
    else if (grid[r][c] == '\\') grid[r][c] = '/';
}

void move_right(int r, int c);
void move_left(int r, int c);
void move_up(int r, int c);
void move_down(int r, int c);

void move_right(int r, int c){
    if (finished(r, c)) return;
    t--;
    if (grid[r][c] == '\\'){
        rotate_cell(r, c);
        move_down(r + 1, c);
    }
    else if (grid[r][c] == '/'){
        rotate_cell(r, c);
        move_up(r - 1, c);
    }
    else if (grid[r][c] == '|'){
        rotate_cell(r, c);
        move_left(r, c - 1);
    }
    else{
        move_right(r, c + 1);
    }
}
void move_left(int r, int c){
    if (finished(r, c)) return;
    t--;
    if (grid[r][c] == '\\'){
        rotate_cell(r, c);
        move_up(r - 1, c);
    }
    else if (grid[r][c] == '/'){
        rotate_cell(r, c);
        move_down(r + 1, c);
    }
    else if (grid[r][c] == '|'){
        rotate_cell(r, c);
        move_right(r, c + 1);
    }
    else{
        move_left(r, c - 1);
    }
}
void move_up(int r, int c){
    if (finished(r, c)) return;
    t--;
    if (grid[r][c] == '\\'){
        rotate_cell(r, c);
        move_left(r, c - 1);
    }
    else if (grid[r][c] == '/'){
        rotate_cell(r, c);
        move_right(r, c + 1);
    }
    else if (grid[r][c] == '-'){
        rotate_cell(r, c);
        move_down(r + 1, c);
    }
    else{
        move_up(r - 1, c);
    }
}
void move_down(int r, int c){
    if (finished(r, c)) return;
    t--;
    if (grid[r][c] == '\\'){
        rotate_cell(r, c);
        move_right(r, c + 1);
    }
    else if (grid[r][c] == '/'){
        rotate_cell(r, c);
        move_left(r, c - 1);
    }
    else if (grid[r][c] == '-'){
        rotate_cell(r, c);
        move_up(r - 1, c);
    }
    else{
        move_down(r + 1, c);
    }
}

int main(){
    //freopen("testdata.txt","r",stdin);
    cin >> C >> R >> T;

    int sr = 0, sc = 0;
    for (int i=0; i<R; ++i){
        for (int j=0; j<C; ++j){
            cin >> grid[i][j];
            if (grid[i][j] == 'O'){
                sr = i, sc = j;
                grid[i][j] = '.';
            }
        }
    }
    //cout << sr << " " << sc << " " << T << endl;
    t = T;
    move_right(sr, sc);


    return 0;
}