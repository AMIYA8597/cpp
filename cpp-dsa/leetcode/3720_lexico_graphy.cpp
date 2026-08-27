3720. Lexicographically Smallest Permutation Greater Than Target
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given two strings s and target, both having length n, consisting of lowercase English letters.

Return the lexicographically smallest permutation of s that is strictly greater than target. If no permutation of s is lexicographically strictly greater than target, return an empty string.

A string a is lexicographically strictly greater than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b.

 

Example 1:

Input: s = "abc", target = "bba"

Output: "bca"

Explanation:

The permutations of s (in lexicographical order) are "abc", "acb", "bac", "bca", "cab", and "cba".
The lexicographically smallest permutation that is strictly greater than target is "bca".
Example 2:

Input: s = "leet", target = "code"

Output: "eelt"

Explanation:

The permutations of s (in lexicographical order) are "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
The lexicographically smallest permutation that is strictly greater than target is "eelt".
Example 3:

Input: s = "baba", target = "bbaa"

Output: ""

Explanation:

The permutations of s (in lexicographical order) are "aabb", "abab", "abba", "baab", "baba", and "bbaa".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
 

Constraints:

1 <= s.length == target.length <= 300
s and target consist of only lowercase English letters.




























class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        string res;

        for (int i = 0; i < target.size(); i++) {
            int x = target[i] - 'a';

            if (cnt[x] == 0) {
                for (int c = x + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        res += char('a' + c);
                        cnt[c]--;

                        for (int k = 0; k < 26; k++)
                            res += string(cnt[k], char('a' + k));

                        return res;
                    }
                }

                break;
            }

            res += target[i];
            cnt[x]--;
        }

        for (int i = (int)res.size() - 1; i >= 0; i--) {
            int x = target[i] - 'a';

            cnt[x]++;

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = target.substr(0, i);

                    ans += char('a' + c);
                    cnt[c]--;

                    for (int k = 0; k < 26; k++)
                        ans += string(cnt[k], char('a' + k));

                    return ans;
                }
            }
        }

        return "";
    }
};



























class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int>v(26, 0);

        for(auto ch: s){
            v[ch-'a']++;
        }

        int i = 0;
        string ans = "";

        while(i<n){
            if(v[target[i]-'a']){
                ans.push_back(target[i]);
                v[target[i]-'a']--;
            }else{
                // find the next max
                for(int x = target[i]-'a' + 1 ; x<26; x++){
                    if(v[x]){
                        ans.push_back(x + 'a');
                        v[x]--;
                        for(int y=0; y<26; y++){
                            while(v[y]>0) {
                                ans.push_back(y + 'a');
                                v[y]--;
                            }
                        }
                        return ans;
                    }
                }
                break;
            }
            i++;
        }

        while(ans.size()>0){
            int ind = ans[ans.size()-1]-'a';
            ans.pop_back();
            v[ind]++;
            
            for(int i = ind+1; i<26; i++){
                if(v[i]){
                    ans.push_back(i+'a');
                    v[i]--;
                    for(int j = 0; j<26; j++){
                        int k = v[j];
                        while(k--) ans.push_back(j + 'a');
                    }
                    return ans;
                }
            }
        }

        return "";
    }
};




















class Solution {
public:
    string ans;

    bool solve(
        vector<char>& path,
        vector<int>& cnt,
        string& target,
        bool greater
    ) {
        int i = path.size();
        int n = target.size();

        if (!ans.empty())
            return true;

        if (i == n) {
            if (greater) {
                ans = string(path.begin(), path.end());
                return true;
            }
            return false;
        }

        for (int c = 0; c < 26; c++) {
            if (cnt[c] == 0)
                continue;

            char ch = 'a' + c;

            // If we are still equal to target,
            // we cannot choose a smaller character.
            if (!greater && ch < target[i])
                continue;

            path.push_back(ch);
            cnt[c]--;

            bool ngreater = greater || ch > target[i];

            if (solve(path, cnt, target, ngreater))
                return true;

            path.pop_back();
            cnt[c]++;
        }

        return false;
    }

    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26, 0);

        for (char ch : s)
            cnt[ch - 'a']++;

        ans = "";

        vector<char> path;

        solve(path, cnt, target, false);

        return ans;
    }
};


























class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        
        int n = s.size();
        vector<int> freq(26);
        for(auto ch : s) freq[ch - 'a']++;
        string ans = "";
        for(int i = 0; i < n; i++)
        {
            if(freq[target[i] - 'a'])
            {
                ans += target[i];
                freq[target[i] - 'a']--;
            }
            else break;
        }
        if(ans.size() != n)
        {
            int num = 27;
            for(int i = 0; i < 26; i++)
            {
                if(freq[i] == 0) continue;
                if(i > target[(int)ans.size()] - 'a') num = min(num, i);
            }
            if(num != 27)
            {
                freq[num]--;
                ans.push_back(num + 'a');
                for(int i = 0; i < 26; i++)
                {
                    for(int j = 0; j < freq[i]; j++) ans += i + 'a';
                }
                return ans;
            }
        }

        while(ans.size())
        {
            freq[ans.back() - 'a']++;
            ans.pop_back();
            int num = 27;
            for(int i = 0; i < 26; i++)
            {
                if(freq[i] == 0) continue;
                if(target[ans.size()] - 'a' < i) num = min(num, i);
            }
            if(num != 27)
            {
                freq[num]--;
                ans.push_back(num + 'a');
                for(int i = 0; i < 26; i++)
                {
                    for(int j = 0; j < freq[i]; j++) ans += i + 'a';
                }
                return ans;
            }
        }

        return "";
    }
};





















