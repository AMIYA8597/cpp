3740. Minimum Distance Between Three Equal Elements I



You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

 

Example 1:

Input: nums = [1,2,1,1,3]

Output: 6

Explanation:

The minimum distance is achieved by the good tuple (0, 2, 3).

(0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

Example 2:

Input: nums = [1,1,2,3,2,1,2]

Output: 8

Explanation:

The minimum distance is achieved by the good tuple (2, 4, 6).

(2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

Example 3:

Input: nums = [1]

Output: -1

Explanation:

There are no good tuples. Therefore, the answer is -1.

 

Constraints:

1 <= n == nums.length <= 100
1 <= nums[i] <= n






























  class Solution {
public:
    int minimumDistance(vector<int>& nums) {
         unordered_map<int, vector<int>> mp;
        
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }
        
        int ans = INT_MAX;
        
        for (auto &it : mp) {
            vector<int> &v = it.second;
            
            if (v.size() < 3) continue;
            
            for (int i = 0; i + 2 < v.size(); i++) {
                int dist = 2 * (v[i + 2] - v[i]);
                ans = min(ans, dist);
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};




























class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n=nums.size(),mini=1e9;

        for(int i=0;i<n-2;i++){
            for(int j=i+1;j<n-1;j++){
                for(int k=j+1;k<n;k++){
                    if(nums[i]==nums[j] && nums[j]==nums[k]){
                        int dist=abs(i-j)+abs(j-k)+abs(k-i);
                        mini=min(mini,dist);
                    }
                }
            }
        }

        return mini==1e9?-1:mini;
    }
};





























class Solution {
public:
    int fn(vector<int>& a){
        int n=a.size();
        int i=0,j=0;
        int mini=INT_MAX;
        for(int i=0;i<n;i++){
            if(i-j+1==3){
                mini=min(mini,2*abs(a[j]-a[i]));
                j++;
            }
        }
        return mini;
    }
    int minimumDistance(vector<int>& a) {
     //   0 , 2 , 9  = 
        // 5 3 5 5 5 = 0 , 2 
        int n=a.size();
        map<int,vector<int>>mp;
        for(int i=0;i<a.size();i++){
            mp[a[i]].push_back(i);
        }
        
        int mini=INT_MAX;
        for(auto it : mp){
            vector<int>sze= it.second;
            if(sze.size()<3)continue;
            int ele =fn(sze);
            cout<<ele<<endl;
            mini=min(mini,ele);
        }
        return  mini==INT_MAX?-1:mini;
    }
};





























class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        int mn = INT_MAX;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] == nums[j] && nums[j] == nums[k]) {
                        mn = min(mn, 2 * (k - i));
                    }
                }
            }
        }

        return (mn == INT_MAX ? -1 : mn);
    }
};







































class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        int mini_dist = INT_MAX;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k = j+1;k<n;k++){
                    if(nums[i] == nums[j] && nums[j] == nums[k] ){
                        int dist = abs(i-j) + abs(j-k) + abs(k-i);
                         mini_dist = min(mini_dist,dist);
                    }
                }
            }
        }
        return (mini_dist == INT_MAX) ? -1 : mini_dist;
    }
};
