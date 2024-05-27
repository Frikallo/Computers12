#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> triangle;
void solve(int subtriangle_size){

    if (subtriangle_size == 1){
        return;
    }

    int subsize = ceil(subtriangle_size * 2.0 / 3.0);
    if (subtriangle_size == 2){
        subsize = 1;
    }
    
    solve(subsize);
    for (int i = 0; i <= triangle.size() - subtriangle_size; i++){
        for (int j = 0; j <= i; j++){
            triangle[i][j] = max(triangle[i][j], max(triangle[i + subtriangle_size - subsize][j], triangle[i + subtriangle_size - subsize][j + subtriangle_size - subsize]));
        }   
    }
}

int main(){

    int N, K;
    scanf("%d%d", &N, &K); //USE SCANF, DO NOT USE CIN
    triangle.resize(N);

    //Get triangle
    for (int i = 0; i < N; i++){
        for (int j = 0; j <= i; j++){
            int value;
            scanf("%d", &value); //USE SCANF, DO NOT USE CIN
            triangle[i].push_back(value);
        }
    }

    //Solve
    solve(K);
    long long sum = 0; //Use long long, number gets very big

    //For each subtriangle of size K
    for (int i = 0; i <= N - K; i++){
        for (int j = 0; j <= i; j++){
            //Add max value for this sub triangle size generated from solve()
            sum += triangle[i][j]; 
        }
    }
    
    cout << sum << '\n';
    
    return 0;
  
}