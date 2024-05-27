#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    string plaintext_message, key, ciphertext_message;
    vector<pair<string, string>> map;

    getline(cin, plaintext_message);
    getline(cin, key);
    getline(cin, ciphertext_message);

    for ( int i=0; (unsigned)i < plaintext_message.length(); ++i ) {
        map.push_back(
            make_pair(string(1, plaintext_message[i]), string(1, key[i]))
        );
    }

    // Sort the map and remove duplicates
    sort( map.begin(), map.end() );
    map.erase( unique( map.begin(), map.end() ), map.end() );
    
    string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    // Infering the 27th character if all 26 characters are present
    // I.E "G" is not in the plaintext message but the key contains every letter except "Z"
    // so append G -> Z to the map
    string missing_letter_in_key, missing_letter;
    if (map.size() == 26) {
        for ( int i=0; (unsigned)i < characters.length(); ++i ) {
            for ( int j=0; (unsigned)j < map.size(); ++j ) {
                if ( string(1, characters[i]) == map[j].first ) {
                    break;
                }
                if ( (unsigned)j == map.size() - 1 ) {
                    missing_letter_in_key = characters[i];
                }
            }
            for ( int j=0; (unsigned)j < map.size(); ++j ) {
                if ( string(1, characters[i]) == map[j].second ) {
                    break;
                }
                if ( (unsigned)j == map.size() - 1 ) {
                    missing_letter = characters[i];
                }
            }
        }
        map.push_back(make_pair(missing_letter_in_key, missing_letter));
    }

    vector<char> decoded_message;
    bool found = false;
    for ( int i=0; (unsigned)i < ciphertext_message.length(); ++i ) {

        for ( int j=0; (unsigned)j < map.size(); ++j ) {
            if ( string(1, ciphertext_message[i]) == map[j].second ) {
                decoded_message.push_back(map[j].first[0]);
                found = true;
            }
        }

        if ( !found ) {
            decoded_message.push_back('.');
        }

        found = false;
    }

    string s( decoded_message.begin(), decoded_message.end() );
    cout << s << endl;
    return 0;
}


/*

THE QUICK BROWN FOX JUMPS OVER THE LAZY DO
TMFPNOQLRPHYK IPUKVPGOEADPKBFYPTMFPJCZXPWK
TMFPWKSPCIWPTMFPUKV

*/