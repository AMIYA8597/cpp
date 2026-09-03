3876. Construct Uniform Parity Array II
Medium
Topics
premium lock icon
Companies
Hint
You are given an array nums1 of n distinct integers.

You want to construct another array nums2 of length n such that the elements in nums2 are either all odd or all even.

For each index i, you must choose exactly one of the following (in any order):

nums2[i] = nums1[i]​​​​​​​
nums2[i] = nums1[i] - nums1[j], for an index j != i, such that nums1[i] - nums1[j] >= 1
Return true if it is possible to construct such an array, otherwise return false.

 

Example 1:

Input: nums1 = [1,4,7]

Output: true

Explanation:​​​​​​​​​​​​​​

Set nums2[0] = nums1[0] = 1.
Set nums2[1] = nums1[1] - nums1[0] = 4 - 1 = 3.
Set nums2[2] = nums1[2] = 7.
nums2 = [1, 3, 7], and all elements are odd. Thus, the answer is true.
Example 2:

Input: nums1 = [2,3]

Output: false

Explanation:

It is not possible to construct nums2 such that all elements have the same parity. Thus, the answer is false.

Example 3:

Input: nums1 = [4,6]

Output: true

Explanation:

Set nums2[0] = nums1[0] = 4.
Set nums2[1] = nums1[1] = 6.
nums2 = [4, 6], and all elements are even. Thus, the answer is true.
 

Constraints:

1 <= n == nums1.length <= 105
1 <= nums1[i] <= 109
nums1 consists of distinct integers.






















 class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int smallestOdd = INT_MAX;

        for (int x : nums1) {
            if (x % 2 == 1) {
                smallestOdd = min(smallestOdd, x);
            }
        }

        if (smallestOdd == INT_MAX) {
            return true;
        }

        for (int x : nums1) {
            if (x % 2 == 0 && x <= smallestOdd) {
                return false;
            }
        }

        return true;
    }
};
























class Solution {
public:
    bool uniformArray(vector<int>& arr) {
        int n=arr.size();
        int e=0;
        int o=0;
        int smallest_odd=INT_MAX;
        for(int i=0;i<n;i++){
            if(arr[i]%2==0) e++;
            else {
                o++;
                smallest_odd=min(smallest_odd,arr[i]);
            }
        }
        if(e==n) return true;
        else if(o==n) return true;
        else {
           for(int i=0;i<n;i++){
               if(arr[i] % 2==0){
                   if(arr[i]<smallest_odd) return false;
               }
           } 
        }
    return true;
    }
};

























class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n=nums1.size(),mn=INT_MAX;
        for (int i:nums1) {
            if ((i%2) == 1) {
                mn = min(mn, i);
            }
        }
        if (mn == INT_MAX)return true;
        for (int x : nums1) {
            if (x % 2 == 0 && x < mn)
            return false;
        }
        return true;
    }
};





















class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());
        if (mn % 2 == 1)
            return true;
        for (int x : nums1) {
            if (x % 2 == 1)
                return false;
        }
        return true;
    }
};






















class Solution {
public:
bool uniformArray(vector<int>& nums1) {
    int mn = *min_element(nums1.begin(), nums1.end());
    if (mn & 1) return true; 
    for (int x : nums1) {
        if (x & 1) return false;
    }
    return true; 
}
};
