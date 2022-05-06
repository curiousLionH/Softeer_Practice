// 소요시간 42분
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
// A : 65

string M, K, ans="";        // message, key, answer
int cnt = 0, ax, ay, bx, by;    // ssang(pair) 각각의 v상에서의 위치
vector<bool> alphabet(26, false);
vector<vector<char>> v(5, vector<char> (5, ' '));
vector<pair<char,char>> ssang;

// printv, printssang은 그냥 코딩중에 내가 확인하기 위한 용도로 만든 프린트 함수임. 별의미없음
void printv(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
void printssang(){
    for (int i = 0; i < ssang.size(); i++){
        printf("%c %c\t", ssang[i].first, ssang[i].second);
    }
}

// 보드 제작
void make_board(){
    for (int i = 0; i < K.length(); i++){
        if (alphabet[K[i]- 65] == false){
            v[cnt/5][cnt%5] = K[i];
            alphabet[K[i]- 65] = true;
            cnt++;
        } 
    }
    for (int i = 0; i < 26; i++){
        if (!alphabet[i]){
            v[cnt/5][cnt%5] = i+65;
            cnt++;
        }
    }
}
// 쌍 제작 (make_pair로 짓고 싶었으나 이미 있는 함수이름이라 어쩔수없었음....)
void make_ssang(){
    cnt = 0;
    while(cnt < M.length()){
        if (cnt == M.length()-1){
            ssang.push_back(make_pair(M[cnt], 'X'));
            cnt += 1;
        }
        else if (M[cnt] == M[cnt+1]){
            if (M[cnt] == 'X'){
                ssang.push_back(make_pair(M[cnt], 'Q'));
            }
            else{
                ssang.push_back(make_pair(M[cnt], 'X'));
            }
            cnt += 1;
        }
        else{
            ssang.push_back(make_pair(M[cnt], M[cnt+1]));
            cnt += 2;
        }
    }
}
// 쌍의 두 문자의 v에서의 위치 찾기
void find_xy(char A, char B){
    for (int i = 0; i < 5; i++){
        auto itr = find(v[i].begin(), v[i].end(), A);
        if (itr != v[i].end()){
            ax = i; ay = itr-v[i].begin();
            break;
        }
    }
    for (int i = 0; i < 5; i++){
        auto itr = find(v[i].begin(), v[i].end(), B);
        if (itr != v[i].end()){
            bx = i; by = itr-v[i].begin();
            break;
        }
    }
}
// 암호화
void cipher(){
    for (int i = 0; i < ssang.size(); i++){     
        find_xy(ssang[i].first, ssang[i].second);
        if (ax == bx){              // 1. 행이 같은 경우
            ans += v[ax][(ay+1)%5];
            ans += v[bx][(by+1)%5];
        }
        else if (ay == by){         // 2. 열이 같은 경우
            ans += v[(ax+1)%5][ay];
            ans += v[(bx+1)%5][by];
        }
        else{                       // 3. 둘다 다른 경우
            ans += v[ax][by];
            ans += v[bx][ay];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    alphabet[9] = true;
    cin >> M >> K;

    make_board();
    make_ssang();
    cipher();
    cout << ans;
}