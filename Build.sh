YEAR=$1
PROBLEM_NUMBER=$2

cd /Users/noahkay/Desktop/Repos/Computers12/$YEAR
/usr/bin/clang++ -std=c++20 -fcolor-diagnostics -fansi-escape-codes -g Problem$PROBLEM_NUMBER.cpp -o ./Builds/Problem$PROBLEM_NUMBER
./Builds/Problem$PROBLEM_NUMBER