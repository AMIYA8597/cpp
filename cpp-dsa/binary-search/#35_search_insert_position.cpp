// 35. Search Insert Position




// premium lock icon
// Companies
// Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

// You must write an algorithm with O(log n) runtime complexity.

 

// Example 1:

// Input: nums = [1,3,5,6], target = 5
// Output: 2
// Example 2:

// Input: nums = [1,3,5,6], target = 2
// Output: 1
// Example 3:

// Input: nums = [1,3,5,6], target = 7
// Output: 4
 

// Constraints:

// 1 <= nums.length <= 104
// -104 <= nums[i] <= 104
// nums contains distinct values sorted in ascending order.
// -104 <= target <= 104













class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() -1;
        while (low <= high) {
            int middle = (low + high) / 2;

            if (nums[middle] == target) {
                return middle;
            }

            if(nums[middle] < target) {
                low = middle + 1;
            }

            else {
                high = middle -1;
            }
        }
        return low;
    }
};













class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        nums.push_back(target);
        sort(nums.begin(), nums.end());
        auto it = find(nums.begin(), nums.end(), target);
        return it - nums.begin();
        

        
    }
};





















class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = round((left + right) / 2);
      cout << left << "," << right << "," << mid << "0\n";
      if (nums[mid] == target) {
        cout << left << "," << right << "," << mid << "1\n";
        return mid;
      } else if (nums[mid] < target) {
        cout << left << "," << right << "," << mid << "2\n";
        left = mid + 1;
      } else {
        cout << left << "," << right << "," << mid << "3\n";
        right = mid - 1;
      }
    }
    return left;
  }
};

























int binary(vector<int> nums,int left,int right,int target){
    if(left>right){
        return left;
    }
    int mid = left + (right -left)/2;
    if(nums[mid] == target){
        return mid;
    }
    else if(nums[mid]>target){
        right = mid -1;
        return binary(nums,left,right,target);
    }
    else{
        left = mid+1;
        return binary(nums,left,right,target);
    }
}

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return binary(nums,0,nums.size()-1,target);
    }
};


















class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (target == nums[i]) {
                return i;
            }
        }

        nums.push_back(target);  
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {  
            if (target == nums[i]) {
                return i;
            }
        }
        return -1;
    }
};







