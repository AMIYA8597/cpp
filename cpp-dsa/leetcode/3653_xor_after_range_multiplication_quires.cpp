3653. XOR After Range Multiplication Queries I


You are given an integer array nums of length n and a 2D integer array queries of size q, where queries[i] = [li, ri, ki, vi].

For each query, you must apply the following operations in order:

Set idx = li.
While idx <= ri:
Update: nums[idx] = (nums[idx] * vi) % (109 + 7)
Set idx += ki.
Return the bitwise XOR of all elements in nums after processing all queries.

 

Example 1:

Input: nums = [1,1,1], queries = [[0,2,1,4]]

Output: 4

Explanation:

A single query [0, 2, 1, 4] multiplies every element from index 0 through index 2 by 4.
The array changes from [1, 1, 1] to [4, 4, 4].
The XOR of all elements is 4 ^ 4 ^ 4 = 4.
Example 2:

Input: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]

Output: 31

Explanation:

The first query [1, 4, 2, 3] multiplies the elements at indices 1 and 3 by 3, transforming the array to [2, 9, 1, 15, 4].
The second query [0, 2, 1, 2] multiplies the elements at indices 0, 1, and 2 by 2, resulting in [4, 18, 2, 15, 4].
Finally, the XOR of all elements is 4 ^ 18 ^ 2 ^ 15 ^ 4 = 31.​​​​​​​​​​​​​​
 

Constraints:

1 <= n == nums.length <= 103
1 <= nums[i] <= 109
1 <= q == queries.length <= 103
queries[i] = [li, ri, ki, vi]
0 <= li <= ri < n
1 <= ki <= n
1 <= vi <= 105









class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        
        for (auto& q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = (1LL * nums[idx] * v) % MOD;
            }
        }

        int result = 0;
        for (int x : nums) result ^= x;
        return result;
        
    }
};































class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        
        // Process each query sequentially
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];
            
            // Step through the array with stride k
            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = (1LL * nums[idx] * v) % MOD;
            }
        }
        
        // Calculate the final XOR sum
        int result = 0;
        for (int val : nums) {
            result ^= val;
        }
        
        return result;
    }
};






class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int ans = 0;
        int n = nums.size();
        int m = queries.size();

        int cnt = 0;
        int tp = pow(10,9)+7;
        while(cnt < m){
            int left =  queries[cnt][0];
            int right =  queries[cnt][1];
            int k = queries[cnt][2];
            int x = queries[cnt][3];

            int idx = left;
            while(idx <= right){
                long long temp = nums[idx];
                temp *= x;
                temp %= tp;
                nums[idx] = (int)temp;
                idx += k;
            }
            cnt++;
        }
        for(int i=0;i<n;i++){
            ans ^= nums[i];
        }
        return ans;
    }
};































class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        const long long MOD = 1e9 + 7;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            long long v = q[3];

            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = (nums[idx] * v) % MOD;
            }
        }

        long long ans = 0;
        for (auto &x : nums) {
            ans ^= x;
        }

        return ans;
        
    }
};





























class Solution {
public:
    const static int mod = 1e9+7;
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        for( auto &q : queries){
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];
            for(int idx = l; idx<=r;idx+=k){
                nums[idx] = ((long long)nums[idx] * v) % mod;
            }
        }
        int ret =0;
        for(auto &val : nums){
            ret= ret ^ val;
        }
        return ret;
    }
};


































class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = int(1e9)+7;
        for(const auto& q : queries){
            int l = q[0], r = q[1], k = q[2], v = q[3];
            int idx = l;
            while(idx <= r){
                nums[idx] = (1LL*nums[idx]*v)%MOD;
                idx += k;
            }
        }
        int res = 0;
        for(int i : nums){
            res = res^i;
        }
        return res;
    }
};





























CPP solve it
