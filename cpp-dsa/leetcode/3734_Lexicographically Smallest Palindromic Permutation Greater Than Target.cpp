3734. Lexicographically Smallest Palindromic Permutation Greater Than Target
Hard
Topics
premium lock icon
Companies
Hint
You are given two strings s and target, each of length n, consisting of lowercase English letters.

Return the lexicographically smallest string that is both a palindromic permutation of s and strictly greater than target. If no such permutation exists, return an empty string.

 

Example 1:

Input: s = "baba", target = "abba"

Output: "baab"

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
The lexicographically smallest permutation that is strictly greater than target is "baab".
Example 2:

Input: s = "baba", target = "bbaa"

Output: ""

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
Example 3:

Input: s = "abc", target = "abb"

Output: ""

Explanation:

s has no palindromic permutations. Therefore, the answer is "".

Example 4:

Input: s = "aac", target = "abb"

Output: "aca"

Explanation:

The only palindromic permutation of s is "aca".
"aca" is strictly greater than target. Therefore, the answer is "aca".
 

Constraints:

1 <= n == s.length == target.length <= 300
s and target consist of only lowercase English letters.



































  #include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26);

        for (char c : s)
            cnt[c - 'a']++;

        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++)
            halfCnt[i] = cnt[i] / 2;

        auto build = [&](string half) {
            string ans = half;

            if (n % 2)
                ans += mid;

            for (int i = m - 1; i >= 0; i--)
                ans += half[i];

            return ans;
        };

        string half;
        vector<int> rem = halfCnt;

        for (int i = 0; i < m && i < target.size(); i++) {
            int x = target[i] - 'a';

            if (rem[x] == 0)
                break;

            half += target[i];
            rem[x]--;
        }

        int matched = half.size();

        if (matched == m) {
            string candidate = build(half);

            if (candidate > target)
                return candidate;
        } else {
            int x = matched < target.size() ? target[matched] - 'a' : -1;

            for (int c = x + 1; c < 26; c++) {
                if (rem[c] == 0)
                    continue;

                string newHalf = half;
                newHalf += char('a' + c);
                rem[c]--;

                for (int d = 0; d < 26; d++)
                    newHalf += string(rem[d], char('a' + d));

                return build(newHalf);
            }
        }

        // Backtrack to find the next valid lexicographically larger permutation
        for (int i = matched - 1; i >= 0; i--) {
            rem[target[i] - 'a']++;

            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (rem[c] == 0)
                    continue;

                string newHalf = target.substr(0, i);
                newHalf += char('a' + c);
                rem[c]--;

                for (int d = 0; d < 26; d++)
                    newHalf += string(rem[d], char('a' + d));

                return build(newHalf);
            }
        }

        return "";
    }
};
























class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n=s.size();
        vector<int>hsh(26,0);
        for(int i=0;i<n;i++){
            hsh[s[i]-'a']++;
        }
        string ans=s;
        int odd=0;
        for(int i=0;i<26;i++){
            if(hsh[i]%2!=0){
                odd++;
                ans[n/2]=char('a'+i);
            }
            hsh[i]/=2;
        }
        if(odd>1){
            return "";
        }
        int p=0;
        while(p<n/2 && hsh[target[p]-'a']){
            hsh[target[p]-'a']--;
            p++;
        }
        int start=min(n-1,p);
        for(int i=start;i>=0;i--){
            if(i==(n/2)){
                for(int j=0;j<n/2;j++){
                    ans[j] = target[j];
                    ans[n-1-j] = target[j];
                }
                if(ans > target){
                    return ans;
                }
                continue;
            }
            int b=target[i]-'a';
            if(i<p){
                hsh[b]++;
            }
            int idx=-1;
            for(int c=b+1;c<26;c++){
                if(hsh[c]){
                    hsh[c]--;
                    idx=c;
                    break;
                }
            }
            if(idx==-1){
                continue;
            }
            for(int j=0;j<i;j++){
                ans[j]=target[j];
            }
            ans[i]=char('a'+idx);
            int k=i+1;
            for(int c=0;c<26;c++){
                while(k<n && hsh[c]){
                    ans[k]=char(c+'a');
                    k++;
                    hsh[c]--;
                }
            }
            for(int j=0;j<n/2;j++){
                ans[n-1-j]=ans[j];
            }
            return ans;
        }
        return "";
    }
};

























