#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int dfs(int start, int goal, vector<vector<int>>& adj_list) {
    int num_paths = 0;
    vector<bool> visited(adj_list.size(), false);
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int current = st.top();
        st.pop();

        if (current == goal) {
            num_paths++;
            continue;
        }

        visited[current] = true;

        for (int neighbor : adj_list[current]) {
            if (!visited[neighbor]) {
                st.push(neighbor);
            }
        }
    }

    return num_paths;
}

int main() {
    int n, x, y;
    vector<vector<int>> adj_list(10000);
    cin >> n;
    while(x != 0 && y != 0) {
        cin >> x >> y;
        adj_list[x].push_back(y);
    }

    int num_paths = dfs(1, n, adj_list);
    cout << num_paths << endl;

    return 0;
}
