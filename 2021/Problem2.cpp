#include <bits/stdc++.h>

int main(){
    
    //Collect input
    int M, N, K;

    std::cin >> M >> N >> K;

    //Initialize vectors containing information as to how many times row[i] or column[i] has been painted over
    std::vector<int> row(M + 1, 0);
    std::vector<int> column(N + 1, 0);

    char instruction; //Storing whether the painter chooses a row or a column
    int num; //Storing row or column number

    for (int i = 0; i < K; i++){
        
        std::cin >> instruction >> num;

        if (instruction == 'R'){

            row[num] += 1;

        }

        else{

            column[num] += 1;

        }

    }

    //Calculate number of gold cells
    int gold = 0;
    for (int i = 1; i <= M; i++){

        for (int j = 1; j <= N; j++){

            //The number of times a cell has been painted over is the number of times its row and column have been painted together
            if ( (row[i] + column[j]) % 2 == 1 ){
                gold += 1;
            }

        }

    }

    std::cout << gold;

    return 0; 
}