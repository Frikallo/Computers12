#include <bits/stdc++.h>

int main(){

    while (true){

        //Get vector size, if 0 terminate
        int n; std::cin >> n;

        if (n == 0){
            break;
        }

        //Create group
        std::vector<std::vector<int>> group (n, std::vector<int> (n));

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                std::cin >> group[i][j];
            }
        }

        //Find identity

        int identity = -1; //Stores the identity of the group, if no identity found, its default is -1

        for (int i = 0; i < n; i++){

            bool identityFound = true;

            for (int j = 0; j < n; j++){

                //Check horizontally
                if (group[i][j] != j + 1){
                    identityFound = false;
                    break;
                }

                //Check vertically
                if (group[j][i] != j + 1){
                    identityFound = false;
                    break;
                }

            }

            //If the identity is found
            if (identityFound){
                identity = i + 1;
                break;
            }

        }

        //If no identity, the group is impossible
        if (identity == -1){
            std::cout << "no\n";
            continue;
        }

        //Check inverse
        bool inverseCheck = true;

        for (int i = 0; i < n && inverseCheck; i++){

            bool iFound = false; //Remember, each row must contain i, if no identity is found, then there's no inverse then

            for (int j = 0; j < n && inverseCheck; j++){

                if (group[i][j] == identity){
                    iFound = true;

                    //If group[i][j] equals identity so must group[j][i]
                    if (group[j][i] != identity){
                        inverseCheck = false;
                    }

                }

            }

            if (!iFound){
                inverseCheck = false;
            }

        }

        if (!inverseCheck){
            std::cout << "no\n";
            continue;
        }

        //Check associativity

        bool good = true;

        for (int x = 0; x < n && good; x++){

            for (int y = 0; y < n && good; y++){

                for (int z = 0; z < n && good; z++){

                    //Literaly implementing the problem
                    if (group[x][group[y][z] - 1] != group[group[x][y] - 1][z]){
                        good = false;
                    }

                }

            }

        }

        if (!good){
            std::cout << "no\n";
            continue;
        }

        std::cout << "yes\n";

    }

    return 0;

}