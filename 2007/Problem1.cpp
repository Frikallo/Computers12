#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    int electionYear, electionMonth, electionDay;
    electionYear = 2007;
    electionMonth = 2;
    electionDay = 27;

    for (int i = 0; i < n; i++) {
        int year, month, day;
        std::cin >> year >> month >> day;
        int age = electionYear - year;
        if (age > 18) {
            std::cout << "Yes" << std::endl;
        } else if (age < 18) {
            std::cout << "No" << std::endl;
        } else {
            if (month < electionMonth) {
                std::cout << "Yes" << std::endl;
            } else if (month > electionMonth) {
                std::cout << "No" << std::endl;
            } else {
                if (day <= electionDay) {
                    std::cout << "Yes" << std::endl;
                } else {
                    std::cout << "No" << std::endl;
                }
            }
        }
    }
    return 0;
}
