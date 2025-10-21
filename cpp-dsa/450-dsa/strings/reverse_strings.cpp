// 344. Reverse String
 
// Write a function that reverses a string. The input string is given as an array of characters s.

// You must do this by modifying the input array in-place with O(1) extra memory.

 

// Example 1:

// Input: s = ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]
// Example 2:

// Input: s = ["H","a","n","n","a","h"]
// Output: ["h","a","n","n","a","H"]














#include <vector>
#include <bits/basic_string.h>
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size()-1;
        while(left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
        
    }
};












// class Solution {
// public:
//     void reverseString(vector<char>& s) {
//         int n = s.size();
//         int i = 0, j = n-1;
        
//         while(i < j) {
//             swap(s[i], s[j]);
//             i++;
//             j--;
//         }
//     }
// };












// class Solution {
// public:
//     void reverseString(vector<char>& s) {
//         for(int i=0;i<s.size()/2;i++)
//         {
//             s[i] = s[i]^s[s.size()-i-1];
//             s[s.size()-i-1] = s[i]^s[s.size()-i-1];
//             s[i] = s[i]^s[s.size()-i-1];

//             // char temp = s[i];
//             // s[i] = s[s.size()-i-1];
//             // s[s.size()-i-1] = temp;
//         }
//     }
// };











// class Solution {
// public:
//     void reverseString(vector<char>& s) {
//         int start=0;
//         int end=s.size()-1;
//         while(start<=end){
//             swap(s[start],s[end]);
//             start++;
//             end--;
//         }   
//     }
// };












// class Solution {
// public:
//     void reverseString(vector<char>& s) {

//         vector<char>p;
//         for(int I=s.size()-1; I>=0;I--){
//             p.push_back(s[I]);
//         }
//         for(int I=0;I<s.size();I++){
//             s[I]=p[I];
//         }
//     }
// };