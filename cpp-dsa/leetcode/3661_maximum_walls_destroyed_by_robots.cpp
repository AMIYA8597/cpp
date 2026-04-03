3661. Maximum Walls Destroyed by Robots


There is an endless straight line populated with some robots and walls. You are given integer arrays robots, distance, and walls:
robots[i] is the position of the ith robot.
distance[i] is the maximum distance the ith robot's bullet can travel.
walls[j] is the position of the jth wall.
Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it immediately stops at that robot and cannot continue.

Return the maximum number of unique walls that can be destroyed by the robots.

Notes:

A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
Robots are not destroyed by bullets.
 

Example 1:

Input: robots = [4], distance = [3], walls = [1,10]

Output: 1

Explanation:

robots[0] = 4 fires left with distance[0] = 3, covering [1, 4] and destroys walls[0] = 1.
Thus, the answer is 1.
Example 2:

Input: robots = [10,2], distance = [5,1], walls = [5,2,7]

Output: 3

Explanation:

robots[0] = 10 fires left with distance[0] = 5, covering [5, 10] and destroys walls[0] = 5 and walls[2] = 7.
robots[1] = 2 fires left with distance[1] = 1, covering [1, 2] and destroys walls[1] = 2.
Thus, the answer is 3.
Example 3:
Input: robots = [1,2], distance = [100,1], walls = [10]

Output: 0

Explanation:

In this example, only robots[0] can reach the wall, but its shot to the right is blocked by robots[1]; thus the answer is 0.

 

Constraints:

1 <= robots.length == distance.length <= 105
1 <= walls.length <= 105
1 <= robots[i], walls[j] <= 109
1 <= distance[i] <= 105
All values in robots are unique
All values in walls are unique


































































class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
         int n = robots.size();
        
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b){ return robots[a] < robots[b]; });
        
        vector<long long> pos(n);
        vector<int> dist(n);
        for (int i = 0; i < n; i++) {
            pos[i] = robots[idx[i]];
            dist[i] = distance[idx[i]];
        }
        sort(walls.begin(), walls.end());

        auto countW = [&](long long lo, long long hi) -> int {
            if (lo > hi) return 0;
            return (int)(upper_bound(walls.begin(), walls.end(), hi) -
                         lower_bound(walls.begin(), walls.end(), lo));
        };

        int selfTotal = 0;
        for (int i = 0; i < n; i++)
            selfTotal += countW(pos[i], pos[i]);

        int outerLeft = countW(max(pos[0] - dist[0], 1LL), pos[0] - 1);
        int outerRight = countW(pos[n-1] + 1, pos[n-1] + (long long)dist[n-1]);

        int dp0 = outerLeft;
        int dp1 = 0;

        for (int i = 1; i < n; i++) {
            long long gLo = pos[i-1] + 1;
            long long gHi = pos[i] - 1;

            long long LgLo = max(pos[i] - dist[i], gLo);
            int Lg = countW(LgLo, gHi);

            long long RgHi = min(pos[i-1] + (long long)dist[i-1], gHi);
            int Rg = countW(gLo, RgHi);

            int ov = countW(max(LgLo, gLo), min(gHi, RgHi));
            int both_ = Lg + Rg - ov;

            int ndp0 = max(dp0 + Lg, dp1 + both_);
            int ndp1 = max(dp0, dp1 + Rg);
            dp0 = ndp0;
            dp1 = ndp1;
        }

        dp1 += outerRight;

        return selfTotal + max(dp0, dp1);
    }
};








