class Solution {
    public:
        string ans;

            bool func(vector<char>& path,vector<int>& cnt,string & target, bool big,char mid,int n){
                    if(!ans.empty())return true;
                            int half=n/2;
                                    if(path.size()==half){
                                                string left(path.begin(),path.end());
                                                            string right=left;
                                                                        reverse(right.begin(),right.end());
                                                                                    string pal="";
                                                                                                if(n%2!=0)pal=left+mid+right;
                                                                                                            else pal=left+right;
                                                                                                                        if(pal>target){
                                                                                                                                        ans=pal;
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
                                                                                                                                                                                                                                                                    bool newbig=big || (c+'a' >target[i]);
                                                                                                                                                                                                                                                                                if(func(path,cnt,target,newbig,mid,n))return true;
                                                                                                                                                                                                                                                                                            path.pop_back();
                                                                                                                                                                                                                                                                                                        cnt[c]++;
                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                        return false;
                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                    string lexPalindromicPermutation(string s, string target) {
                                                                                                                                                                                                                                                                                                                                            vector<int>cnt(26,0);
                                                                                                                                                                                                                                                                                                                                                    for(char c:s)cnt[c-'a']++;
                                                                                                                                                                                                                                                                                                                                                            ans="";
                                                                                                                                                                                                                                                                                                                                                                    int odd=0;
                                                                                                                                                                                                                                                                                                                                                                            char mid=0;
                                                                                                                                                                                                                                                                                                                                                                                    for(int i=0;i<26;i++){
                                                                                                                                                                                                                                                                                                                                                                                                if(cnt[i]%2){
                                                                                                                                                                                                                                                                                                                                                                                                            odd++;
                                                                                                                                                                                                                                                                                                                                                                                                                        mid='a'+i ;   
                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                cnt[i]/=2;
                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                if(odd>1)return "";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                        vector<char>path;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                func(path,cnt,target,false,mid,s.size());
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        return ans;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            };























class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        int cnt[26] = {};

        for (char c : s)
            cnt[c - 'a']++;

        // Check whether a palindrome is possible.
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = 'a' + i;
            }
        }

        if (odd > 1)
            return "";

        // cnt now stores the number of PAIRS available.
        for (int i = 0; i < 26; i++)
            cnt[i] /= 2;

        int half = n / 2;

        // Try to make the left half equal to target's left half.
        int temp[26];
        copy(cnt, cnt + 26, temp);

        bool possible = true;

        for (int i = 0; i < half; i++) {
            int c = target[i] - 'a';

            if (temp[c] == 0) {
                possible = false;
                break;
            }

            temp[c]--;
        }

        // If the entire left half can match target,
        // construct that palindrome and check it.
        if (possible) {
            string left = target.substr(0, half);

            string right = left;
            reverse(right.begin(), right.end());

            string candidate = left;

            if (n % 2)
                candidate += mid;

            candidate += right;

            if (candidate > target)
                return candidate;
        }

        // We couldn't get an answer by keeping the whole
        // left half equal. So backtrack from the right.
        for (int i = half - 1; i >= 0; i--) {

            // Restore target[i] to temp.
            // Recompute the remaining counts for this position.
            copy(cnt, cnt + 26, temp);

            bool ok = true;

            // Keep target[0 ... i-1] unchanged.
            for (int j = 0; j < i; j++) {
                int c = target[j] - 'a';

                if (temp[c] == 0) {
                    ok = false;
                    break;
                }

                temp[c]--;
            }

            if (!ok)
                continue;

            int current = target[i] - 'a';

            // Find the smallest character greater than target[i].
            int bigger = -1;

            for (int c = current + 1; c < 26; c++) {
                if (temp[c] > 0) {
                    bigger = c;
                    break;
                }
            }

            if (bigger == -1)
                continue;

            // Use the bigger character.
            temp[bigger]--;

            string left = target.substr(0, i);
            left += char('a' + bigger);

            // Fill remaining left half as small as possible.
            for (int c = 0; c < 26; c++) {
                while (temp[c] > 0) {
                    left += char('a' + c);
                    temp[c]--;
                }
            }

            // Build palindrome.
            string ans = left;

            if (n % 2)
                ans += mid;

            string rev = left;
            reverse(rev.begin(), rev.end());

            ans += rev;

            return ans;
        }

        return "";
    }

    /*
    1. Match target's left half.
        ↓
    2. If resulting palindrome > target → return it.
        ↓
    3. Otherwise go backwards.
        ↓
    4. Restore the pair used at i.
        ↓
    5. Try smallest character > target[i].
        ↓
    6. Fill remaining half in ascending order.
        ↓
    7. Mirror.
    */
};























class Solution {
    int freq[128] = {0};
    int halfLen;
    string curr, strL;
    string processFreq() {
        string ret = "";
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (freq[ch] % 2)
                ret.push_back(ch);
            freq[ch] /= 2;
        }
        return ret;
    }
    void genStr(string &target, int pos, bool isGreater) {
        if (pos == halfLen) {
            strL = curr;
            return;
        }
        if (isGreater) {
            strL = curr;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                strL += string(freq[ch], ch);
            }
            return;
        }

        char ch = target[pos];
        if (freq[ch]) {
            --freq[ch];
            curr.push_back(ch);
            genStr(target, pos + 1, false);
            curr.pop_back();
            ++freq[ch];
            if (!strL.empty())
                return;
        }

        ++ch;
        while (ch <= 'z' && !freq[ch]) {
            ++ch;
        }
        if (ch <= 'z') {
            --freq[ch];
            curr.push_back(ch);
            genStr(target, pos + 1, true);
            curr.pop_back();
            ++freq[ch];
        }
        return;
    }
public:
    string lexPalindromicPermutation(string s, string target) {
        int cntOdd = 0;
        for (const char ch: s) {
            cntOdd += ++freq[ch] % 2 ? 1 : -1;
        }
        if (cntOdd > 1 || (cntOdd && s.size() % 2 == 0))
            return "";
        
        string strM = processFreq();
        halfLen = target.size() / 2;
        genStr(target, 0, false);
        if (strL.size() != halfLen)
            return "";
        
        string strR = strL;
        reverse(strR.begin(), strR.end());
        string res = strL + strM + strR;
        if (res > target)
            return res;
        
        next_permutation(strL.begin(), strL.end());
        strR = strL;
        reverse(strR.begin(), strR.end());
        res = strL + strM + strR;
        return res > target ? res : "";
    }
};















