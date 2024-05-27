#include <bits/stdc++.h>

using namespace std;

int sequence[150001];
int segmentTree[150001 * 4];

void build (int i = 1, int treeleft = 1, int treeright = 150001){
    if (treeleft == treeright){
        segmentTree[i] = sequence[treeleft];
    }
    else{
        int mid = treeleft + (treeright - treeleft) / 2;
        build (i * 2, treeleft, mid);
        build (i * 2 + 1, mid + 1, treeright);
        segmentTree[i] = gcd(segmentTree[i * 2], segmentTree[i * 2 + 1]);
    }
}

int query (int left, int right, int i = 1, int treeleft = 1, int treeright = 150001){

    //Out of range
    if (left > right){
        return 0;
    }

    if (left == treeleft && right == treeright){
        return segmentTree[i];
    }
    
    int mid = treeleft + (treeright - treeleft) / 2;
    return gcd(query (left, min(mid, right), i * 2, treeleft, mid), query (max(mid + 1, left), right, i * 2 + 1, mid + 1, treeright));

}

int main(){
    map<int, vector<int>> diffarrays;
    diffarrays[1] = vector<int> (150002, 0);
    diffarrays[2] = vector<int> (150002, 0);
    diffarrays[3] = vector<int> (150002, 0);
    diffarrays[4] = vector<int> (150002, 0);
    diffarrays[5] = vector<int> (150002, 0);
    diffarrays[6] = vector<int> (150002, 0);
    diffarrays[7] = vector<int> (150002, 0);
    diffarrays[8] = vector<int> (150002, 0);
    diffarrays[9] = vector<int> (150002, 0);
    diffarrays[10] = vector<int> (150002, 0);
    diffarrays[11] = vector<int> (150002, 0);
    diffarrays[12] = vector<int> (150002, 0);
    diffarrays[13] = vector<int> (150002, 0);
    diffarrays[14] = vector<int> (150002, 0);
    diffarrays[15] = vector<int> (150002, 0);
    diffarrays[16] = vector<int> (150002, 0);
    int N, M;

    cin >> N >> M;

    int x[150000];
    int y[150000];
    int z[150000];

    for (int i = 0; i < M; i++){
        cin >> x[i] >> y[i] >> z[i];
        diffarrays[z[i]][x[i]] += 1;
        diffarrays[z[i]][y[i] + 1] -= 1;
        
    }

    int sum;
    for (int i = 1; i <= 16; i++){
        sum = 0;
        for (int j = 1; j <= 150000; j++){
            sum += diffarrays[i][j];
            diffarrays[i][j] = sum;
        }
    }

    //Generate sequence
    for (int i = 1; i <= N; i++){
        //Find LCM
        int lcm = 1;
        for (int z = 1; z <= 16; z++){
            if (diffarrays[z][i] > 0){
                lcm = lcm * z / gcd(lcm, z);
            }
        }
        sequence[i] = lcm;
    }

    //Build tree
    build();

    for (int i = 0; i < M; i++){
        if (query(x[i], y[i]) != z[i]){
            cout << "Impossible";
            return 0;
        }

    }

    for (int i = 1; i <= N; i++){
        cout << sequence[i] << ' ';
    }
    return 0;
}