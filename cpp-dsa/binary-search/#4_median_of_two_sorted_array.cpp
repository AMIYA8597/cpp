// 4. Median of Two Sorted Arrays


// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

// The overall run time complexity should be O(log (m+n)).

 

// Example 1:

// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
// Example 2:

// Input: nums1 = [1,2], nums2 = [3,4]
// Output: 2.50000
// Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

// Constraints:

// nums1.length == m
// nums2.length == n
// 0 <= m <= 1000
// 0 <= n <= 1000
// 1 <= m + n <= 2000
// -106 <= nums1[i], nums2[i] <= 106



















class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        vector<int> merged;
        merged.reserve(m + n);
        int i =0;
        int j = 0;
        while (i < m && j < n) {
            if(nums1[i]< nums2[j]) {
                merged.push_back(nums1[i++]);
            }
            else {
                merged.push_back(nums2[j++]);
            }
        }

    while (i < m) {
        merged.push_back(nums1[i++]);
    }

    while(j < n) {
        merged.push_back(nums2[j++]);
    }

    int total = m + n;
    if (total % 2 == 1) {
        return merged[total / 2];
    } else {
        return (merged[total / 2 -1 ] + merged[total / 2]) / 2.0;
    }
    }
};





























// #include <bits/stdc++.h>   // Includes all standard C++ libraries (shortcut)
// using namespace std;

// class Solution {
// public:
//     // Function to find the median of two sorted arrays
//     // nums1 and nums2 are passed by reference (to avoid copying)
//     double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//         int m = nums1.size(), n = nums2.size();  // sizes of both arrays

//         vector<int> merged;          // this will hold the merged sorted array
//         merged.reserve(m + n);       // pre-allocate memory for efficiency

//         int i = 0, j = 0;            // two pointers, one for nums1 and one for nums2

//         // Merge process (like merge step of merge sort)
//         while (i < m && j < n) {     // while both arrays still have elements
//             if (nums1[i] < nums2[j]) {
//                 merged.push_back(nums1[i]);  // take element from nums1 if smaller
//                 i++;                         // move pointer i forward
//             } else {
//                 merged.push_back(nums2[j]);  // otherwise take element from nums2
//                 j++;                         // move pointer j forward
//             }
//         }

//         // If nums1 still has leftover elements, add them all
//         while (i < m) {
//             merged.push_back(nums1[i]);
//             i++;
//         }

//         // If nums2 still has leftover elements, add them all
//         while (j < n) {
//             merged.push_back(nums2[j]);
//             j++;
//         }

//         int total = m + n;  // total number of elements after merging

//         // If total number of elements is odd, median is the middle element
//         if (total % 2 == 1) {
//             return merged[total / 2];
//         } 
//         // If total number of elements is even,
//         // median is average of the two middle elements
//         else {
//             return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
//         }
//     }
// };


















// class Solution {
// public:
//     double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//         nums1.insert(nums1.end(), nums2.begin(), nums2.end());
//         sort(nums1.begin(),nums1.end());

//         int n = nums1.size();
//         if(n%2 == 1){
//             return nums1[n/2];
//         }else{
//             return (nums1[n/2 - 1] + nums1[n/2])/2.0;
//         }
//         return 0;
//     }
// };















// class Solution {
// public:
//     double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

//         //  Extreme brute force
//         // int n = nums1.size();
//         // int m = nums2.size();

//         // vector <int> arr;
//         // for(int i=0;i<n;i++){
//         //     arr.push_back(nums1[i]);
//         // }

//         // for(int i=0;i<m;i++){
//         //     arr.push_back(nums2[i]);
//         // }

//         // double median;
//         // sort(arr.begin(),arr.end());
//         // if((n+m)%2==0) median = (arr[(n+m)/2] + arr[((n+m)/2)- 1]) / 2.00 ;
//         // else median = arr[(n+m)/2];

//         // return median;


//         //Brute force using merge sort t.c => 0(n+m);

//         vector <int> arr;
//         int n = nums1.size();
//         int m = nums2.size();

//         int i=0,j=0;
//         while(i<n && j<m){

//             if(nums1[i]<nums2[j]) {arr.push_back(nums1[i]); i++;}
//             else{ arr.push_back(nums2[j]); j++; }

//         }

//         while(i<n){
//             arr.push_back(nums1[i]);
//             i++;
//         }

//         while(j<m){
//             arr.push_back(nums2[j]);
//             j++;
//         }

//         double median;
//         if((n+m)%2==0) median = (arr[(n+m)/2] + arr[((n+m)/2)- 1]) / 2.00 ;
//         else median = arr[(n+m)/2];

//         return median;




        
//     }
// };



















// class Solution {
// public:
//     double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
//         vector<int> nums3;

//         for(auto m : nums1)
//         nums3.push_back(m);

//                 for(auto m : nums2)
//         nums3.push_back(m);

//         sort(nums3.begin(), nums3.end());

//         int l = nums3.size();
//         double m;
//         if(l%2==0)
//         {
//             m = (nums3[l/2-1]+nums3[l/2])/2.0;
//         }
//         else{
//             m = nums3[l/2];
//         }

//         return m;
        
        
//     }
// };































