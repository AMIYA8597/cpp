1927. Sum Game
Solved
Medium
Topics
premium lock icon
Companies
Hint
Alice and Bob take turns playing a game, with Alice starting first.

You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:

Choose an index i where num[i] == '?'.
Replace num[i] with any digit between '0' and '9'.
The game ends when there are no more '?' characters in num.

For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.

For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.

 

Example 1:

Input: num = "5023"
Output: false
Explanation: There are no moves to be made.
The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.
Example 2:

Input: num = "25??"
Output: true
Explanation: Alice can replace one of the '?'s with '9' and it will be impossible for Bob to make the sums equal.
Example 3:

Input: num = "?3295???"
Output: false
Explanation: It can be proven that Bob will always win. One possible outcome is:
- Alice replaces the first '?' with '9'. num = "93295???".
- Bob replaces one of the '?' in the right half with '9'. num = "932959??".
- Alice replaces one of the '?' in the right half with '2'. num = "9329592?".
- Bob replaces the last '?' in the right half with '7'. num = "93295927".
Bob wins because 9 + 3 + 2 + 9 = 5 + 9 + 2 + 7.
 

Constraints:

2 <= num.length <= 105
num.length is even.
num consists of only digits and '?'.























class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int leftSum =0, rightSum = 0;
        int leftQ =0, rightQ = 0;

        for(int i =0; i< half; i++) {
             if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        int diff = leftSum - rightSum;

        if ((leftQ + rightQ) % 2 == 1)
            return true;

        return diff != 9 * (rightQ - leftQ) / 2;
    }
};



























class Solution {
    public:
        bool sumGame(string num) {
                int n = num.length();
                        int sum = 0;
                                int cnt1 = 0;
                                        int cnt2 = 0;
                                                
                                                        for (int i = 0;i < n;i++) {
                                                                    if (i < n/2) {
                                                                                    if (num[i] == '?') cnt1++;
                                                                                                    else sum += (num[i] - '0');
                                                                                                                } else {
                                                                                                                                if (num[i] == '?') cnt2++;
                                                                                                                                                else sum -= (num[i] - '0');
                                                                                                                                                            }
                                                                                                                                                                    }
                                                                                                                                                                            
                                                                                                                                                                                    if ((cnt1 + cnt2) % 2 == 1) return true; // The number of question marks is odd, so Alice must wins
                                                                                                                                                                                            int ans = sum + (cnt1/2)*9 - (cnt2/2)*9;
                                                                                                                                                                                                    return ans != 0;
                                                                                                                                                                                                        }

























#pragma GCC optimize("O3,inline")

class Solution {
public:
    bool sumGame(string s) {
        int n=s.length();
        int h=n>>1;
        int L=0,R=0;
        int lq=0,rq=0;
        for(int i=0;i<n;++i){
            if(i<h){
                if(s[i]=='?')
                    ++lq;
                else
                    L+=s[i]-'0';
            }else{
                if(s[i]=='?')
                    ++rq;
                else
                    R+=s[i]-'0';
            }
        }
        if(lq<rq){
            swap(L,R);
            swap(lq,rq);
        }
        int rem=lq-rq;
        if(rem==0)
            return L!=R;
        // println("{} {} {}",L,R,rem);
        if(L>=R)
            return true;
        int da=(rem+1)>>1;
        int db=rem>>1;
        int alice_max=L+da*9;
        if(alice_max>R)
            return true;
        int bob_max=L+db*9;
        // println("{} {}",alice_max,bob_max);
        //L<R
        return bob_max<R;
    }
};
























class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();

        auto get = [](string&& s) -> pair<int, int> {
            int nn = 0, qq = 0;
            for (char ch : s) {
                if (ch == '?') {
                    ++qq;
                } else {
                    nn += (ch - '0');
                }
            }
            return {nn, qq};
        };

        auto [n0, q0] = get(num.substr(0, n / 2));
        auto [n1, q1] = get(num.substr(n / 2, n / 2));

        return ((q0 + q1) % 2 == 1) || (n0 - n1 != (q1 - q0) * 9 / 2);
    }
};



















class Solution {
public:
    bool solve(int ps, int ss, int pcnt, int scnt) {
        int n = (scnt - pcnt);
        int ax = (n / 2) * 9, an = n * 0;
        int bx = (ps - ss) - (n - n / 2) * 9;
        int bn = (ps - ss) - (n - n / 2) * 0;
        if ((bx <= ax and bx >= an) and (bn >= an and bn <= ax))
            return false;
        
        return true;
    }
    bool sumGame(string num) {
        int ps = 0, ss = 0, pcnt = 0, scnt = 0;

        for (int i = 0; i < num.length() / 2; i++) {
            if (num[i] == '?')
                pcnt++;
            else
                ps += (num[i] - '0');
        }
        for (int i = num.length() / 2; i < num.length(); i++) {
            if (num[i] == '?')
                scnt++;
            else
                ss += (num[i] - '0');
        }
        cout<<ss<<" "<<ps<<endl;
        if (ps > ss) return solve(ps, ss, pcnt, scnt);
        return solve(ss, ps, scnt, pcnt);
    }
};














