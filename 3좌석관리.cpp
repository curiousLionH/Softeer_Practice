#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, Q, id, x, y;
float D = 0;
string com;     // 커맨드 (in / out)
vector<vector<int>> table(22, vector<int> (22, -1));        // table
vector<int> eat_done;       // 다먹은 id들
vector<int> eating;         // 식사중인 id들
vector<pair<int,int>> eating_xy;        // 식사중인 id들의 자리
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};       // 상하좌우

float getD (int x, int y){      // 안전도 D찾는 함수
    float d = M+N;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            if (table[i][j] > 0){
                float temp = sqrt(pow(x-i, 2) + pow(y-j, 2));
                if (temp < d){
                    d = temp;
                }
            }
        }
    }
    return d;
}

bool can_sit(int X, int Y){         // 앉을 수 있는 자리인지 판별 (상하좌우에 앉은 사람 없는지 판별)
    for (int k = 0; k < 4; k++){
        if (table[X+dx[k]][Y+dy[k]] > 0){
            return false;
        }
    }
    return true;
}

void find_seat(){       // 자리 배정
    if (eating.empty()){
        x = 1; y = 1;
        return;
    }
    D = 1; x = -1; y = -1;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            if (table[i][j] == 0 && can_sit(i, j)){
                float temp = getD(i, j);
                // printf("D at %d,%d is %f\n", i, j, temp);
                if (temp > D){
                    D = temp;
                    x = i; y = j;
                }
            }
        }
    }
    return;
}

void in(){
    if (find(eat_done.begin(), eat_done.end(), id) != eat_done.end()){
        printf("%d already ate lunch.\n", id);
        return;
    }
    if (find(eating.begin(), eating.end(), id) != eating.end()){
        printf("%d already seated.\n", id);
        return;
    }
    find_seat();
    if (x == -1){
        printf("There are no more seats.\n");
    }
    else{
        eating.push_back(id);
        eating_xy.push_back(make_pair(x, y));
        table[x][y] = id;
        printf("%d gets the seat (%d, %d).\n", id, x, y);
    }
}

void out(){
    auto itr = find(eating.begin(), eating.end(), id);
    if (itr == eating.end()){
        if (find(eat_done.begin(), eat_done.end(), id) == eat_done.end()){
            printf("%d didn't eat lunch.\n", id);
            return;
        }
        else{
            printf("%d already left seat.\n", id);
            return;
        }
    }
    int index = itr-eating.begin();
    int tempx = eating_xy[index].first;
    int tempy = eating_xy[index].second;
    table[tempx][tempy] = 0;
    eating_xy.erase(eating_xy.begin()+index);
    eating.erase(itr);
    eat_done.push_back(id);
    printf("%d leaves from the seat (%d, %d).\n", id, tempx, tempy);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> Q;

    for (int i = 1; i <= N; i++){       // 테이블 초기화
        for (int j = 0; j <= M; j++){
            table[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= Q; i++){
        cin >> com >> id;
        
        if (com == "In"){
            in();
        }
        else{
            out();
        }
    }

}