#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    string input;
    cin>>input;
    string grid = "1234";
    for(char i : input){
            string y;
            string a, b, c, d;
        a = grid[0];
        b = grid[1];
        c = grid[2];
        d = grid[3];
        if(i == 'H'){
            grid = c + d + a + b;

        }
        else{
            grid = b + a + d + c;
        }

    }

    cout<<grid[0]<<" "<<grid[1]<<endl;
    cout<<grid[2]<<" "<<grid[3]<<endl;
}