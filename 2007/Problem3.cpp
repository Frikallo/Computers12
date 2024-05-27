#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x, y, separation = -1;
    cin >> n;
    vector<int> assf(10000);
    vector<bool> circle(10000, false);

    for (int i = 1; i < n + 1; i++) {
        int index;
        cin >> index;
        cin >> assf[index];
    }

    cin >> x >> y;

    while (x != 0 && y != 0) {
        do {
            circle[x] = true;
            x = assf[x];
            separation++;
        } while (y != x && !circle[x]);

        if (x == y)
            cout << "Yes " << separation << endl;
        else
            cout << "No" << endl;

        separation = -1;
        fill(circle.begin(), circle.end(), false);

        cin >> x >> y;
    }

    return 0;
}
