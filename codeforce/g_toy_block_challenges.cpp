// G. The Toy Block Challenge
// time limit per test2 seconds
// memory limit per test512 megabytes
// Jag is a young mathematician and toy enthusiast. He has a set of n
//  wooden blocks, numbered 1
//  through n
// . His goal is to stack the blocks in order, from 1
//  (smallest) at the top to n
//  (largest) at the bottom.

// However, Jag's clumsy friend has mixed up the blocks, creating a random shuffled stack. To measure how "out-of-order" the stack is, Jag counts Mistakes.

// A Mistake occurs whenever a block with a smaller number is placed above a block with a larger number in the stack.

// For example:

// If block 1 is above block 3 in the stack, this counts as a Mistake.

// If block 3 is above block 1, this does not count as a Mistake.

// Mistakes are counted for all pairs of blocks where the smaller number is above the larger number, not just adjacent blocks.

// Jag wants to know: given the total number of blocks n
//  and a desired number of Mistakes k
// , how many ways can the blocks be stacked so that there are exactly k
//  Mistakes? Since the answer can be very large, report it modulo 109+7
// .

// Input
// A single line containing two integers n
//  and k
//  (1≤n≤100
// , 0≤k≤n(n−1)2
// ) — the total number of blocks and the desired number of Mistakes.

// Output
// Print a single integer — the number of ways to stack the blocks so that there are exactly k
//  Mistakes, modulo 109+7
// .

// Example
// InputCopy
// 4 3
// OutputCopy
// 6
// Note
// For example, when n=4
//  and k=3
// , there are 6
//  valid stackings:

// [1, 4, 3, 2]
// [2, 3, 4, 1]
// [2, 4, 1, 3]
// [3, 1, 4, 2]
// [3, 2, 1, 4]
// [4, 1, 2, 3]
// Each arrangement corresponds to a stack with exactly 3
//  Mistakes — that is, 3
//  pairs of blocks (i,j)
//  such that i<j
//  but block i
//  appears above block j
// .

// For example, in the permutation [1,4,3,2]
// :

// Mistake pairs are (1,4)
// , (1,3)
// , and (1,2)
// , so the total number of Mistakes is 3
// .







































#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        vector<int> prefix(k + 1, 0);
        prefix[0] = dp[i - 1][0];
        for (int j = 1; j <= k; ++j)
            prefix[j] = (prefix[j - 1] + dp[i - 1][j]) % MOD;

        for (int j = 0; j <= k; ++j) {
            int left = j - i >= 0 ? prefix[j - i] : 0;
            dp[i][j] = (prefix[j] - left + MOD) % MOD;
        }
    }

    cout << dp[n][k] % MOD << "\n";
    return 0;
}
