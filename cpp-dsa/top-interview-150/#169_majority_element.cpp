// 169. Majority Element


// Given an array nums of size n, return the majority element.

// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

// Example 1:

// Input: nums = [3,2,3]
// Output: 3
// Example 2:

// Input: nums = [2,2,1,1,1,2,2]
// Output: 2
 

// Constraints:

// n == nums.length
// 1 <= n <= 5 * 104
// -109 <= nums[i] <= 109


















// int main() {
//     Solution sol;
//     vector<int> nums = {2, 2, 1, 1, 1, 2, 2};  // You can modify this input

//     int result = sol.majorityElement(nums);
//     cout << "Majority Element: " << result << endl;

//     return 0;
// }


#include <iostream>
#include <vector>
using namespace std;



class Solution {
public:    
    int majorityElement(vector<int>& nums) {
        int count =0;
        int candidate =0;
        for(int num: nums) {
            if (count ==0) {
                candidate = num;
            }    
            count += (num == candidate) ? 1: -1;
        }    
        return candidate;
    }    
};    




int main() {
    Solution sol;
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2,6,6,5,6,5,6,7,8,7,8,75,6,5,6,5,6,5,6,5};  // You can modify this input

    int result = sol.majorityElement(nums);
    cout << "Majority Element: " << result << endl;

    return 0;
}










// class Solution {
// public:
//     void merge(vector<int>& arr, vector<int>& temp, int start, int mid, int end){
//         int left = start;
//         int right= mid+1;
//         int k=start;
//         while (left<=mid && right <=end){
//             if(arr[left]<arr[right]){
//                 temp[k++]=arr[left++];
//             }
//             else{
//                 temp[k++]=arr[right++];
//             }
//         }
//         while(left<=mid){
//             temp[k++]=arr[left++];
//         }
//         while (right<=end){
//             temp[k++]=arr[right++];
//         }

//         for(int i=start; i<=end;i++){
//             arr[i]=temp[i];
//         }
//     }
//     void mergeSort(vector<int>& arr, vector<int>& temp, int start, int end){
//         if(start>=end) return;
//         int mid= start+(end-start)/2;
//         mergeSort(arr, temp, start, mid);
//         mergeSort(arr, temp, mid+1, end);
//         merge(arr, temp, start, mid,end);

//     }

//     int majorityElement(vector<int>& nums) {
//         int n=nums.size();
//         vector<int> temp(n);
//         mergeSort(nums, temp,0,n-1);
//         return nums[n/2];
//     }
// };






















// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//        int keys = nums.size() / 2;
//   int majority = 0;
//   unordered_map<int, int> hasher;
//   for (int num : nums) {

//     if (hasher.find(num) != hasher.end())
//       hasher.insert({num, hasher[num]++});

//     else
//       hasher.insert({num, 1});

//     if (hasher[num] > majority) {
//       majority = hasher[num];
//       keys = num;
//     }
//   }
//   return keys;
   
//     }
// };

























// class Solution {
// public:
//     void insertionSort(vector<int> &nums, int n){
//         for(int i = 1; i < n; i++){
//             int key = nums[i];
//             int j = i - 1;
//             while(j >= 0 && nums[j] > key){
//                 nums[j + 1] = nums[j];
//                 j--;
//             }
//             nums[j + 1] = key;
//         }
//     }
//     int majorityElement(vector<int>& nums) {
//         vector <int> tmp = nums;
//         insertionSort(tmp, tmp.size());
//         int result = 0;
//         int number = tmp[0];
//         int i = 0;
//         while(i < tmp.size()){
//             int counter = 0;
//             int key = tmp[i];
//             while(i < tmp.size() && tmp[i] == key){
//                 // cout << "key = " << key << " result = " <<  result << " i = " <<  i << endl;
//                 // cout << "Counter = " << counter << endl;
//                 counter++;
//                 i++;
//             }
//             if(result < counter){
//                 // cout << "key = " << key << " result = " <<  result << " i = " <<  i << endl;
//                 number = key;
//                 result = counter;
//             }
//         }
//         return number;
//     }
// };


















// class Solution {
// public:
//   int majorityElement(vector<int>& nums) {
//     int bubs_val,bubs_idx, cmp_val;
//     if ( nums.size()==1 ) { return nums[0]; }
//     for ( int ii=1; ii<nums.size(); ++ii ) {
//       bubs_val = nums[ii];
//       bubs_idx = ii;
//       for ( int jj=ii-1; jj>=0; --jj ) {
//         cmp_val = nums[jj];
//         if ( bubs_val < cmp_val ) {
//           nums[bubs_idx] = cmp_val;
//           nums[jj] = bubs_val;
//           bubs_idx-=1;
//         }
//         else {
//           break;
//         }
//       }
//     }
//     return nums[ nums.size()/2 ];
//   }
// };
















// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         int majority=nums.size()/2;
//         int sayac=0;
//         int cevap =0;
//         sort(nums.begin(),nums.end());
//         for(int i=0;i<nums.size();i++)
//         {
//             if(nums.size()==1)
//             {
//                 return nums[0];
//             }
//             if(sayac>majority)
//             {
//                cevap=nums[i];
//             }
//             if(i+1<nums.size() && nums[i+1]==nums[i])
//             {
//             if(sayac==0)
//             {
//                     sayac++;
//             }
//             sayac++;
//             }
//             else
//             {
//                 sayac=0;
//             }
//             cout<<sayac;
//         }
//         return cevap;
//     }
// };