class Solution {
    int new_freq[26];
    string result = "";
    int mid_ = -1;

    void backtracking(string& target, int pos, string& cur){
        if(!result.empty()) return;

        if(cur > target.substr(0, cur.size())){
            string remaining;
            for(int i = 0; i < 26; ++i){
                remaining += string(new_freq[i], 'a'+i);
            }
            cur += remaining;
            string temp = cur;
            string rev = cur;
            reverse(rev.begin(), rev.end());
            if(target.size() % 2 == 1) temp.push_back('a'+mid_);
            if(temp + rev > target){
                result = temp+rev;
            }
            return;
        }
        if(pos == target.size()/2){
            string temp = cur;
            string rev = cur;
            reverse(rev.begin(), rev.end());
            if(target.size() % 2 == 1) temp.push_back('a'+mid_);
            if(temp + rev > target){
                result = temp + rev;
            }
            return;
        }

        int start = target[pos]-'a';
        for(int i = start; i < 26; ++i){
            if(new_freq[i] == 0) continue;

            cur.push_back('a'+i);
            new_freq[i]--;
            backtracking(target, pos+1, cur);
            if(!result.empty()) return; 
            new_freq[i]++;
            cur.pop_back();
        }
    }

public:
    string lexPalindromicPermutation(string s, string target) {
        int freq[26];
        memset(freq, 0, sizeof(freq));
        for(char c : s) freq[c-'a']++;
        memset(new_freq, 0, sizeof(new_freq));
        for(int i = 0; i < 26; ++i) new_freq[i] = freq[i]/2;

        int n = target.size();
        bool be_one = (n%2 == 0);
        for(int i = 0; i < 26; ++i){
            if(freq[i] % 2 == 1){
                if(be_one) return "";
                else{
                    be_one = true;
                    mid_ = i;
                }
            }
        }

        string cur;

        backtracking(target, 0, cur);

        return result;
    }
};
