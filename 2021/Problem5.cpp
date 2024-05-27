#include <bits/stdc++.h>

using namespace std;

int sequence[150001];
int segmentTree[150001 * 4]; //Generally a segment tree will never be larger than 4 times the size of the original array, read proof online if you're curious as to why

//Build function for segment tree with 1 indexing
void build (int i = 1, int treeleft = 1, int treeright = 150001){

    //When we encounter a leaf node
    if (treeleft == treeright){

        segmentTree[i] = sequence[treeleft];

    }

    else{

        //Calculate midpoint, use int division to discard remainder
        int mid = treeleft + (treeright - treeleft) / 2;
        build (i * 2, treeleft, mid);
        build (i * 2 + 1, mid + 1, treeright);
        segmentTree[i] = gcd(segmentTree[i * 2], segmentTree[i * 2 + 1]);

    }

}

//Query function for segment tree
int query (int left, int right, int i = 1, int treeleft = 1, int treeright = 150001){

    //Out of range
    if (left > right){
        return 0;
    }

    //Segment of the tree is a part of the range
    if (left == treeleft && right == treeright){
        return segmentTree[i];
    }
    
    //Calculate mid
    int mid = treeleft + (treeright - treeleft) / 2;
    
    //If segment is partially in range, recurse deeper down the segment tree until corresponding nodes are found
    //The min and max functions are important here to ensure that the proper range is being queried with each recurse
    return gcd(query (left, min(mid, right), i * 2, treeleft, mid), query (max(mid + 1, left), right, i * 2 + 1, mid + 1, treeright));

}

int main(){

    //Difference arrays, size 150002 because of 1 indexing and the final index padding as well
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

    //Main code
    int N, M;

    cin >> N >> M;

    //For storing requirements
    int x[150000];
    int y[150000];
    int z[150000];

    //Collect requirements
    for (int i = 0; i < M; i++){
        cin >> x[i] >> y[i] >> z[i];

        //Update difference array
        diffarrays[z[i]][x[i]] += 1;
        diffarrays[z[i]][y[i] + 1] -= 1;
        
    }

    //Final iteration over difference arrays
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

        //Determine LCM
        int lcm = 1;
        for (int z = 1; z <= 16; z++){

            if (diffarrays[z][i] > 0){

                //Formula of lowest common multiple of a, b is the absolute of (a * b) / gcd(a, b), in this case there's no negatives so I discard the absolute value part
                lcm = lcm * z / gcd(lcm, z);

            }

        }

        //Add to sequence
        sequence[i] = lcm;

    }

    //Build segment tree
    build();

    //Check requirements via query function we created
    for (int i = 0; i < M; i++){

        //If GCD of range(x, y) != z
        if (query(x[i], y[i]) != z[i]){
            cout << "Impossible";
            return 0;
        }

    }

    //Output sequence
    for (int i = 1; i <= N; i++){
        cout << sequence[i] << ' ';
    }

    return 0;
}