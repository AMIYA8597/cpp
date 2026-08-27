2904. Shortest and Lexicographically Smallest Beautiful String
Medium
Topics
premium lock icon
Companies
Hint
You are given a binary string s and a positive integer k.

A substring of s is beautiful if the number of 1's in it is exactly k.

Let len be the length of the shortest beautiful substring.

Return the lexicographically smallest beautiful substring of string s with length equal to len. If s doesn't contain a beautiful substring, return an empty string.

A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b.

For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
 

Example 1:

Input: s = "100011001", k = 3
Output: "11001"
Explanation: There are 7 beautiful substrings in this example:
1. The substring "100011001".
2. The substring "100011001".
3. The substring "100011001".
4. The substring "100011001".
5. The substring "100011001".
6. The substring "100011001".
7. The substring "100011001".
The length of the shortest beautiful substring is 5.
The lexicographically smallest beautiful substring with length 5 is the substring "11001".
Example 2:

Input: s = "1011", k = 2
Output: "11"
Explanation: There are 3 beautiful substrings in this example:
1. The substring "1011".
2. The substring "1011".
3. The substring "1011".
The length of the shortest beautiful substring is 2.
The lexicographically smallest beautiful substring with length 2 is the substring "11".
Example 3:

Input: s = "000", k = 1
Output: ""
Explanation: There are no beautiful substrings in this example.
 

Constraints:

1 <= s.length <= 100
1 <= k <= s.length


























  class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
         vector<int> ones;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                ones.push_back(i);
            }
        }

        if (ones.size() < k)
            return "";

        string ans = "";

        for (int i = 0; i + k - 1 < ones.size(); i++) {
            int left = ones[i];
            int right = ones[i + k - 1];

            string cur = s.substr(left, right - left + 1);

            if (ans.empty() ||
                cur.size() < ans.size() ||
                (cur.size() == ans.size() && cur < ans)) {
                ans = cur;
            }
        }

        return ans;
    }
};


























class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        string ans;
        for(int i = 0, n = s.size(); i + k - 1 < n; i++) {
            int c = 0;
            for(int j = i; j < n; j++) {
                if((c += s[j] == '1') == k) {
                    string t = s.substr(i, j - i + 1);
                    if(ans.empty() || t.size() < ans.size() || (t.size() == ans.size() && t < ans)) ans = t;
                    break;
                }
            }
        }
        return ans;
    }
};



















class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int l = 0, ones = 0;
        __uint128_t curr = 0, best = 0;
        int minv = n + 1, mini = 0;
        for (int r = 0; r < n; r++) {
            curr = (curr << 1) | (s[r] == '1');
            ones += s[r] == '1';
            if (ones > k) {
                while (s[l] == '0')
                    l++;

                int len = r - l + 1;
                curr &= (((__uint128_t)1 << (len - 1)) - 1);
                l++;
                ones--;
            }

            if (ones != k)
                continue;

            while (s[l] == '0')
                l++;

            int len = r - l + 1;
            if (len < minv || (len == minv && curr < best)) {
                minv = len;
                mini = l;
                best = curr;
            }
        }

        return minv == n + 1 ? "" : s.substr(mini, minv);
    }
};
























class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n=s.size();
        set<string> bst;
        for(int i=0;i<n;i++){
            if(s[i]=='1'){
            int cnt=0;
            string temp="";
            int min_temp=INT_MAX;
            for(int j=i;j<n;j++){
                
                if(s[j]=='1') cnt++;
                temp+=s[j];
                if(cnt==k) 
                {
                    int len_temp=temp.size();
                    if(len_temp>min_temp) break;
                    else min_temp=len_temp;
                    bst.insert(temp);
                    break;
                }
                
                
            }
            }
        }
        string answer;
        if(bst.empty()) return "";
        int mini=INT_MAX;
        for(auto x:bst){
            if(x.size()<mini){
                answer=x;
                mini=x.size();
            }
        }
       return answer;
    }
};





















class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
      int n=s.size();
      int l=0;
      int ones=0;
      string ans="";
      for(int r=0; r<n; r++){
        if(s[r]=='1')ones++;
        while(ones==k){
            string curr=s.substr(l,r-l+1);
            if(ans==""||curr.size()<ans.size()||(curr.size()==ans.size()&&curr<ans)){
                ans=curr;
            }
        
         if (s[l] == '1')
                    ones--;

                l++;
      } }
      return ans;
    }
};


















class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int minlen = 1e9;
        vector<string>ans;
        for(int i=0;i<n;i++)
        {
            string p;
            int sum =0;
            int len = 0;
            for(int j=i;j<n;j++)
            {
                sum+=s[j]-'0';
                p+=s[j];
                if(sum==k) {len = j-i+1; minlen = min(len,minlen);ans.push_back(p);}
                if(sum>k) break;
            }
        }
        sort(ans.begin(),ans.end());
        for(auto x: ans)
        {
            if(x.size()==minlen) return x;
        }
        return "";
    }
};
