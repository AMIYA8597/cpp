// 704. Binary Search



// premium lock icon
// Companies
// Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

// You must write an algorithm with O(log n) runtime complexity.

 

// Example 1:

// Input: nums = [-1,0,3,5,9,12], target = 9
// Output: 4
// Explanation: 9 exists in nums and its index is 4
// Example 2:

// Input: nums = [-1,0,3,5,9,12], target = 2
// Output: -1
// Explanation: 2 does not exist in nums so return -1
 

// Constraints:

// 1 <= nums.length <= 104
// -104 < nums[i], target < 104
// All the integers in nums are unique.
// nums is sorted in ascending order.








class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() -1;
        while (low <=high) {
            int middle = (low + high)  /2;
            if (nums[middle] == target) {
                return middle;
            }
            if (nums[middle] < target) {
                low = middle + 1;
            }
            else {
                high = middle -1;
            }
        }
        return -1;
    }
};
























class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int first = 0, last = n-1;
        int mid;
        int ans = -1;

        while(first<=last)
        {
            mid = (first+last)/2;
            if(nums[mid] == target)
            {
                ans = mid;
                break;
            }
            if(nums[mid] > target)
            {
                last--;
            }
            else
            {
                first++;
            }
        }

        return ans;
    }
};















class Solution {
public:
    int search(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right) {
            // calculate mid index
            int mid = (left + right) / 2;
            // found the result
            if(nums[mid] == target) return mid;
            // target on the right side
            else if(nums[mid] < target) left = mid + 1;
            // target on the left side
            else if(nums[mid] > target) right = mid - 1;
        }
        return -1;
    }
};











