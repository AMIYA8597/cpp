// Kth Smallest
// Difficulty: MediumAccuracy: 35.17%Submissions: 721K+Points: 4Average Time: 25m
// Given an integer array arr[] and an integer k, your task is to find and return the kth smallest element in the given array.

// Examples :

// Input: arr[] = [10, 5, 4, 3, 48, 6, 2, 33, 53, 10], k = 4
// Output: 5
// Explanation: 4th smallest element in the given array is 5.
// Input: arr[] = [7, 10, 4, 3, 20, 15], k = 3
// Output: 7
// Explanation: 3rd smallest element in the given array is 7.
// Constraints:
// 1 ≤ arr.size() ≤ 105
// 1 ≤ arr[i] ≤ 105
// 1 ≤ k ≤  arr.size() 








#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
  public:
    int kthSmallest(vector<int> &arr, int k) {
        // code here
        sort(arr.begin(), arr.end());   //Sort the array
        
        return arr[k-1];    //Return the (k-1)th element (0-based indexing)
        
        
    }
};


int main() {
    vector<int> arr = {10,2,5,8,2,34,75,5,1,54};
    int k = 3;
    Solution sol;
    cout << "the smallest element : " << sol.kthSmallest(arr, k) << endl;
    return 0;
}