#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();
        
        // Pair robots with their distances and sort them by position
        vector<pair<int, int>> rd(n);
        for (int i = 0; i < n; ++i) {
            rd[i] = {robots[i], distance[i]};
        }
        sort(rd.begin(), rd.end());
        sort(walls.begin(), walls.end());

        // Filter out walls that are on the exact same position as a robot
        vector<int> w;
        int base_destroyed = 0;
        int i = 0, j = 0;
        
        while (i < walls.size() && j < n) {
            if (walls[i] < rd[j].first) {
                w.push_back(walls[i]);
                i++;
            } else if (walls[i] == rd[j].first) {
                base_destroyed++; // Guaranteed to be destroyed by this robot
                i++;
            } else {
                j++;
            }
        }
        while (i < walls.size()) {
            w.push_back(walls[i]);
            i++;
        }

        int idx = 0;
        int s = 0;
        
        // Process the first interval (-infinity to 1st Robot)
        while (idx < w.size() && w[idx] < rd[0].first) {
            idx++;
        }
        int e = idx;
        
        long long reach_L = (long long)rd[0].first - rd[0].second;
        // Count walls destroyed if the 1st robot shoots Left
        int dp0 = (w.begin() + e) - lower_bound(w.begin() + s, w.begin() + e, reach_L);
        int dp1 = 0;

        // Process strictly intermediate intervals between adjacent robots
        for (int k = 1; k < n; ++k) {
            s = idx;
            while (idx < w.size() && w[idx] < rd[k].first) {
                idx++;
            }
            e = idx;

            long long X = (long long)rd[k-1].first + rd[k-1].second; // Reach of Robot k-1 shooting Right
            long long Y = (long long)rd[k].first - rd[k].second;     // Reach of Robot k shooting Left

            // Walls covered by k-1 shooting Right
            int count_le_X = upper_bound(w.begin() + s, w.begin() + e, X) - (w.begin() + s);
            // Walls covered by k shooting Left
            int count_ge_Y = (w.begin() + e) - lower_bound(w.begin() + s, w.begin() + e, Y);
            
            // Walls covered if BOTH k-1 shoots Right AND k shoots Left
            int count_union = 0;
            if (X >= Y) {
                count_union = e - s; // Full overlap, all walls in this sub-interval are hit
            } else {
                count_union = count_le_X + count_ge_Y;
            }

            // Update DP transitions
            int next_dp0 = max(dp0 + count_ge_Y, dp1 + count_union);
            int next_dp1 = max(dp0 + 0, dp1 + count_le_X);
            
            dp0 = next_dp0;
            dp1 = next_dp1;
        }

        // Process the final interval (last Robot to +infinity)
        s = idx;
        e = w.size();
        long long X_last = (long long)rd[n-1].first + rd[n-1].second;
        int count_last = upper_bound(w.begin() + s, w.begin() + e, X_last) - (w.begin() + s);

        int ans = max(dp0, dp1 + count_last);

        return ans + base_destroyed;
    }
};


































class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        // when i saw this question i get the idea of itervative dp 
        // from last to first using stack for better and clarity 
        // what one robot can do it can fire to left or right or no fire there is three option 
        // so simply i check all of them with using dp greedy pattern
        vector<pair<int,int>>nums;
        stack<int>st;
        stack<int>st1;
        int left_fire = 0,right_fire = 0, no_fire = 0;
        int n = robots.size();
        sort(walls.begin(),walls.end());
        for(int i = 0; i < n; i++){
            nums.push_back({robots[i],distance[i]});
        }
        sort(nums.begin(),nums.end());
        for(int i = 0; i < walls.size(); i++){
            // cout << walls[i] << " ";
            st.push({walls[i]});
            st1.push({walls[i]});
        }
        for(int i = n-1; i >= 0; i--){
            int pos = nums[i].first, dist = nums[i].second;
            int rrange = pos + dist,lrange = pos-dist;
            int prev = 0;
            while(!st.empty() && st.top() > rrange) st.pop();
            int rightcnt = 0;
            int rightcnt1 = 0;
            int leftcnt = 0;
            while(!st.empty() && st.top() >= pos){
                if(st.top()==pos) leftcnt++;
                rightcnt++;
                st.pop();
            }
            while(!st1.empty() && st1.top() > rrange) st1.pop();
            while(!st1.empty() && st1.top() >= pos){
                rightcnt1++;
                st1.pop();
            }
            
            if(i!=0) prev = nums[i-1].first;
            else prev = 0;

            while(!st.empty() && st.top() >= lrange && st.top() > prev){
                leftcnt++;
                st.pop();
            }
            int uleft_fire = leftcnt + max({left_fire,right_fire,no_fire});   
            int uright_fire = rightcnt + max({left_fire,right_fire,no_fire}); 
            uright_fire = max(uright_fire,rightcnt1 + max({right_fire,no_fire}));
            int uno_fire = max({left_fire,right_fire,no_fire});
            left_fire = uleft_fire;
            right_fire = uright_fire;
            no_fire = uno_fire;

            // if(i==0) cout << rightcnt1;
        }

        return max({left_fire,right_fire,no_fire});
    } 
};



























