// 34. Find First and Last Position of Element in Sorted Array


// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

// If target is not found in the array, return [-1, -1].

// You must write an algorithm with O(log n) runtime complexity.

 

// Example 1:

// Input: nums = [5,7,7,8,8,10], target = 8
// Output: [3,4]
// Example 2:

// Input: nums = [5,7,7,8,8,10], target = 6
// Output: [-1,-1]
// Example 3:

// Input: nums = [], target = 0
// Output: [-1,-1]
 

// Constraints:

// 0 <= nums.length <= 105
// -109 <= nums[i] <= 109
// nums is a non-decreasing array.
// -109 <= target <= 109














class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {

        int first = -1, last = -1;
        int low = 0;
        int high = nums.size() - 1;
        int answer = -1;

        while(low <= high ) {
            int middle = (low + high) / 2;

            if(nums[middle]== target) {
                first = middle;
                high = middle -1;

            }
            else if(nums[middle] < target) {
                low = middle + 1;
            }

            else {
                high = middle -1;
            }
        }

        low = 0, high = nums.size() - 1;
        while (low <= high) {
            int middle = (low + high) / 2;
            if (nums[middle] == target) {
                last = middle;
                low = middle + 1;
            }
            else if (nums[middle] < target) {
                low = middle + 1;
            }
            else {
                high = middle - 1;
            }
        }

        return {first, last};

    }
        // return -1;
};






























class Solution {
public:
   int firstocc(vector<int>&nums,int target) {
    int low=0;
    int first=-1;
    int n=nums.size();
    int high=n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(nums[mid]==target){
            first=mid;
            high=mid-1;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return first;
   }

int lastocc(vector<int>&nums,int target) {
    int low=0;
    int last=-1;
    int n=nums.size();
    int high=n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(nums[mid]==target){
            last=mid;
            low=mid+1;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return last;
   }

    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> v;
        int first=firstocc(nums,target);
        if(first==-1) return {-1,-1};
        int last=lastocc(nums,target);
        v.push_back(first);
        v.push_back(last);
        return v;

    }
};




































class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // int n = nums.size();
        // int low = 0, high = n - 1;
        // vector<int> arr = {-1, -1};
        // while (low < high) {
        //     int mid = low + (high - low) / 2;
        //     if (nums[mid] < x) 
        //         low = mid + 1;
        //     else
        //         high = mid;
        // }
        // high = n - 1;
        // if(nums[low]!=x)return arr;
        // else arr[0]=low;
        // while (low < high) {
        //     int mid = low + (high - low) / 2+1;
        //     if(nums[mid]>x) high=mid-1;
        //     else low=mid;
        // }
        // arr[1]=high;
        // return arr;
        int low = 0, high = nums.size()-1;
        int startingPosition = lower_bound(nums.begin(),nums.end(), target)-nums.begin();
        int endingPosition = lower_bound(nums.begin(),nums.end(), target + 1)-nums.begin() - 1;
        if(startingPosition < nums.size() && nums[startingPosition] == target){
            return {startingPosition, endingPosition};
        }
        return {-1, -1};
    }
};




































class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0; 
        int high = nums.size() - 1;
        int mid;
        int floor = -1, ceil = -1;
        while(low <= high){
            mid = (low + high)  / 2;
            if(nums[mid] < target){
                low = mid + 1;
            }
            else if(nums[mid] == target){
                floor = mid;
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        mid = 0; low = 0; high = nums.size() - 1;
            while(low <= high){
            mid = (low + high) / 2;
            if(nums[mid] > target){
                high = mid - 1;
            }
            else if(nums[mid] == target){
                ceil = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return {ceil,floor};
    }
};
































class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
       pair<int,int>p={-1,-1};
       int i,n=nums.size();
       for(i=0;i<n;i++)
       {
        if(target==nums[i])
        {
        p.first=i;
        break;
        }
       
       }
      for(i=n-1;i>=0;i--)
      {
        if (target==nums[i])
        {
            p.second=i;
            break;
        }
       
      }
       return {p.first,p.second};
    }
};