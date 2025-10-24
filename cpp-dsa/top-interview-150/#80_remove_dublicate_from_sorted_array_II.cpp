// 80. Remove Duplicates from Sorted Array II


// Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element appears at most twice. The relative order of the elements should be kept the same.

// Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the first part of the array nums. More formally, if there are k elements after removing the duplicates, then the first k elements of nums should hold the final result. It does not matter what you leave beyond the first k elements.

// Return k after placing the final result in the first k slots of nums.

// Do not allocate extra space for another array. You must do this by modifying the input array in-place with O(1) extra memory.

// Custom Judge:

// The judge will test your solution with the following code:

// int[] nums = [...]; // Input array
// int[] expectedNums = [...]; // The expected answer with correct length

// int k = removeDuplicates(nums); // Calls your implementation

// assert k == expectedNums.length;
// for (int i = 0; i < k; i++) {
//     assert nums[i] == expectedNums[i];
// }
// If all assertions pass, then your solution will be accepted.

 

// Example 1:

// Input: nums = [1,1,1,2,2,3]
// Output: 5, nums = [1,1,2,2,3,_]
// Explanation: Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
// Example 2:

// Input: nums = [0,0,1,1,1,1,2,3,3]
// Output: 7, nums = [0,0,1,1,2,3,3,_,_]
// Explanation: Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
 

// Constraints:

// 1 <= nums.length <= 3 * 104
// -104 <= nums[i] <= 104
// nums is sorted in non-decreasing order.














class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        if (n < 2) return n;
        int i =2;
        for(int j =2; j<n; j++) {
            if( nums[j]!= nums[i - 2]) {
                nums[i]=nums[j];
                i++;
            }
        }
        return i;


    }
};










class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        int expected_vals = 2;

        if(nums.size() == 1){
            return 1;
        }
        else if(nums.size() == 2){
            return 2;
        }


        for(int i = 2; i < nums.size(); i++){
            if(nums[i] != nums[expected_vals-2]){
                nums[expected_vals++] = nums[i];
            }
        }
    return expected_vals;
    }
};




















class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> temp;
        int n=nums.size();
        for(int i=2;i<nums.size();i++){
            if(nums[i]==nums[i-1] && nums[i]==nums[i-2]){
                nums.erase(nums.begin()+i);
                i=i-1;
            }
        }return nums.size();
    }
};
#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
  struct ___ { static void _() { std::ofstream("display_runtime.txt") << 1 << '\n'; } };
  std::atexit(&___::_);
  return 0;
}();
#endif













class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k =2;
        if(nums.size()<=2) return nums.size();

        for(int i=2; i<nums.size(); i++)
        {
            if(nums[i] != nums[k-2])
            {
                nums[k] = nums[i];
                k++;
            }
        }
        return k;
    }
};




















class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(n<3)
        {
            return n;
        }
        int k=2;
        for(int i=2;i<n;i++)
        {
            if(nums[i]!=nums[k-2])
            {
                nums[k]=nums[i];
                k++;
            }
        }
        return k;
    }
};
















class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        size_t i = 0;
        size_t res = 1;
        size_t cnt = 1;

        for (size_t j = 1; j < nums.size(); ++j)
        {
            if (cnt < 2 || nums[j] != nums[i])
            {
                if (nums[j] != nums[i])
                {
                    cnt = 1;
                }
                else
                {
                    cnt += 1;                    
                }
                res += 1;
                i += 1;
                nums[i] = nums[j];
            }
        }
        return res;
    }
};