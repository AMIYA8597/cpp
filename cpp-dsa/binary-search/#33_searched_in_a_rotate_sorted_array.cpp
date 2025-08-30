// 33. Search in Rotated Sorted Array




// There is an integer array nums sorted in ascending order (with distinct values).

// Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

// Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

// You must write an algorithm with O(log n) runtime complexity.

 

// Example 1:

// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
// Example 2:

// Input: nums = [4,5,6,7,0,1,2], target = 3
// Output: -1
// Example 3:

// Input: nums = [1], target = 0
// Output: -1
 

// Constraints:

// 1 <= nums.length <= 5000
// -104 <= nums[i] <= 104
// All values of nums are unique.
// nums is an ascending array that is possibly rotated.
// -104 <= target <= 104















class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() -1;
        while (low <= high) {
            int middle = (low + high)/ 2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[low] <= nums[middle]) {
                if (nums[low] <= target && target < nums[middle]){
                    high = middle -1;
                }
                else {
                    low = middle +1 ;
                }
            } else {
                if(nums[middle] < target && target <= nums[high]) {
                    low = middle +1;
                } else {
                    high = middle -1;
                }
            }
        }
        return -1;
    }
};




























class Solution {
public:
    int search(vector<int>& nums, int target) {
     int ans=-1;
        for(int i=0;i<nums.size();i++){
             if(nums[i]==target){
                 return i;
             }
        }
        return -1;
    }
};



















class Solution {
public:
    int search(vector<int>& nums, int k) {
        int start = 0;
        int end = nums.size() - 1;
        int ans = -1;
        while(start <= end) {
            int mid = start + (end - start)/2;
            cout << "x: " <<mid;
            if(nums[mid] == k) {
                return mid;
            }
            else if(nums[mid] >= nums[start]) {
                if(nums[start] <= k && k <= nums[mid]) end = mid - 1;
                else start = mid + 1;
            } else {
                if(nums[mid] <= k && k <= nums[end]) start = mid + 1;
                else end = mid - 1;
            }
        }
        return -1;
    }
};
































#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;                         // start pointer
        int high = nums.size() - 1;          // end pointer

        while (low <= high) {                // binary search loop
            int middle = (low + high) / 2;   // mid element index

            // 🎯 Case 1: Found the target
            if (nums[middle] == target) {
                return middle;
            }

            // Case 2: Left half [low..middle] is sorted
            if (nums[low] <= nums[middle]) {
                // If target lies in the sorted left half
                if (nums[low] <= target && target < nums[middle]) {
                    high = middle - 1;       // search in left half
                } else {
                    low = middle + 1;        // otherwise search in right half
                }
            }
            // Case 3: Right half [middle..high] is sorted
            else {
                // ✅ FIXED: must be `<= nums[high]` not `< nums[high]`
                if (nums[middle] < target && target <= nums[high]) {
                    low = middle + 1;        // search in right half
                } else {
                    high = middle - 1;       // otherwise search in left half
                }
            }
        }

        // Case 4: Not found
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4,5,6,7,0,1,2};
    cout << sol.search(nums, 0) << endl;  // Output: 4
    cout << sol.search(nums, 3) << endl;  // Output: -1
    cout << sol.search(nums, 2) << endl;  // Output: 6 ✅ fixed
}




















