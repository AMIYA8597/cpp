788. Rotated Digits
Medium
Topics
premium lock icon
Companies
An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

0, 1, and 8 rotate to themselves,
2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
6 and 9 rotate to each other, and
the rest of the numbers do not rotate to any other number and become invalid.
Given an integer n, return the number of good integers in the range [1, n].

 

Example 1:

Input: n = 10
Output: 4
Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Example 2:

Input: n = 1
Output: 0
Example 3:

Input: n = 2
Output: 1
 

Constraints:

1 <= n <= 104












































  class Solution {
public:
    int rotatedDigits(int n) {
        int count = 0;

        for (int i = 1; i <= n; i++) {
            int num = i;
            bool isValid = true;
            bool isGood = false;

            while (num > 0) {
                int digit = num % 10;

                if (digit == 3 || digit == 4 || digit == 7) {
                    isValid = false;
                    break;
                }

                if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
                    isGood = true;
                }

                num /= 10;
            }

            if (isValid && isGood) {
                count++;
            }
        }

        return count;
    }
};































class Solution {
public:
    inline const int rotatedDigits(
        const int& __n
    ) const noexcept {
        int __res{0};
        
        for( int __i{1}; __i <= __n; ++__i ) {
            int __temp{__i};
            int __pow{1};
            int __rot{0};

            while( __temp ) {
                int __dig{__temp % 10};
                if( 
                    __dig != 3 &&
                    __dig != 4 &&
                    __dig != 7
                ) {
                    if( __dig == 2 ) __rot += 5 * __pow;
                    else if( __dig == 5 ) __rot += 2 * __pow;
                    else if( __dig == 6 ) __rot += 9 * __pow;
                    else if( __dig == 9 ) __rot += 6 * __pow;
                    else __rot += __dig * __pow;
                    __pow *= 10; 
                    __temp /= 10;
                
                }
                else break;

            }

            if( !__temp && __rot != __i) {
                // cout << __rot << " " << __i << "\n";
                ++__res;
                
            }

        }

        return __res;

    }
};






















class Solution {
public:
    int rotatedDigits(int n) {
        vector<int> digits = {0, 1, 2, 5, 6, 8, 9};
        string s = to_string(n);
        // idx, tight, valid, started
        vector<vector<vector<vector<int>>>> dp(s.size(), vector<vector<vector<int>>>(2, vector<vector<int>> (2, vector<int>(2,-1))));

        return solve(s, 0, true, false, false, digits, dp);
    }

    int solve(string& s, int idx, bool tight, bool valid, bool started, vector<int>& digits, vector<vector<vector<vector<int>>>>& dp) {
        if(idx == s.size()) return valid;

        if(dp[idx][tight][valid][started] != -1) return dp[idx][tight][valid][started];

        int ans = 0;
        int limit = tight ? s[idx] - '0' : 9;
        for(int i: digits) {
            if(i > limit) break;
            int ntight = tight && (i == limit);
            if(!started && i == 0) {
                ans += solve(s, idx + 1, ntight, false, false, digits, dp);
            }
            else if(!valid && (i == 0 || i == 1 || i == 8)) {
                ans += solve(s, idx + 1, ntight, false, true, digits, dp);
            }
            else {
                ans += solve(s, idx + 1, ntight, true, true, digits, dp);
            }
        }
        return dp[idx][tight][valid][started] = ans;
    }
};
































#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rotatedDigits(int n) {
        unordered_set<int> same = {0,1,8};
        unordered_set<int> diff = {2,5,6,9};
        
        int ans = 0;
        
        for (int i = 1; i <= n; i++) {
            int x = i;
            bool ok = true, changed = false;
            
            while (x > 0) {
                int d = x % 10;
                if (!same.count(d) && !diff.count(d)) {
                    ok = false;
                    break;
                }
                if (diff.count(d)) changed = true;
                x /= 10;
            }
            
            if (ok && changed) ans++;
        }
        
        return ans;
    }
};
