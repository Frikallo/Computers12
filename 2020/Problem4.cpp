#include <bits/stdc++.h>

int main(){

    std::string table; //Represent table
    std::cin >> table;

    int table_size = table.size();

    table += table; //Since the table is circular, we need to connect it's ends for our sliding window to work. You could try to accomplish a rolling window with negative indexing but that's too much work

    int countA = 0; //Total number of A's
    int countB = 0; //Total number of B's
    int countC = 0; //Total number of C's

    //Count each letter frequency
    for (int i = 0; i < table_size; i++){

        if (table[i] == 'A'){
            countA++;
        }

        else if (table[i] == 'B'){
            countB++;
        }

        else{
            countC++;
        }

    }

    //Our sections, the key is the letter in that section and the corresponding value is the frequency of that letter
    //For example sectionA['A'] == 5 means that there are 5 A's in section A
    std::map<char, int> sectionA;
    std::map<char, int> sectionB;
    std::map<char, int> sectionC;

    sectionA['A'] = 0, sectionA['B'] = 0, sectionA['C'] = 0;
    sectionB['A'] = 0, sectionB['B'] = 0, sectionB['C'] = 0;
    sectionC['A'] = 0, sectionC['B'] = 0, sectionC['C'] = 0;

    //Calculate letter frequency in each section

    //Section A
    for (int i = 0; i < countA; i++){

        sectionA[table[i]]++;

    }

    //Section B
    for (int i = countA; i < countA + countB; i++){

        sectionB[table[i]]++;

    }

    //Section C
    for (int i = countA + countB; i < countA + countB + countC; i++){

        sectionC[table[i]]++;

    }

    //Calculate minimum number of swaps for initial arrangement (no offset)
    int num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
    std::set<int> swaps; //I will just be inserting all values into a set, sets are ordered therefore at the end I will print the minimum value of the set
    swaps.insert(num_of_swaps);

    //Rolling window begin
    for (int i = 0; i < table_size - 1; i++){

        sectionA[table[i]]--; //Remove first part of section A
        sectionA[table[i + countA]]++; //Add to section A
        sectionB[table[i + countA]]--; //Remove first part of section B
        sectionB[table[i + countA + countB]]++; //Add to section B
        sectionC[table[i + countA + countB]]--; //Remove first part of section C
        sectionC[table[i + countA + countB + countC]]++; //Add to section C

        //Calculate minimum number of swaps for this particular arrangement and positioning
        num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
        swaps.insert(num_of_swaps);

    }

    //
    // Previously, we just calculated all possible possitions for arrangement ABC, we must now do the same for CBA 
    //

    //Reset sections
    sectionA['A'] = 0, sectionA['B'] = 0, sectionA['C'] = 0;
    sectionB['A'] = 0, sectionB['B'] = 0, sectionB['C'] = 0;
    sectionC['A'] = 0, sectionC['B'] = 0, sectionC['C'] = 0;

    //Count frequencies once more, except in CBA order now

    //Section C
    for (int i = 0; i < countC; i++){

        sectionC[table[i]]++;

    }

    //Section B
    for (int i = countC; i < countC + countB; i++){

        sectionB[table[i]]++;

    }

    //Section A
    for (int i = countC + countB; i < countC + countB + countA; i++){

        sectionA[table[i]]++;

    }

    num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
    swaps.insert(num_of_swaps);

    //Rolling window once again
    for (int i = 0; i < table_size - 1; i++){

        sectionC[table[i]]--; //Remove first part of section C
        sectionC[table[i + countC]]++; //Add to section C
        sectionB[table[i + countC]]--; //Remove first part of section B
        sectionB[table[i + countC + countB]]++; //Add to section B
        sectionA[table[i + countC + countB]]--; //Remove first part of section A
        sectionA[table[i + countC + countB + countA]]++; //Add to section A

        num_of_swaps = sectionA['B'] + sectionA['C'] + sectionB['A'] + sectionB['C'] - std::min(sectionA['B'], sectionB['A']);
        swaps.insert(num_of_swaps);

    }

    //Output minimum number of swaps
    std::cout << *swaps.begin();

    return 0;

}