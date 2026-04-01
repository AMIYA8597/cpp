// 2751. Robot Collisions


// There are n 1-indexed robots, each having a position on a line, health, and movement direction.

// You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.

// All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.

// If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.

// Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final health of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.

// Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.

// Note: The positions may be unsorted.

 
 

// Example 1:



// Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
// Output: [2,17,9,15,10]
// Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].
// Example 2:



// Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
// Output: [14]
// Explanation: There are 2 collisions in this example. Firstly, robot 1 and robot 2 will collide, and since both have the same health, they will be removed from the line. Next, robot 3 and robot 4 will collide and since robot 4's health is smaller, it gets removed, and robot 3's health becomes 15 - 1 = 14. Only robot 3 remains, so we return [14].
// Example 3:



// Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
// Output: []
// Explanation: Robot 1 and robot 2 will collide and since both have the same health, they are both removed. Robot 3 and 4 will collide and since both have the same health, they are both removed. So, we return an empty array, [].
 

// Constraints:

// 1 <= positions.length == healths.length == directions.length == n <= 105
// 1 <= positions[i], healths[i] <= 109
// directions[i] == 'L' or directions[i] == 'R'
// All values in positions are distinct



























class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();

        vector<tuple<int,int,char,int>> robots;
        for(int i = 0; i < n; i++) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }

        sort(robots.begin(), robots.end());

        stack<int> st;
        vector<int> currHealth(n);
        
        for(int i = 0; i < n; i++) {
            currHealth[i] = get<1>(robots[i]);
        }

        for(int i = 0; i < n; i++) {
            char dir = get<2>(robots[i]);

            if(dir == 'R') {
                st.push(i);
            } else {
                while(!st.empty() && currHealth[i] > 0) {
                    int j = st.top();

                    if(currHealth[j] < currHealth[i]) {
                        st.pop();
                        currHealth[i] -= 1;
                        currHealth[j] = 0;
                    }
                    else if(currHealth[j] > currHealth[i]) {
                        currHealth[j] -= 1;
                        currHealth[i] = 0;
                        break;
                    }
                    else {
                        st.pop();
                        currHealth[j] = 0;
                        currHealth[i] = 0;
                        break;
                    }
                }
            }
        }

        vector<pair<int,int>> survivors;

        for(int i = 0; i < n; i++) {
            if(currHealth[i] > 0) {
                int originalIndex = get<3>(robots[i]);
                survivors.push_back({originalIndex, currHealth[i]});
            }
        }

        sort(survivors.begin(), survivors.end());

        vector<int> result;
        for(auto &p : survivors) {
            result.push_back(p.second);
        }
        return result;
    }
};































typedef tuple<int, int, int, int> tup4;

class Solution {
    const int L = 0, R = 1;
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int size = positions.size();
        vector<tup4> robots;
        robots.reserve(size);
        for (int i = 0; i < size; i++)
            robots.push_back({i, positions[i], healths[i], directions[i] == 'R'});
        sort(robots.begin(), robots.end(), [](tup4 &robot1, tup4& robot2) {
            return get<1>(robot1) < get<1>(robot2);
        });
        int l = 0, r = 0;
        for (int r = 0; r < size; r++) {
            auto &[idx, pos, hp, dir] = robots[r];
            if (dir == R) {
                robots[l++] = robots[r];
                continue;
            }
            while (l && get<3>(robots[l - 1]) == R && hp) {
                // dir0: R dir: L
                auto &[idx0, pos0, hp0, dir0] = robots[l - 1];
                if (hp0 > hp) {
                    hp = 0;
                    if (--hp0 == 0)
                        --l;
                } else if (hp0 < hp) {
                    --hp;
                    --l;
                } else {
                    hp = 0;
                    --l;
                }
            }
            if (hp) {
                robots[l++] = robots[r];
            }
        }
        robots.resize(l);
        sort(robots.begin(), robots.end(), [](tup4 &robot1, tup4& robot2) {
            return get<0>(robot1) < get<0>(robot2);
        });
        vector<int> res;
        res.reserve(robots.size());
        for (const auto &[idx, pos, hp, dir]: robots) {
            res.push_back(hp);
        }
        return res;
    }
};




























