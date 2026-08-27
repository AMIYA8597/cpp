3718. Smallest Missing Multiple of K
Easy
Topics
premium lock icon
Companies
Hint
Given an integer array nums and an integer k, return the smallest positive multiple of k that is missing from nums.

A multiple of k is any positive integer divisible by k.

 

Example 1:

Input: nums = [8,2,3,4,6], k = 2

Output: 10

Explanation:

The multiples of k = 2 are 2, 4, 6, 8, 10, 12... and the smallest multiple missing from nums is 10.

Example 2:

Input: nums = [1,4,7,10,15], k = 5

Output: 5

Explanation:

The multiples of k = 5 are 5, 10, 15, 20... and the smallest multiple missing from nums is 5.

 

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
1 <= k <= 100




























  class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> st(nums.begin(), nums.end());

        int multiple = k;

        while (st.count(multiple)) {
            multiple += k;
        }

        return multiple;
    }
};

























class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> s(nums.begin(),nums.end());
        int m;
        for(m = 1;m<101;m+=1){
            if(!s.count(k*m)) break;
        }
        return m*k;
    }
};






















class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int>st;
        for(int num:nums) st.insert(num);
        int m=1;
        while(true){
            if(st.count(m*k)==0) return m*k;
            m++;
        }
        return 0;
    }
};

























class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {

        unordered_map<int, int> mpp;

        for(int i=0; i<nums.size(); i++){
            if(nums[i] % k == 0) mpp[nums[i]]++;
        }

        int cnt = 1;
        int product = 1;

        while(true){

            product = k * cnt;
            if(mpp.find(product) == mpp.end()) break;
            else cnt++;


        }

        return product;
        
    }
};






















class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int ans=0;
        unordered_map<int,int> mp;
        for(int i=0 ; i<nums.size() ; i++){
            mp[nums[i]]=1;
        }
        for(int i=k ; i>0 ; i+=k){
            if(mp[i]==0){
                return i;
            }
        }
        return 0;
    }
};















