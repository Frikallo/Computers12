#include <bits/stdc++.h>

using namespace std;

// Function to determine if a baby's genes could possibly come from given parents
bool possibleBaby(const string &m, const string &f, const string &b)
{
    bool okay = true;
    for (int i = 0; i <= 4 && okay; i++)
    {
        if (b[i] >= 'A' && b[i] <= 'E')
            okay = (m[i * 2] >= 'A' && m[i * 2] <= 'E') ||
                   (m[i * 2 + 1] >= 'A' && m[i * 2 + 1] <= 'E') ||
                   (f[i * 2] >= 'A' && f[i * 2] <= 'E') ||
                   (f[i * 2 + 1] >= 'A' && f[i * 2 + 1] <= 'E');
        else
            okay = ((m[i * 2] >= 'a' && m[i * 2] <= 'e') ||
                    (m[i * 2 + 1] >= 'a' && m[i * 2 + 1] <= 'e')) &&
                   ((f[i * 2] >= 'a' && f[i * 2] <= 'e') ||
                    (f[i * 2 + 1] >= 'a' && f[i * 2 + 1] <= 'e'));
    }
    return okay;
}

int main()
{
    string mother, father, baby;
    int numBabies;

    cout << "Enter mother's genes: ";
    cin >> mother;
    cout << "Enter father's genes: ";
    cin >> father;

    cout << "Enter number of babies: ";
    cin >> numBabies;
    vector<string> babies;
    for (int i = 0; i < numBabies; i++)
    {
        cout << "Enter baby " << i + 1 << "'s genes: ";
        cin >> baby;
        babies.push_back(baby);
    }

    for (int i = 0; i < numBabies; i++)
    {
        baby = babies[i];
        if (possibleBaby(mother, father, baby))
            cout << "Possible baby." << endl;
        else
            cout << "Not their baby!" << endl;
    }
    return 0;
}