class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        
        vector<int>count(26,0) ;
        int n=s.length() ;
        for(int i=0;i<n;i++){
            count[s[i]-'a']++ ;
        }
        string ans="" ;
        for(int i=n-1;i>=0;i--){
            vector<int> temp=count ;
            bool ispos1=true ;
            for(int j=0;j<i;j++){
                if(temp[target[j]-'a']>0) temp[target[j]-'a']-- ;
                else ispos1=false ;
            }
            bool ispos2=false ;
            char val ;
            for(int j=(target[i]-'a'+1);j<26;j++){
                if(temp[j]>0){
                    ispos2=true ;
                    val =char('a'+j) ;
                    temp[j]-- ;
                    break ;
                }
            }

            if(ispos1&&ispos2){
                ans=target.substr(0,i) ;
                ans+=val ;
                for(int j=0;j<26;j++){
                    while(temp[j]>0){ans+=char('a'+j); temp[j]-- ; }
                }
                break ;
            }
        }
        return ans ;

    }
};
























class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n=s.size();

        unordered_map<char,int> mp;
        for(char ch:s){
            mp[ch]++;
        }

        string ans="";

        for(int i=0;i<n;i++){
            char ch=target[i];

            if(mp[ch]>0){
                mp[ch]--;
                ans+=ch;
                continue;
            }
            for(char c=ch+1;c<='z';c++){
                if(mp[c]>0){
                    mp[c]--;
                    ans+=c;
  
                    fill(mp,ans);
                    return ans;
                }
            }

            for(int j=i-1;j>=0;j--){
                mp[ans[j]]++;
                ans.pop_back();

                for(char c=target[j]+1;c<='z';c++){
                    if(mp[c]>0){
                        ans+=c;
                        mp[c]--;

                        fill(mp,ans);
                        return ans;
                    }
                }
            }

            return "";
        }

        if(nextperm(ans)){
            return ans;
        }

       return "";
    }
    bool nextperm(string & ans){
        int n = ans.size();

        int i = n - 2;

        while (i >= 0 && ans[i] >= ans[i + 1]) {
            i--;
        }

        if (i < 0) return false;

        int j = n - 1;

        while (ans[j] <= ans[i]) {
            j--;
        }

        swap(ans[i], ans[j]);

        reverse(ans.begin() + i + 1, ans.end());

        return true;
    }
    void fill(unordered_map<char,int> &mp,string & ans){
        for(char ch='a';ch<='z';ch++){
            while(mp[ch]>0){
                mp[ch]--;
                ans+=ch;
            }
        }

        
    }
};





















class Solution {
    public:
        string ans;
            
                bool func(vector<char>& path,vector<int>& cnt, string & target, bool big){
                        int n=target.size();
                                if(!ans.empty())return true;

                                        if(path.size()==n){
                                                    if(big){
                                                                    ans=string(path.begin(),path.end());
                                                                                    return true;
                                                                                                }
                                                                                                            return false;
                                                                                                                    }
                                                                                                                            int i=path.size();
                                                                                                                                    for(int c=0;c<26;c++){
                                                                                                                                                if(cnt[c]==0)continue;
                                                                                                                                                            if(!big && c+'a'<target[i])continue;
                                                                                                                                                                        path.push_back(c+'a');
                                                                                                                                                                                    cnt[c]--;
                                                                                                                                                                                                bool newbig=big||(c+'a'>target[i]);

                                                                                                                                                                                                            if(func(path,cnt,target,newbig))return true;

                                                                                                                                                                                                                        path.pop_back();
                                                                                                                                                                                                                                    cnt[c]++;
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                    return false;
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                string lexGreaterPermutation(string s, string target) {
                                                                                                                                                                                                                                                                        vector<int>cnt(26,0);
                                                                                                                                                                                                                                                                                for(char c:s)cnt[c-'a']++;
                                                                                                                                                                                                                                                                                        ans="";
                                                                                                                                                                                                                                                                                                vector<char>path;
                                                                                                                                                                                                                                                                                                        func(path,cnt,target,false);
                                                                                                                                                                                                                                                                                                                // if(ans==target)return "";
                                                                                                                                                                                                                                                                                                                        return ans;
                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                            };








class Solution {
public:
    string ans;
    
    bool func(vector<char>& path,vector<int>& cnt, string & target, bool big){
        int n=target.size();
        if(!ans.empty())return true;

        if(path.size()==n){
            if(big){
                ans=string(path.begin(),path.end());
                return true;
            }
            return false;
        }
        int i=path.size();
        for(int c=0;c<26;c++){
            if(cnt[c]==0)continue;
            if(!big && c+'a'<target[i])continue;
            path.push_back(c+'a');
            cnt[c]--;
            bool newbig=big||(c+'a'>target[i]);

            if(func(path,cnt,target,newbig))return true;

            path.pop_back();
            cnt[c]++;
        }
        return false;
    }
    
    string lexGreaterPermutation(string s, string target) {
        vector<int>cnt(26,0);
        for(char c:s)cnt[c-'a']++;
        ans="";
        vector<char>path;
        func(path,cnt,target,false);
        // if(ans==target)return "";
        return ans;
    }
};








