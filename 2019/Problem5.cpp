#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> triangle; //Our original triangle, note that as we run solve(), it will overwrite the actual values of this triangle

//subtriangle_size is the size of the current triangle we're trying to solve for
void solve(int subtriangle_size){

    //If subtriangles of size 1, just do nothing
    if (subtriangle_size == 1){
        return;
    }

    //Otherwise, we calculate the size of the 3 sub triangles of this sub triangle
    int subsize = ceil(subtriangle_size * 2.0 / 3.0);

    //Edge case, if subtriangle_size = 2, we actually only need subsize 1
    if (subtriangle_size == 2){
        subsize = 1;
    }
    
    solve(subsize); //Solve for all the smaller subtriangles that will make up the triangles of our current size
    //Note that for every triangle we solve, we put the max value of a triangle at its head node, (the top corner)

    //Update the triangles using triplets of smaller subtriangles
    for (int i = 0; i <= triangle.size() - subtriangle_size; i++){
        for (int j = 0; j <= i; j++){
            //The first top subtriangle has the same head as the current triangle, the bottom left subtriangle has its head at i + subtriangle_size - subsize
            //Lastly, the bottom right subtriangle is located at [i + subtriangle_size - subsize][j + subtriangle_size - subsize]
            //If you don't believe me, try this on paper
            triangle[i][j] = max(triangle[i][j], max(triangle[i + subtriangle_size - subsize][j], triangle[i + subtriangle_size - subsize][j + subtriangle_size - subsize]));
        }   
    }
    
}

int main(){

    int N, K;
    scanf("%d%d", &N, &K);

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
            //Add max value for this sub triangle size generated from solve() function call
            sum += triangle[i][j]; 
        }
    }
    
    cout << sum << '\n';
    
    return 0;
  
}