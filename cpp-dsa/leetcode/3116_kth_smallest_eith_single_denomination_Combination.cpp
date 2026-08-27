3116. Kth Smallest Amount With Single Denomination Combination
Hard
Topics
premium lock icon
Companies
Hint
You are given an integer array coins representing coins of different denominations and an integer k.

You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.

Return the kth smallest amount that can be made using these coins.

 

Example 1:

Input: coins = [3,6,9], k = 3

Output: 9

Explanation: The given coins can make the following amounts:
Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
All of the coins combined produce: 3, 6, 9, 12, 15, etc.

Example 2:

Input: coins = [5,2], k = 7

Output: 12

Explanation: The given coins can make the following amounts:
Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
All of the coins combined produce: 2, 4, 5, 6, 8, 10, 12, 14, 15, etc.

 

Constraints:

1 <= coins.length <= 15
1 <= coins[i] <= 25
1 <= k <= 2 * 109
coins contains pairwise distinct integers.



























  class Solution {
public:
    using int64 = long long;
    using i128 = __int128_t;

    long long gcdll(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long lcmLimited(long long a, long long b, long long limit) {
        long long g = gcdll(a, b);

        // a / gcd(a,b) * b
        i128 l = (i128)(a / g) * b;

        if (l > limit)
            return limit + 1;

        return (long long)l;
    }

    long long count(long long x, vector<int>& coins) {
        int m = coins.size();
        long long total = 0;

        // Inclusion-exclusion over all subsets.
        for (int mask = 1; mask < (1 << m); mask++) {
            long long lcm = 1;
            bool valid = true;
            int bits = 0;

            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    lcm = lcmLimited(lcm, coins[i], x);

                    if (lcm > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            long long ways = x / lcm;

            if (bits % 2 == 1)
                total += ways;
            else
                total -= ways;
        }

        return total;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        // Remove redundant denominations.
        //
        // If a coin a divides coin b, every multiple of b
        // is already a multiple of a, so b is unnecessary.
        sort(coins.begin(), coins.end());

        vector<int> useful;

        for (int c : coins) {
            bool redundant = false;

            for (int x : useful) {
                if (c % x == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                useful.push_back(c);
        }

        coins = useful;

        // The answer cannot be greater than k * smallest coin.
        long long low = 1;
        long long high = (long long)coins[0] * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid, coins) >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};






















#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, vector<long long>> subsetLcmBySize;

    long long gcd(long long a, long long b) {
        return std::gcd(a, b);
    }

    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    vector<int> filterRedundantCoins(vector<int>& coins) {
        int n = coins.size();
        vector<bool> keep(n, true);

        for (int i = 0; i < n; i++) {
            if (!keep[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (coins[j] % coins[i] == 0) {
                    keep[j] = false;
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (keep[i]) result.push_back(coins[i]);
        }
        return result;
    }

    void precomputeSubsetLcms(const vector<int>& nums, int n) {
        subsetLcmBySize.clear();
        for (int i = 1; i <= n; i++) {
            subsetLcmBySize[i] = vector<long long>();
        }

        for (int mask = 1; mask < (1 << n); mask++) {
            int subsetSize = 0;
            long long currentLcm = 1;

            for (int bit = 0; bit < n; bit++) {
                if ((mask >> bit) & 1) {
                    subsetSize++;
                    currentLcm = lcm(currentLcm, nums[bit]);
                }
            }
            subsetLcmBySize[subsetSize].push_back(currentLcm);
        }
    }

    long long countMultiples(long long target, int n) {
        long long totalCount = 0;
        int sign = 1;

        for (int size = 1; size <= n; size++) {
            if (subsetLcmBySize.find(size) == subsetLcmBySize.end()) continue;
            for (long long lcmVal : subsetLcmBySize[size]) {
                totalCount += sign * (target / lcmVal);
            }
            sign = -sign;
        }

        return totalCount;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());

        vector<int> uniqueCoins = filterRedundantCoins(coins);
        int n = uniqueCoins.size();

        precomputeSubsetLcms(uniqueCoins, n);

        long long low = uniqueCoins[0];
        long long high = 1LL * uniqueCoins[0] * k;
        long long answer = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long count = countMultiples(mid, n);

            if (count >= k) {
                answer = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return answer;
    }
};






















class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        vector<int> c;
        for (int x : coins) {
            bool keep = true;
            for (int y : c) {
                if (x % y == 0) {
                    keep = false;
                    break;
                }
            }
            if (keep) {
                c.push_back(x);
            }
        }

        int n = c.size();
        int m = 1 << n;
        vector<long long> lcm_val(m, 1);
        vector<int> bits(m, 0);

        for (int mask = 1; mask < m; mask++) {
            int pre = mask & (mask - 1);
            int i = __builtin_ctz(mask);
            bits[mask] = bits[pre] + 1;
            
            long long g = std::__gcd(lcm_val[pre], (long long)c[i]);
            long long tmp = lcm_val[pre] / g;
            if (tmp <= (1LL * c[0] * k + 1) / c[i]) {
                lcm_val[mask] = tmp * c[i];
            } else {
                lcm_val[mask] = 1LL * c[0] * k + 2;
            }
        }

        auto count = [&](long long target) {
            long long cnt = 0;
            for (int mask = 1; mask < m; mask++) {
                if (lcm_val[mask] <= target) {
                    if (bits[mask] & 1) {
                        cnt += target / lcm_val[mask];
                    } else {
                        cnt -= target / lcm_val[mask];
                    }
                }
            }
            return cnt;
        };

        long long low = 1, high = 1LL * c[0] * k, ans = high;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (count(mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};


























class Solution {
public:
    using ll = long long;
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        int m = (1 << n);
        sort(coins.begin(), coins.end());
        vector<int> bit_count(m);
        vector<ll> lcm(m);
        ll l = k, r = 1ll * coins[0] * k + 1;

        for (int mask = 1; mask < m; mask++) {
            ll cur_lcm = 1;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    ll tmp = cur_lcm / gcd(cur_lcm, coins[i]);
                    if (tmp <= r / coins[i]) {
                        cur_lcm = tmp * coins[i];
                    } else {
                        cur_lcm = r + 1;
                        break;
                    }
                    bit_count[mask]++;
                }
            }
            lcm[mask] = cur_lcm;
        }

        auto get = [&](ll x) -> ll {
            ll count = 0;
            for (int mask = 1; mask < m; mask++) {
                if (lcm[mask] > x) {
                    continue;
                }
                if (bit_count[mask] & 1) {
                    count += x / lcm[mask];
                } else {
                    count -= x / lcm[mask];
                }
            }
            return count;
        };

        while (l < r) {
            ll x = (l + r) >> 1;
            if (get(x) >= k) {
                r = x;
            } else {
                l = x + 1;
            }
        }
        return l;
    }
};
