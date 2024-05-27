#include <bits/stdc++.h>

using namespace std;

#define INFINITY 100000000

int main(){

    int N, W, D;
    cin >> N >> W >> D;

    vector<int> walkways[N + 1]; //Adjacency list for walkways
    for (int i = 0; i < W; i++){
        int start, stop;
        cin >> start >> stop;
        walkways[stop].push_back(start); //Append in reverse for the breadth first search
    }

    //Calculate walking time from station i to station N
    //Breadth First Search
    queue<int> stack;
    vector<bool> alreadyvisited(N + 1, false); 
    vector<int> walkwaytimes(N + 1, INFINITY);
    walkwaytimes[N] = 0;
    alreadyvisited[N] = 1;
    stack.push(N);
    int time = 0;

    while(stack.empty() != true){

        int curstation = stack.front();
        stack.pop();

        for (const int connectingstation: walkways[curstation]){

            if (!alreadyvisited[connectingstation]){
                walkwaytimes[connectingstation] = walkwaytimes[curstation] + 1;
                stack.push(connectingstation);
            }

            alreadyvisited[connectingstation] = true;

        }

    }

    vector<int> subwayroute(N + 1);
    multiset<int> cumulativeTime; 
    subwayroute[0] = 0;

    for (int i = 1; i < N + 1; i++){
        cin >> subwayroute[i];
        cumulativeTime.insert(i - 1 + walkwaytimes[subwayroute[i]]);
    }

    int temp;
    int value;
    for (int d = 0; d < D; d++){
        int changes1, changes2;
        cin >> changes1 >> changes2;

        value = changes1 - 1 + walkwaytimes[subwayroute[changes1]];
        cumulativeTime.erase(cumulativeTime.find(value));

        value = changes2 - 1 + walkwaytimes[subwayroute[changes2]];
        cumulativeTime.erase(cumulativeTime.find(value));

        //Swap stations
        temp = subwayroute[changes1];
        subwayroute[changes1] = subwayroute[changes2];
        subwayroute[changes2] = temp;

        //Add new times
        cumulativeTime.insert(changes1 - 1 + walkwaytimes[subwayroute[changes1]]);
        cumulativeTime.insert(changes2 - 1 + walkwaytimes[subwayroute[changes2]]);

        cout << *cumulativeTime.begin() << endl;
    }
    return 0;
}