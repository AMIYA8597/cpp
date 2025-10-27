// B. Candy Purchase
// time limit per test1 second
// memory limit per test256 megabytes
// A group of K
//  friends wants to buy all the candies from a list with original prices given by the array C
// .

// The candy store uses a unique dynamic pricing rule based on customer loyalty: If a friend has already purchased p
//  candies, their next candy's price will be the original price multiplied by (p+1)
// .

// Essentially:

// The 1st candy a friend buys has a ×1
//  multiplier.
// The 2nd candy a friend buys has a ×2
//  multiplier.
// The 3rd candy a friend buys has a ×3
//  multiplier, and so on.
// The friends must divide all the candies among themselves to achieve the lowest possible total cost. Given the number of friends K
//  and the array of original candy prices C
// , what is the minimum total cost to purchase all the candies?

// Input
// The first line contains two space-separated integers N
//  and K
//  (1≤N,K≤105
// ) — representing the number of candies and the number of friends, respectively.

// The second line contains N
//  space-separated integers C1,C2,…,CN
//  (1≤Ci≤106
// ) — representing the original prices of the candies.

// Output
// Print a single line containing one integer — the minimum total cost to purchase all the candies.

// Example
// InputCopy
// 6 3
// 3 2 5 1 4 6
// OutputCopy
// 27
// Note
// For example, when n=6
//  and k=3
// , one possible combination to get the minimum cost is:

   
// Friend 1 bought C3
//  then C1
// : 1×5+2×3
    
// Friend 2 bought C5
//  then C2
// : 1×4+2×2
    
// Friend 3 bought C6
//  then C4
// : 1×6+2×1
// Thus, giving a minimum total cost of purchase of 27
// .


















#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];

    sort(c.rbegin(), c.rend());

    long long total_cost = 0;
    vector<int> count(k, 0); 
    for (int i = 0; i < n; ++i) {
        int friend_index = i % k; 
        total_cost += 1LL * (count[friend_index] + 1) * c[i];
        count[friend_index]++;
    }

    cout << total_cost << "\n";
    return 0;
}
