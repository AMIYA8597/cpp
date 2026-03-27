10. Regular Expression Matching


Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
Return a boolean indicating whether the matching covers the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
 

Constraints:

1 <= s.length <= 20
1 <= p.length <= 20
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.




















  class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2];

                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }


};

































class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        bool dp[n+1][m+1];
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        
        for(int i=0; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(p[j-1] == '*'){
                    dp[i][j] = dp[i][j-2] || (i > 0 && (s[i-1] == p[j-2] || p[j-2] == '.') && dp[i-1][j]);
                }
                else{
                    dp[i][j] = i > 0 && dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
                }
            }
        }
        
        return dp[n][m];
    }
};






























class Solution {
public:
    bool dfs(string s,string p,int i,int j,vector<vector<int>>& dp){
        if(j == p.length()){
            return i == s.length();
        }
        if(dp[i][j] != -1) return dp[i][j];
        bool match = (i<s.length() && (s[i] == p[j] || p[j] == '.'));

        if(j+1<p.length() && p[j+1] == '*'){ 
            return dp[i][j] = dfs(s,p,i,j+2,dp) || (match && dfs(s,p,i+1,j,dp));
        }
        if(match){
            return dp[i][j] = dfs(s,p,i+1,j+1,dp); 
        }
        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        int n=s.size();
        int m=p.size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,-1));
        return dfs(s,p,0,0,dp);
    }
};























class Solution {
public:
    bool check(int i, int j, string s, string p, vector<vector<int>>&dp){
        if(j == p.length()){
            return (i == s.length());
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        bool isFirstCharSame = false;
        if(i < s.length() && (s[i] == p[j] || p[j] == '.')){
            isFirstCharSame = true;
        }

        if(j + 1 < p.length() && p[j+1] == '*'){
            bool skip = check(i,j+2,s,p,dp);
            bool take = isFirstCharSame && check(i+1,j,s,p,dp);

            return dp[i][j] = skip || take;
        }

        return dp[i][j] = isFirstCharSame && check(i+1,j+1,s,p,dp);
    }
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        vector<vector<int>>dp(21,vector<int>(21,-1));
        return check(0,0,s,p,dp);
    }
};


























class Solution {
public:
    map<pair<int,int>,bool> mp;
    bool rec(int i, int j, string s, string p) {
        if (j == p.size()) {
            if (i == s.size()) {
                return true;
            }
            return false;
        }

        if (i == s.size()) {
            while (j <= p.size() - 1) {
                if (p[j] == '*') {
                    j++;
                } else if (j + 1 <= p.size() - 1 && p[j + 1] == '*') {
                    j += 2;
                } else {
                    return false;
                }
            }

            if (j == p.size()) {
                return true;
            } else {
                return false;
            }
        }

        if(mp.count({i,j}))
        {
            return mp[{i,j}];
        }
        bool a = false, b = false, c = false, d = false;
        if (j + 1 <= p.size() - 1 && p[j + 1] == '*') {
            int index = i;
            while (index <= s.size() - 1 && (p[j] == '.' || s[index] == p[j])) {
                b = b || rec(index + 1, j, s, p);
                index++;
            }
            b = b || rec(i, j + 2, s, p);
        } else if (s[i] == p[j]) {
            c = c || rec(i + 1, j + 1, s, p);
        } else if (p[j] == '.') {
            a = a || rec(i + 1, j + 1, s, p);
        } else {
            return d = false;
        }

        return mp[{i,j}] = a || b || c || d;
    }
    bool isMatch(string s, string p) { return rec(0, 0, s, p); }
};




























class Solution {
public:
    bool rec(int sind, int pind, string &s, string &p, vector<vector<int>> &dp){
        cout<<"rec("<<sind<<", "<<pind<<")"<<endl;
        if(sind < 0 && pind < 0){
            return dp[sind+1][pind+1] = true;
        }
        if (sind >= 0 && pind < 0){
            return dp[sind+1][pind+1] = false;
        }
        if (dp[sind+1][pind+1] != -1){
            return dp[sind+1][pind+1];
        }
        // if (sind < 0 && pind >= 0){
        //     return false;
        // }
        bool ans = false;
        if(p[pind] == '*'){
            if (sind>=0 && (p[pind-1] == '.' || s[sind] == p[pind-1])){
                ans = rec(sind, pind-2, s, p, dp) || rec(sind-1, pind, s, p,dp);
            } else{
                ans = rec(sind, pind-2, s, p,dp);
            }
        }
        else if(sind>=0 && (s[sind] == p[pind] || p[pind] == '.')){
            ans = rec(sind - 1, pind-1, s, p,dp);
        }
        return dp[sind+1][pind+1] = ans;
    }

    bool front(int sind, int pind, string &s, string &p, vector<vector<int>> &dp){
        cout<<"rec("<<sind<<", "<<pind<<")"<<endl;
        if(sind >= s.length() && pind >= p.length()){
            return dp[sind+1][pind+1] = true;
        }
        if (sind < s.length() && pind >= p.length()){
            return dp[sind+1][pind+1] = false;
        }
        if (dp[sind+1][pind+1] != -1){
            return dp[sind+1][pind+1];
        }
        // if (sind < 0 && pind >= 0){
        //     return false;
        // }
        bool ans = false;
        if(pind + 1 < p.length() && p[pind+1] == '*'){
            if (sind < s.length() && (p[pind] == '.' || s[sind] == p[pind])){
                ans = front(sind, pind+2, s, p,dp) || front(sind+1, pind, s, p,dp);
            } else{
                ans = front(sind, pind+2, s, p,dp);
            }
        }
        else if(sind < s.length() && (p[pind] == '.' || s[sind] == p[pind])){
            ans = front(sind + 1, pind+1, s, p,dp);
        }
        return dp[sind+1][pind+1] = ans;
    }

    bool isMatch(string s, string p) {
        vector<vector<int>> dp (25, vector<int> (25, -1));
        return rec(s.length()-1,p.length()-1,s,p, dp);
        // return front(0,0,s,p,dp);
    }
};
























class Solution {
public:
    bool isMatch(string s, string p) {
        vector<bool> prev(p.size() + 1, true);
        vector<bool> curr(p.size() + 1);

        for(int i = 0; i < p.size(); i++){
            if(p[i] != '*'){
                prev[i+1] = false;
            }

            else{
                prev[i+1] = prev[i-1];
            }
        }

        for(char c: s){
            curr[0] = false;

            for(int i = 0; i < p.size(); i++){
                if(p[i] == '.'){
                    curr[i+1] = prev[i];

                    continue;
                }

                if(isalpha(p[i])){
                    curr[i+1] = prev[i] && p[i] == c;

                    continue;
                }

                bool opt1 = curr[i-1];
                bool opt2 = curr[i];
                bool opt3 = (p[i-1] == c || p[i-1] == '.') && prev[i+1];
                
                curr[i+1] = opt1 || opt2 || opt3;
            }

            for(int i = 0; i < prev.size(); i++){
                printf(" %d", prev[i]?1:0);
            }

            puts("");

            swap(prev, curr);
        }

        return prev.back();
    }
};
