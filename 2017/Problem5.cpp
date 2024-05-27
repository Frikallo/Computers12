#include <bits/stdc++.h>

using namespace std;

#define INF 2147483647
#define vi vector<int>
#define vvi vector<vector<int>>

const int blockLength = 388;

struct block{
    vi left = vi (150001, INF);
    vi right = vi (150001, -1);
    int totalPeople = 0;
};

vector<block> blocks (blockLength + 1);

int main(){

    int N, M, Q;
    cin >> N >> M >> Q;

    vi trainToLine (150001);
    for (int i = 1; i <= N; i++){
       cin >> trainToLine[i]; 
    }

    vvi lines (150001);
    vi posInLine (150001);
    for (int i = 1; i <= N; i++){

        int ppl; cin >> ppl;

        blocks[i / blockLength].totalPeople += ppl;

        lines[trainToLine[i]].push_back(ppl);

        blocks[i / blockLength].left[trainToLine[i]] = min(blocks[i / blockLength].left[trainToLine[i]], (int)lines[trainToLine[i]].size() - 1);

        blocks[i / blockLength].right[trainToLine[i]] = (int)lines[trainToLine[i]].size() - 1;

        posInLine[i] = (int) lines[trainToLine[i]].size() - 1;
    }

    vi shift (150001, 0);
    
    while (Q--){
        int option;
        cin >> option;

        //Survey
        if (option == 1){
            int left, right;
            cin >> left >> right;
            int survey = 0;
            for (int i = left; i <= right; ){
                //Entire block is in range
                if (i % blockLength == 0 && i + blockLength - 1 <= right){
                    survey += blocks[i / blockLength].totalPeople;
                    i += blockLength;
                }
                //Block is partially in range
                else{
                    survey += lines[trainToLine[i]][ (posInLine[i] - shift[trainToLine[i]] + (int)lines[trainToLine[i]].size()) % (int)lines[trainToLine[i]].size()];
                    i++;
                }
            }
            cout << survey << '\n';
        }
        //Run line
        else{
            int line;
            cin >> line;

            int lineSize = lines[line].size();
            
            shift[line]++;
            shift[line] %= lineSize;
            for (int i = 0; i <= blockLength; i++){
                if (blocks[i].left[line] == INF){
                    continue;
                }
                blocks[i].totalPeople -= lines[line][blocks[i].right[line]];
                blocks[i].left[line]--; blocks[i].left[line] = (blocks[i].left[line] + lineSize) % lineSize;
                blocks[i].right[line]--; blocks[i].right[line] = (blocks[i].right[line] + lineSize) % lineSize;
                blocks[i].totalPeople += lines[line][blocks[i].left[line]];
            }
        }
    }
    return 0;
}