class Solution {
    const int LL = 0, LR = 1, RL = 2, RR = 3; 
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        robots.push_back(-1), robots.push_back(2e9);
        distance.push_back(0), distance.push_back(0);
        vector<int> rIndices(robots.size());
        iota(rIndices.begin(), rIndices.end(), 0);
        sort(rIndices.begin(), rIndices.end(), [&](int idx1, int idx2) {
            return robots[idx1] < robots[idx2];
        });
        int wallSize = walls.size();
        sort(walls.begin(), walls.end());
        int curr = 0;
        int lbot = rIndices[curr], rbot = rIndices[curr + 1];
        int dp[4] = {0}, cnt = 0;
        for (int i = 0; i < wallSize; i++) {
            while (walls[i] > robots[rbot]) {
                ++curr;
                lbot = rIndices[curr];
                rbot = rIndices[curr + 1];
                int maxL = max(dp[LL], dp[RL]);
                int maxR = max(dp[LR], dp[RR]);
                dp[LL] = dp[LR] = maxL;
                dp[RL] = dp[RR] = maxR;
            }
            if (walls[i] == robots[rbot]) {
                ++cnt;
                continue;
            }
            dp[LL] += walls[i] >= robots[rbot] - distance[rbot];
            dp[RL] += walls[i] <= robots[lbot] + distance[lbot] || walls[i] >= robots[rbot] - distance[rbot];
            dp[RR] += walls[i] <= robots[lbot] + distance[lbot];
        }
        return *max_element(dp, dp + 4) + cnt;
    }
};




















#include <vector>
#include <algorithm>

using namespace std;

static const int fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        if (n == 0) return 0;

        sort(walls.begin(), walls.end());

        vector<pair<int, int>> x(n);
        for(int i = 0; i < n; i++) x[i] = {robots[i], d[i]};
        sort(x.begin(), x.end());

        // Хелпер для быстрого поиска индекса (бинарный поиск остается только тут)
        auto get_idx = [&](long long val) {
            return lower_bound(walls.begin(), walls.end(), (int)val);
        };

        // DP состояния
        long long dp0 = 0; // i-й робот стреляет влево
        long long dp1 = 0; // i-й робот стреляет вправо

        // Начальные параметры
        auto it_start = get_idx(x[0].first - x[0].second);
        auto it_robot0 = get_idx(x[0].first);
        
        // i = 0 влево
        dp0 = distance(it_start, it_robot0 + (binary_search(it_robot0, walls.end(), x[0].first) ? 1 : 0));
        
        // i = 0 вправо
        long long first_limit = (n > 1) ? x[1].first - 1 : 2000000007LL;
        auto it_right_end = upper_bound(walls.begin(), walls.end(), (int)min((long long)x[0].first + x[0].second, first_limit));
        dp1 = distance(it_robot0, it_right_end);

        for (int i = 1; i < n; i++) {
            long long cur_p = x[i].first;
            long long cur_d = x[i].second;
            long long prev_p = x[i-1].first;
            long long prev_d = x[i-1].second;
            long long next_p = (i + 1 < n) ? x[i+1].first : 2000000007LL;

            // Итераторы для текущего робота
            auto it_cur_p_low = lower_bound(walls.begin(), walls.end(), (int)cur_p);
            auto it_cur_p_up = upper_bound(walls.begin(), walls.end(), (int)cur_p);
            
            // 1. Gain ВПРАВО
            auto it_r_limit = upper_bound(walls.begin(), walls.end(), (int)min(cur_p + cur_d, next_p - 1));
            int gain_right = distance(it_cur_p_low, it_r_limit);
            long long next_dp1 = max(dp0, dp1) + gain_right;

            // 2. Gain ВЛЕВО
            long long reach_left = max(cur_p - cur_d, prev_p + 1);
            auto it_l_limit = lower_bound(walls.begin(), walls.end(), (int)reach_left);
            int gain_left = distance(it_l_limit, it_cur_p_up);
            
            // 3. Overlap (если i-1 стрелял вправо)
            long long prev_r_end = min(prev_p + prev_d, cur_p - 1);
            int overlap = 0;
            if (reach_left <= prev_r_end) {
                auto it_overlap_end = upper_bound(walls.begin(), walls.end(), (int)prev_r_end);
                overlap = distance(it_l_limit, it_overlap_end);
            }
            
            long long next_dp0 = max(dp0 + gain_left, dp1 + gain_left - overlap);

            dp0 = next_dp0;
            dp1 = next_dp1;
        }

        return (int)max(dp0, dp1);
    }
};


























#include <vector>
#include <algorithm>

using namespace std;

