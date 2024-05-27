#include <bits/stdc++.h>

using namespace std;

#define INFINITY 100000000

int main(){

    int N, W, D;
    cin >> N >> W >> D;

    vector<int> walkways[N + 1]; //array of vectors, walkways[n] is a vector containing all connecting stations to station n

    for (int i = 0; i < W; i++){
        int start, stop;
        cin >> start >> stop;
        walkways[stop].push_back(start); //Append in reverse for the breadth first search
    }

    //Calculate walking time from station i to station N
    //Breadth First Search

    queue<int> stack;
    vector<bool> alreadyvisited(N + 1, false); //to prevent revisiting the same node
    vector<int> walkwaytimes(N + 1, INFINITY); //INF to help us sort our multiset later, indicates there's no possible walkway
    walkwaytimes[N] = 0;
    alreadyvisited[N] = 1;
    stack.push(N);
    int time = 0;

    while(stack.empty() != true){

        int curstation = stack.front();
        stack.pop();

        for (const int connectingstation: walkways[curstation]){

            if (!alreadyvisited[connectingstation]){
                walkwaytimes[connectingstation] = walkwaytimes[curstation] + 1; //Connecting stations will always be 1 more minute away from the current station
                stack.push(connectingstation);
            }

            alreadyvisited[connectingstation] = true;

        }

    }

    //Calculate initial time for subway route
    vector<int> subwayroute(N + 1);
    //indices don't matter for this problem as we're only searching for the minimum time, making multiset extremely useful here as it sorts the times and allows for quick erasing and insertion of elements
    multiset<int> cumulativeTime; 
    subwayroute[0] = 0; //Dummy value

    for (int i = 1; i < N + 1; i++){
        cin >> subwayroute[i];
        cumulativeTime.insert(i - 1 + walkwaytimes[subwayroute[i]]); //calculate cumulative time = subway to station i + walking distance from i to N
    }

    int temp;
    int value;
    //Determining minimum time each day
    for (int d = 0; d < D; d++){
        int changes1, changes2;
        cin >> changes1 >> changes2;

        //Erase previous times for swapped stations that are to be swapped
        value = changes1 - 1 + walkwaytimes[subwayroute[changes1]];
        cumulativeTime.erase(cumulativeTime.find(value)); //important that .find() is used because otherwise all instances of the value would be removed

        value = changes2 - 1 + walkwaytimes[subwayroute[changes2]];
        cumulativeTime.erase(cumulativeTime.find(value));

        //Swap stations
        temp = subwayroute[changes1];
        subwayroute[changes1] = subwayroute[changes2];
        subwayroute[changes2] = temp;

        //Add new times
        cumulativeTime.insert(changes1 - 1 + walkwaytimes[subwayroute[changes1]]);
        cumulativeTime.insert(changes2 - 1 + walkwaytimes[subwayroute[changes2]]);

        cout << *cumulativeTime.begin() << '\n'; //multiset is always ordered meaning the minimum time is always at the front
    }

    return 0;
}