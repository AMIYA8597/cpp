#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n=nums.size();
        int left=0;
        int right=n-1;
        
        while(left<=right){
            int mid = left + (right-left)/2;

            if(nums[mid]==target) return true;
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                left++;
                right--;
            }
            else if(nums[mid]<=nums[right]){
                if(nums[mid]<=target && target<=nums[right]){
                    left=mid+1;
                }
                else right=mid-1;
            }
            else if(nums[left]<=nums[mid]){
                if(nums[left]<=target && target<=nums[mid]){
                    right=mid-1;
                }
                else left=mid+1;
            }

        }

        return false;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {2,5,6,0,0,1,2};
    int target = 0;
    bool result = sol.search(nums, target);
    cout << (result ? "true" : "false") << endl; // Output: true
    return 0;

}