static const int fast_io = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        if (n == 0) return 0;

        sort(walls.begin(), walls.end());

        vector<pair<int, int>> x(n);
        for(int i = 0; i < n; i++) x[i] = {robots[i], d[i]};
        sort(x.begin(), x.end());

        // Хелпер для быстрого поиска индекса (бинарный поиск остается только тут)
        auto get_idx = [&](long long val) {
            return lower_bound(walls.begin(), walls.end(), (int)val);
        };

        // DP состояния
        long long dp0 = 0; // i-й робот стреляет влево
        long long dp1 = 0; // i-й робот стреляет вправо

        // Начальные параметры
        auto it_start = get_idx(x[0].first - x[0].second);
        auto it_robot0 = get_idx(x[0].first);
        
        // i = 0 влево
        dp0 = distance(it_start, it_robot0 + (binary_search(it_robot0, walls.end(), x[0].first) ? 1 : 0));
        
        // i = 0 вправо
        long long first_limit = (n > 1) ? x[1].first - 1 : 2000000007LL;
        auto it_right_end = upper_bound(walls.begin(), walls.end(), (int)min((long long)x[0].first + x[0].second, first_limit));
        dp1 = distance(it_robot0, it_right_end);

        for (int i = 1; i < n; i++) {
            long long cur_p = x[i].first;
            long long cur_d = x[i].second;
            long long prev_p = x[i-1].first;
            long long prev_d = x[i-1].second;
            long long next_p = (i + 1 < n) ? x[i+1].first : 2000000007LL;

            // Итераторы для текущего робота
            auto it_cur_p_low = lower_bound(walls.begin(), walls.end(), (int)cur_p);
            auto it_cur_p_up = upper_bound(walls.begin(), walls.end(), (int)cur_p);
            
            // 1. Gain ВПРАВО
            auto it_r_limit = upper_bound(walls.begin(), walls.end(), (int)min(cur_p + cur_d, next_p - 1));
            int gain_right = distance(it_cur_p_low, it_r_limit);
            long long next_dp1 = max(dp0, dp1) + gain_right;

            // 2. Gain ВЛЕВО
            long long reach_left = max(cur_p - cur_d, prev_p + 1);
            auto it_l_limit = lower_bound(walls.begin(), walls.end(), (int)reach_left);
            int gain_left = distance(it_l_limit, it_cur_p_up);
            
            // 3. Overlap (если i-1 стрелял вправо)
            long long prev_r_end = min(prev_p + prev_d, cur_p - 1);
            int overlap = 0;
            if (reach_left <= prev_r_end) {
                auto it_overlap_end = upper_bound(walls.begin(), walls.end(), (int)prev_r_end);
                overlap = distance(it_l_limit, it_overlap_end);
            }
            
            long long next_dp0 = max(dp0 + gain_left, dp1 + gain_left - overlap);

            dp0 = next_dp0;
            dp1 = next_dp1;
        }

        return (int)max(dp0, dp1);
    }
};



























class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        vector<array<int,2>> x(n);
        for(int i=0; i<n; i++) x[i][0] = robots[i],x[i][1] = d[i];
        sort(walls.begin(),walls.end());
        sort(x.begin(),x.end());
        x.push_back({(int)1e9,0});

        // finds the no of walls in the range [l,r];
        auto query=[&](int l,int r){
            if(l>r) return 0;
            auto it1 = upper_bound(walls.begin(),walls.end(),r);
            auto it2 = lower_bound(walls.begin(),walls.end(),l);
            int res = it1-it2;
            return res;
        };
        
        vector<array<int,2>> dp(n);
        // base case
        dp[0][0] = query(x[0][0] - x[0][1],x[0][0]);
        if(n>1) dp[0][1] = query(x[0][0],min(x[1][0]-1, x[0][0]+x[0][1]));
        else dp[0][1] = query(x[0][0], x[0][0] + x[0][1]);

        //transition
        for(int i=1; i<n; i++){
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]) + query(x[i][0],min(x[i+1][0]-1,x[i][0]+x[i][1]));
            
            dp[i][0] = dp[i-1][0]+ query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]);
            int res = dp[i-1][1] 
                        + query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]) 
                        - query(max(x[i][0]-x[i][1],x[i-1][0]+1),min(x[i-1][0]+x[i-1][1],x[i][0]-1));
            dp[i][0] = max(res,dp[i][0]);
        }
        return max(dp[n-1][0],dp[n-1][1]);
    }
};






