class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        vector<pair<int, int>>vp;
        int n = healths.size();
        for (int i = 0; i<n; i++){
            vp.push_back({positions[i], i});
        }
        sort(vp.begin(), vp.end());
        stack<int>st;
        for (int i = n-1; i>=0; i--){
            int hlth = healths[vp[i].second];
            if ( directions[vp[i].second] == 'R' ){
                while ( !st.empty() ){
                    int tp = st.top();
                    st.pop();
                    if ( healths[tp] < hlth ){
                        hlth--;
                        healths[tp] = 0;
                    }else if ( healths[tp] == hlth ){
                        hlth = 0;
                        healths[tp] = 0;
                        break;
                    }else{
                        healths[tp]--;
                        st.push(tp);
                        hlth = 0;
                        break;
                    }
                }
                healths[vp[i].second] = hlth;
            }else{
                st.push(vp[i].second);
            }
        }
        vector<int>ans;
        for (int i = 0; i<n; i++){
            if ( healths[i] ){
                ans.push_back(healths[i]);
            }
        }
        return ans;
    }
};





























class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();

        //{position, index}
        vector<pair<int,int>> robots;
        for (int i = 0; i < n; i++) {
            robots.push_back({positions[i], i});
        }
        sort(robots.begin(), robots.end());

        stack<int> st;

        for (int i = 0; i < n; i++) {
            int idx = robots[i].second;

            if (directions[idx] == 'R') {
                st.push(i);
            } else {
                while (!st.empty() && healths[idx] > 0) {
                    int j = st.top();
                    int idxR = robots[j].second;

                    if (healths[idxR] < healths[idx]) {
                        st.pop();
                        healths[idx] -= 1;
                        healths[idxR] = 0;
                    } else if (healths[idxR] > healths[idx]) {
                        healths[idxR] -= 1;
                        healths[idx] = 0;
                        break;
                    } else {
                        st.pop();
                        healths[idxR] = 0;
                        healths[idx] = 0;
                        break;
                    }
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (healths[i] > 0) {
                ans.push_back(healths[i]);
            }
        }
        return ans;
    }
};

























class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        
        int n = positions.size();
        // store {position, health, direction, original index}
        vector<tuple<int,int,char,int>> robots;
        
        for(int i = 0; i < n; i++) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }
        
        // sort by position
        sort(robots.begin(), robots.end());
        
        stack<int> st; // indices of robots in vector
        vector<int> finalHealth(n);
        
        for(int i = 0; i < n; i++) {
            auto &[pos, health, dir, idx] = robots[i];
            
            if(dir == 'R') {
                st.push(i);
            } 
            else {
                // dir == 'L'
                while(!st.empty() && health > 0) {
                    auto &[posR, healthR, dirR, idxR] = robots[st.top()];
                    
                    if(healthR < health) {
                        st.pop();
                        health--;
                    }
                    else if(healthR > health) {
                        healthR--;
                        health = 0;
                    }
                    else {
                        st.pop();
                        health = 0;
                    }
                }
                
                if(health > 0) {
                    finalHealth[idx] = health;
                }
            }
        }
        
        // remaining stack robots survive
        while(!st.empty()) {
            auto &[pos, health, dir, idx] = robots[st.top()];
            st.pop();
            finalHealth[idx] = health;
        }
        
        // collect result in original order
        vector<int> result;
        for(int i = 0; i < n; i++) {
            if(finalHealth[i] > 0) {
                result.push_back(finalHealth[i]);
            }
        }
        
        return result;
    }
};

















class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int size = positions.size();
        vector<int> indices(size);
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&](int idx1, int idx2) {
            return positions[idx1] < positions[idx2];
        });

        int l = 0, r = 0;
        for (int r = 0; r < size; r++) {
            if (directions[indices[r]] == 'R') {
                indices[l++] = indices[r];
                continue;
            }
            int &hpCurr = healths[indices[r]];
            while (l && directions[indices[l - 1]] == 'R' && hpCurr) {
                // R-L
                int &hpPrev = healths[indices[l - 1]];
                if (hpPrev > hpCurr) {
                    hpCurr = 0;
                    if (--hpPrev == 0)
                        --l;
                } else if (hpPrev < hpCurr) {
                    hpPrev = 0;
                    --hpCurr;
                    --l;
                } else {
                    hpPrev = hpCurr = 0;
                    --l;
                }
            }
            if (hpCurr) {
                indices[l++] = indices[r];
            }
        }
        vector<int> res;
        for (const int hp: healths) {
            if (hp)
                res.push_back(hp);
        }
        return res;
    }
};