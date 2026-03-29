2573. Find the String with LCP
Solved
Hard
Topics
premium lock icon
Companies
Hint
We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:

lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.

 

Example 1:

Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
Output: "abab"
Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".
Example 2:

Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
Output: "aaaa"
Explanation: lcp corresponds to any 4 letter string with a single distinct letter. The lexicographically smallest of them is "aaaa". 
Example 3:

Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
Output: ""
Explanation: lcp[3][3] cannot be equal to 3 since word[3,...,3] consists of only a single letter; Thus, no answer exists.
 

Constraints:

1 <= n == lcp.length == lcp[i].length <= 1000
0 <= lcp[i][j] <= n

















class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string ans(n, 'a');
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (lcp[i][j] > 0) {
                    ans[j] = ans[i] + 1;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int commonPrefixLength = 0;
                while (i + commonPrefixLength < n && j + commonPrefixLength < n && ans[i + commonPrefixLength] == ans[j + commonPrefixLength]) {
                    commonPrefixLength++;
                }
                if (commonPrefixLength != lcp[i][j]) return "";
            }
        }
        return ans;
    }
};











class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
         int n = lcp.size();

        for (int i = 0; i < n; i++) {
            if (lcp[i][i] != n - i) return "";
        }
        string res(n, '#');
        char ch = 'a';

        for (int i=0; i<n;i++) {
            if(res[i] == '#') {
                if(ch >'z') {
                    return "";
                }
                for(int j =i; j< n; j++) {
                    if (lcp[i][j] > 0) {
                        res[j] = ch;
                    }
                }
                ch++;
            }
        }
    vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int i = n-1; i>=0; i--) {
            for(int j = n-1; j>=0; j--) {
                if (res[i]==res[j]) {
                    if (i == n-1 || j == n-1) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + dp[i+1][j+1];
                    }
                } else {
                    dp[i][j]=0;
                }
                if (dp[i][j] != lcp [i][j]) {
                    return "";
                }
            }
        }
        return res;
    }
};




















class Solution {
public:
    static string findTheString(vector<vector<int>>& lcp) {
        const int n=lcp.size();
        string s(n, 'a'-1);
        int id=-1;
        for(int i=0; i<n; i++){
            if (s[i]>='a') continue;
            if (id++>=25) return "";
            for(int j=0; j<n; j++)
                if(lcp[i][j]) s[j]='a'+id;
        }
        for(int i=0; i<n; i++){
            if (lcp[i][i]!=n-i) return "";// check diagonal
            for(int j=0; j<i; j++){
                const int x=lcp[i][j];
                if (x!=lcp[j][i]) return "";// must be symmetry
                int y=(i<n-1)?lcp[i+1][j+1]:0;
                y=(s[i]==s[j])?y+1:0;
                if (x!=y) return "";
            }
        }
        return s;
    }
};
























class Solution {
public:
    static string findTheString(vector<vector<int>>& lcp) {
        const int n=lcp.size();
        string s(n, 'X');
        int id=-1;
        for(int i=0; i<n; i++){
            if (lcp[i][i]!=n-i) return "";// main diagonal
            if (s[i]>='a') continue;
            if (id++>=25) return "";
            for(int j=0; j<n; j++)
                if(lcp[i][j]) s[j]='a'+id;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                const int x=lcp[i][j];
                if (x!=lcp[j][i] || x+i>n) return "";// must be symmetry
                int y=(i<n-1)?lcp[i+1][j+1]:0;
                y=(s[i]==s[j])?y+1:0;
                if (x!=y) return "";
            }
        }
        return s;
    }
};
































class Solution {
public:
    static string findTheString(vector<vector<int>>& lcp) {
        const int n=lcp.size();
        string s(n, 'X');
        int id=-1;
        for(int i=0; i<n; i++){
            if (lcp[i][i]!=n-i) return "";// main diagonal
            if (s[i]>='a') continue;
            if (id++>=25) return "";
            for(int j=0; j<n; j++)
                if(lcp[i][j]) s[j]='a'+id;
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                const int x=lcp[i][j];
                if (x!=lcp[j][i]) return "";// must be symmetry
                int y=(i<n-1)?lcp[i+1][j+1]:0;
                y=(s[i]==s[j])?y+1:0;
                if (x!=y) return "";
            }
        }
        return s;
    }
};


































class Solution {
public:
    static string findTheString(vector<vector<int>>& lcp) {
        const int n=lcp.size();
        string s(n, 'a'-1);
        int id=-1;
        for(int i=0; i<n; i++){
            if (s[i]>='a') continue;
            if (id++>=25) return "";
            for(int j=0; j<n; j++)
                if(lcp[i][j]) s[j]='a'+id;
        }
        for(int i=0; i<n; i++){
            if (lcp[i][i]!=n-i) return "";// check diagonal
            for(int j=0; j<i; j++){
                const int x=lcp[i][j];
                if (x!=lcp[j][i]) return "";// must be symmetry
                int y=(i<n-1)?lcp[i+1][j+1]:0;
                y=(s[i]==s[j])?y+1:0;
                if (x!=y) return "";
            }
        }
        return s;
    }
};