class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        vector<array<int,2>> x(n);
        for(int i=0; i<n; i++) x[i][0] = robots[i],x[i][1] = d[i];
        sort(walls.begin(),walls.end());
        sort(x.begin(),x.end());
        x.push_back({(int)1e9,0});

        // finds the no of walls in the range [l,r];
        auto query=[&](int l,int r){
            if(l>r) return 0;
            auto it1 = upper_bound(walls.begin(),walls.end(),r);
            auto it2 = lower_bound(walls.begin(),walls.end(),l);
            int res = it1-it2;
            return res;
        };
        
        vector<array<int,2>> dp(n);
        // base case
        dp[0][0] = query(x[0][0] - x[0][1],x[0][0]);
        if(n>1) dp[0][1] = query(x[0][0],min(x[1][0]-1, x[0][0]+x[0][1]));
        else dp[0][1] = query(x[0][0], x[0][0] + x[0][1]);

        //transition
        for(int i=1; i<n; i++){
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]) + query(x[i][0],min(x[i+1][0]-1,x[i][0]+x[i][1]));
            
            dp[i][0] = dp[i-1][0]+ query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]);
            int res = dp[i-1][1] 
                        + query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]) 
                        - query(max(x[i][0]-x[i][1],x[i-1][0]+1),min(x[i-1][0]+x[i-1][1],x[i][0]-1));
            dp[i][0] = max(res,dp[i][0]);
        }
        return max(dp[n-1][0],dp[n-1][1]);
    }
};



























class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        vector<array<int,2>> x(n);
        for(int i=0; i<n; i++) x[i][0] = robots[i],x[i][1] = d[i];
        sort(walls.begin(),walls.end());
        sort(x.begin(),x.end());
        x.push_back({(int)1e9,0});

        // finds the no of walls in the range [l,r];
        auto query=[&](int l,int r){
            if(l>r) return 0;
            auto it1 = upper_bound(walls.begin(),walls.end(),r);
            auto it2 = lower_bound(walls.begin(),walls.end(),l);
            int res = it1-it2;
            return res;
        };
        
        vector<array<int,2>> dp(n);
        // base case
        dp[0][0] = query(x[0][0] - x[0][1],x[0][0]);
        if(n>1) dp[0][1] = query(x[0][0],min(x[1][0]-1, x[0][0]+x[0][1]));
        else dp[0][1] = query(x[0][0], x[0][0] + x[0][1]);

        //transition
        for(int i=1; i<n; i++){
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]) + query(x[i][0],min(x[i+1][0]-1,x[i][0]+x[i][1]));
            
            dp[i][0] = dp[i-1][0]+ query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]);
            int res = dp[i-1][1] 
                        + query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]) 
                        - query(max(x[i][0]-x[i][1],x[i-1][0]+1),min(x[i-1][0]+x[i-1][1],x[i][0]-1));
            dp[i][0] = max(res,dp[i][0]);
        }
        return max(dp[n-1][0],dp[n-1][1]);
    }
};













































class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& d, vector<int>& walls) {
        int n = robots.size();
        vector<array<int,2>> x(n);
        for(int i=0; i<n; i++) x[i][0] = robots[i],x[i][1] = d[i];
        sort(walls.begin(),walls.end());
        sort(x.begin(),x.end());
        x.push_back({(int)1e9,0});

        // finds the no of walls in the range [l,r];
        auto query=[&](int l,int r){
            if(l>r) return 0;
            auto it1 = upper_bound(walls.begin(),walls.end(),r);
            auto it2 = lower_bound(walls.begin(),walls.end(),l);
            int res = it1-it2;
            return res;
        };
        
        vector<array<int,2>> dp(n);
        // base case
        dp[0][0] = query(x[0][0] - x[0][1],x[0][0]);
        if(n>1) dp[0][1] = query(x[0][0],min(x[1][0]-1, x[0][0]+x[0][1]));
        else dp[0][1] = query(x[0][0], x[0][0] + x[0][1]);

        //transition
        for(int i=1; i<n; i++){
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]) + query(x[i][0],min(x[i+1][0]-1,x[i][0]+x[i][1]));
            
            dp[i][0] = dp[i-1][0]+ query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]);
            int res = dp[i-1][1] 
                        + query(max(x[i][0]-x[i][1],x[i-1][0]+1),x[i][0]) 
                        - query(max(x[i][0]-x[i][1],x[i-1][0]+1),min(x[i-1][0]+x[i-1][1],x[i][0]-1));
            dp[i][0] = max(res,dp[i][0]);
        }
        return max(dp[n-1][0],dp[n-1][1]);
    }
};