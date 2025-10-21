// 38. Count and Say


// The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

// countAndSay(1) = "1"
// countAndSay(n) is the run-length encoding of countAndSay(n - 1).
// Run-length encoding (RLE) is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "3322251" we replace "33" with "23", replace "222" with "32", replace "5" with "15" and replace "1" with "11". Thus the compressed string becomes "23321511".

// Given a positive integer n, return the nth element of the count-and-say sequence.

 

// Example 1:

// Input: n = 4

// Output: "1211"

// Explanation:

// countAndSay(1) = "1"
// countAndSay(2) = RLE of "1" = "11"
// countAndSay(3) = RLE of "11" = "21"
// countAndSay(4) = RLE of "21" = "1211"
// Example 2:

// Input: n = 1

// Output: "1"

// Explanation:

// This is the base case.

 

// Constraints:

// 1 <= n <= 30















class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) return "1";
        string prev = countAndSay(n - 1);
        string res = "";
        int count = 1;
        for (int i = 1; i < prev.size(); i++) {
            if (prev[i] == prev[i - 1]) count++;
            else {
                res += to_string(count) + prev[i - 1];
                count = 1;
            }
        }
        res += to_string(count) + prev.back();
        return res;
    }
        
};

// int main() {
//     Solution sol;
//     int n = 4;
//     cout << sol.countAndSay(n);  // Output: "1211"
//     return 0;
// }

























// class Solution {
// public:
//     string countAndSay(int n) {
        
//         if(n==1){
//             return "1";
//         }

//         string res = "1";

//         for(int i =1;i<n;i++){

//             string temp = "";            
//             char ele;
//             int count=0;

//             for(int i=0;i<res.size();i++){

//                 if(i==0){
//                     ele = res[i];
//                     count =1;
//                 }else{

//                     if(res[i]==ele){
//                         count++;
//                     }else{
                        
//                         temp+=to_string(count)+ele;
//                         ele = res[i];
//                         count=1;
//                     }
//                 }

//             }

//             temp+=to_string(count)+ele;
//             res=temp;
//         }
//         return res;
//     }
// };


















// class Solution {
// public:
//     string countAndSay(int n) {
//         string res = "1";
//         for (int i = 1; i < n; i++) {
//             string temp = "";
//             int count = 1;
//             for (int j = 1; j < res.size(); j++) {
//                 if (res[j] == res[j - 1]) {
//                     count++;
//                 } else {
//                     temp += to_string(count) + res[j - 1];
//                     count = 1;
//                 }
//             }
//             temp += to_string(count) + res.back();
//             res = temp;
//         }
//         return res;
//     }
// };





























// class Solution {
// public:
//     string countAndSay(int n) {
//         string s = "1";
//         while (--n) {
//             string t = "";
//             for (int i = 0; i < s.size();) {
//                 int j = i;
//                 while (j < s.size() && s[j] == s[i]) ++j;
//                 t += to_string(j - i);
//                 t += s[i];
//                 i = j;
//             }
//             s = t;
//         }
//         return s;
//     }
// };


















// class Solution {
// public:
//     string nextTerm(const string &s) {
//         string res = "";
//         int count = 1;
//         for (int i = 1; i < s.size(); i++) {
//             if (s[i] == s[i - 1]) {
//                 count++;
//             } else {
//                 res += to_string(count) + s[i-1];
//                 count = 1;
//             }
//         }
//         res += to_string(count) + s.back(); 
//         return res;
//     }

//     string countAndSay(int n) {
//         string ans = "1";
//         for (int i = 1; i < n; i++) {
//             ans = nextTerm(ans);
//         }
//         return ans;
//     }
// };