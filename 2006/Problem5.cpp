#include <bits/stdc++.h>

using namespace std;

int m, n, a, b, c;

vector<int> previous [1048576 + 1];

//Find next generation given an arrangement
void findNextGen(int binary){

    int original = binary; //Make copy for later
    int current [m + 2][n + 2];
    memset(current, 0, sizeof(current));

    //Pad the array with a border so that we don't have to manually check border ourselves
    //Convert decimal back to binary
    for (int i = 1; i < m + 1; i++){
        for (int j = 1; j < n + 1; j++){
            current[i][j] = binary % 2;
            binary /= 2;
        }
    }

    int nextGen = 0;
    int power = 1;

    //Find next gen    
    for (int i = 1; i < m + 1; i++){
        for (int j = 1; j < n + 1; j++){

            //Count alive neighbours
            int alive = 0;
            alive += current[i - 1][j]; //Up
            alive += current[i + 1][j]; //Down
            alive += current[i][j - 1]; //Left
            alive += current[i][j + 1]; //Right
            alive += current[i - 1][j - 1]; //Top Left
            alive += current[i - 1][j + 1]; //Top right
            alive += current[i + 1][j - 1]; //Bottom left
            alive += current[i + 1][j + 1]; //Bottom right

            //If the cell was already alive
            if (current[i][j]){
                if (alive >= a && alive <= b){
                    nextGen += power;
                }
            }

            //If the cell was previously dead
            else{
                if (alive > c){
                    nextGen += power;
                }
            }

            power *= 2;
            
        }
    }

    //Add to graph
    previous[nextGen].push_back(original);
        
}

int main(){

    cin >> m >> n >> a >> b >> c;

    int start = 0;
    int powOf2 = 1;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            char x;
            cin >> x;
            //Cell is alive
            if (x == '*'){
                start += powOf2;
            }
            powOf2 *= 2;
        }
    }   

    //Generate graph
    for (int i = 0; i <= pow(2, m * n); i++){
        findNextGen(i);
    }

    //BFS
    vector<int> visited (1048576 + 1, 0);
    vector<int> distance (1048576 + 1, 0);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    int steps = 0;
    while (!q.empty()){
        int curr = q.front(); q.pop();
        if (previous[curr].size() == 0){
            cout << distance[curr] << '\n';
            return 0;
        }
        for (auto& prev: previous[curr]){
            if (!visited[prev]){
                q.push(prev);
                distance[prev] = distance[curr] + 1;
                visited[prev] = true;
            }
        }
        steps++;
        if (steps == 50){
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    
    return 0;
    
}