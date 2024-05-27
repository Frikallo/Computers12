#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    int electionYear, electionMonth, electionDay;
    electionYear = 2007;
    electionMonth = 2;
    electionDay = 27;

    for (int i = 0; i < n; i++) {
        int year, month, day;
        cin >> year >> month >> day;
        int age = electionYear - year;
        if (age > 18) {
            cout << "Yes" << endl;
        } else if (age < 18) {
            cout << "No" << endl;
        } else {
            if (month < electionMonth) {
                cout << "Yes" << endl;
            } else if (month > electionMonth) {
                cout << "No" << endl;
            } else {
                if (day <= electionDay) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
    }
    return 0;
}
