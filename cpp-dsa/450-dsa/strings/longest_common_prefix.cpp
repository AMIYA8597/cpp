// 14. Longest Common Prefix






// Write a function to find the longest common prefix string amongst an array of strings.

// If there is no common prefix, return an empty string "".

 

// Example 1:

// Input: strs = ["flower","flow","flight"]
// Output: "fl"
// Example 2:

// Input: strs = ["dog","racecar","car"]
// Output: ""
// Explanation: There is no common prefix among the input strings.
 

// Constraints:

// 1 <= strs.length <= 200
// 0 <= strs[i].length <= 200
// strs[i] consists of only lowercase English letters if it is non-empty.

















class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        string prefix = strs[0];
        for( int i =1; i<strs.size(); i++) {
            while(strs[i].find(prefix) !=0) {
                prefix = prefix.substr(0, prefix.size() -1);
                if(prefix.empty()) return "";
            }
        }
        return prefix;
    }
};











class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
     int n = strs.size();
     if( n ==1) return strs[0];

        sort(strs.begin(), strs.end());

        string ans = "";
        

        string first = strs[0];
        string last = strs[n-1];

    int i =0;
    int j = 0;

    while( i < first.size()){

        if(first[i] == last[j]){

            ans+= first[i];
        }

        else return ans;

        i++;
        j++;
    }

return ans;

    }
};




















class Solution {
public:
string prefix(string s1, string s2) {
    string res = "";
    int n = min(s1.size(), s2.size());
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) res += s1[i];
        else return res ;
    }
    return res ;
}
string longestCommonPrefix(vector<string>& strs) {
    string res = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        res = prefix(res, strs[i]);
    }
    return res;
}
};
























class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==1)return strs[0];
        string prefix="";
        int l=0;
        bool k=true;
        sort(strs.begin(),strs.end());
        int minlen=strs[0].size();
        while(l<minlen){
            char p=strs[0][l];
            for(auto i:strs){
                if(i[l]!=p)k=false;                    
            }
            if(k==false){
                return prefix;
            }
            l++;
            prefix+=p;
        }
        return prefix;
    }
        
};


















class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";

        string prefix = strs[0];

        for (int i = 1; i < strs.size(); ++i) {
            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if (prefix.empty()) return "";
            }
        }

        return prefix;
    }
};