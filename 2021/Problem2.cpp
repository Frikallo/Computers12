#include <bits/stdc++.h>

using namespace std;

int main(){
    int M, N, K;
    cin >> M >> N >> K;

    vector<int> row(M + 1, 0);
    vector<int> column(N + 1, 0);

    char instruction;
    int num;

    for (int i = 0; i < K; i++){
        cin >> instruction >> num;
        if (instruction == 'R'){
            row[num] += 1;
        }

        else{
            column[num] += 1;
        }

    }

    int gold = 0;
    for (int i = 1; i <= M; i++){
        for (int j = 1; j <= N; j++){
            if ( (row[i] + column[j]) % 2 == 1 ){
                gold += 1;
            }
        }
    }

    cout << gold;
    return 0; 
}