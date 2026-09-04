3903. Smallest Stable Index I
Easy
Topics
premium lock icon
Companies
Hint
You are given an integer array nums of length n and an integer k.

For each index i, define its instability score as max(nums[0..i]) - min(nums[i..n - 1]).

In other words:

max(nums[0..i]) is the largest value among the elements from index 0 to index i.
min(nums[i..n - 1]) is the smallest value among the elements from index i to index n - 1.
An index i is called stable if its instability score is less than or equal to k.

Return the smallest stable index. If no such index exists, return -1.

 

Example 1:

Input: nums = [5,0,1,4], k = 3

Output: 3

Explanation:

At index 0: The maximum in [5] is 5, and the minimum in [5, 0, 1, 4] is 0, so the instability score is 5 - 0 = 5.
At index 1: The maximum in [5, 0] is 5, and the minimum in [0, 1, 4] is 0, so the instability score is 5 - 0 = 5.
At index 2: The maximum in [5, 0, 1] is 5, and the minimum in [1, 4] is 1, so the instability score is 5 - 1 = 4.
At index 3: The maximum in [5, 0, 1, 4] is 5, and the minimum in [4] is 4, so the instability score is 5 - 4 = 1.
This is the first index with an instability score less than or equal to k = 3. Thus, the answer is 3.
Example 2:

Input: nums = [3,2,1], k = 1

Output: -1

Explanation:

At index 0, the instability score is 3 - 1 = 2.
At index 1, the instability score is 3 - 1 = 2.
At index 2, the instability score is 3 - 1 = 2.
None of these values is less than or equal to k = 1, so the answer is -1.
Example 3:

Input: nums = [0], k = 0

Output: 0

Explanation:

At index 0, the instability score is 0 - 0 = 0, which is less than or equal to k = 0. Therefore, the answer is 0.

 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 109
0 <= k <= 109
























  class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
      int n = nums.size();

        vector<int> prefixMax(n);
        vector<int> suffixMin(n);

        prefixMax[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
        }

        suffixMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        }

        for (int i = 0; i < n; i++) {
            if (prefixMax[i] - suffixMin[i] <= k) {
                return i;
            }
        }

        return -1;  
    }
};

























class Solution {
public:
    int firstStableIndex(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int>p(n);
        p[0]=arr[0];
        for(int i=1;i<n;i++)
            {
                if(arr[i]>p[i-1])
                {
                    p[i]=arr[i];
                }
                else
                {
                    p[i]=p[i-1];
                }
            }

        vector<int>s(n);
        s[n-1]=arr[n-1];

        for(int i=n-2;i>=0;i--)
            {
                if(arr[i]<s[i+1])
                {
                    s[i]=arr[i];
                }
                else
                {
                    s[i]=s[i+1];
                }
            }

        
        for(int i=0;i<n;i++)
            {
                if(p[i]-s[i]<=k)
                {
                    return i;
                }
            }
        return -1;
    }
};



























class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        for(int i = 0; i < nums.size(); i++){
            int a = 0, b = INT_MAX;
            for(int j = 0; j <= i; j++) a = max(a, nums[j]);
            for(int j = i; j < nums.size(); j++) b = min(b, nums[j]);
            if(a - b <= k) return i;
        }
        return -1;
    }
};


























class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int ans=1e9+4;
        int n=nums.size();
        vector<int>pre(n);
        vector<int>suf(n);
        int c=0;
        int c1=1e9+4;
        for(int i=0;i<n;++i){
            c=max(c,nums[i]);
            pre[i]=c;
            c1=min(c1,nums[n-i-1]);
            suf[n-i-1]=c1;
        }
        for(int i=0;i<n;++i){
            if(pre[i]-suf[i]<=k)ans=min(ans,i);
        }
        if(ans==1e9+4)return -1;return ans;
    }
};





















class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> prefixmax(n,INT_MIN);
        vector<int> suffixmin(n,INT_MAX);

        prefixmax[0]=nums[0];
        suffixmin[n-1]=nums[n-1];

        for(int i=1;i<n;i++)
            {
                prefixmax[i]=max(nums[i],prefixmax[i-1]);
            }
        for(int i=n-2;i>=0;i--)
            {
                suffixmin[i]=min(nums[i],suffixmin[i+1]);
            }

        int idx=n;
        for(int i=0;i<n;i++)
            {
                int score=prefixmax[i]-suffixmin[i];
                if(score<=k)
                {
                    idx=min(idx,i);
                }
            }
        return idx==n?-1:idx;
    }
};






















class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        if(nums.size() == 1) return 0;
        vector<int> smallest(nums.size());
        vector<int> maxim(nums.size());
        int mini = nums[nums.size()-1],maxi = nums[0];
        for(int i=0;i<nums.size();i++){
            maxi = max(maxi,nums[i]);
            maxim[i] = maxi;
        }
        for(int i=nums.size()-1;i>=0;i--){
            mini = min(mini,nums[i]);
            smallest[i] = mini;
        }
        int ans = INT_MAX;
        for(int i=0;i<nums.size();i++){
            if(maxim[i]-smallest[i] <= k) ans = min(ans,i);
        }
        return ans == INT_MAX? -1 : ans;
    }
};
