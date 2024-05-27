#include <bits/stdc++.h>

int n, k, w;
int dp[501][30000];
int blocks [30000];

int main(){

    int t;
    std::cin >> t;

    while (t--){
   
        std::cin >> n >> k >> w;

        int pins [n]; int total = 0;
        for (int i = 0; i < n; i++){
            std::cin >> pins[i];
            total += pins[i];
        }

        //Precompute chunks
        blocks[0] = 0;
        for (int i = 0; i < w; i++){
            blocks[0] += pins[i];
        }

        //Use rolling window, aka remove leftmost add right most
        for (int i = 1; i < n; i++){
            blocks[i] = blocks[i - 1] - pins[i - 1];
            if (i + w - 1 < n){
                blocks[i] += pins[i + w - 1];
            }
        }

        //Memset dp
        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= k; i++){
            for (int j = n - 1; j >= 0; j--){
                //Edge case, we're at the end of the line
                if (j >= n - w){
                    dp[i][j] = blocks[j];
                }
                //Otherwise, the usual logic
                else{
                    dp[i][j] = std::max(dp[i - 1][j + w] + blocks[j], dp[i][j + 1]);
                }
            }
        }

        //Answer is found at dp[k][0] since we've used all k balls and we're viewing the max from index 0 to the end of the line
        std::cout << dp[k][0] << '\n';
        
    }
    
    return 0;
    
}