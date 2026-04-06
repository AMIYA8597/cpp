874. Walking Robot Simulation


A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:

-2: Turn left 90 degrees.
-1: Turn right 90 degrees.
1 <= k <= 9: Move forward k units, one unit at a time.
Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.

Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).

Note:

There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
North means +Y direction.
East means +X direction.
South means -Y direction.
West means -X direction.
 

Example 1:

Input: commands = [4,-1,3], obstacles = []

Output: 25

Explanation:

The robot starts at (0, 0):

Move north 4 units to (0, 4).
Turn right.
Move east 3 units to (3, 4).
The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.

Example 2:

Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]

Output: 65

Explanation:

The robot starts at (0, 0):

Move north 4 units to (0, 4).
Turn right.
Move east 1 unit and get blocked by the obstacle at (2, 4), robot is at (1, 4).
Turn left.
Move north 4 units to (1, 8).
The furthest point the robot ever gets from the origin is (1, 8), which squared is 12 + 82 = 65 units away.

Example 3:

Input: commands = [6,-1,-1,6], obstacles = [[0,0]]

Output: 36

Explanation:

The robot starts at (0, 0):

Move north 6 units to (0, 6).
Turn right.
Turn right.
Move south 5 units and get blocked by the obstacle at (0,0), robot is at (0, 1).
The furthest point the robot ever gets from the origin is (0, 6), which squared is 62 = 36 units away.

 

Constraints:

1 <= commands.length <= 104
commands[i] is either -2, -1, or an integer in the range [1, 9].
0 <= obstacles.length <= 104
-3 * 104 <= xi, yi <= 3 * 104
The answer is guaranteed to be less than 231.










































class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};

        unordered_set<string> obs;
        for (auto &o : obstacles) {
            obs.insert(to_string(o[0]) + "#" + to_string(o[1]));
        }

        int x = 0, y = 0, dir = 0, maxDist = 0;

        for (int cmd : commands) {
            if (cmd == -2) {
                dir = (dir + 3) % 4;
            } else if (cmd == -1) {
                dir = (dir + 1) % 4;
            } else {
                for (int i = 0; i < cmd; i++) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    string key = to_string(nx) + "#" + to_string(ny);
                    if (obs.count(key)) break;
                    x = nx;
                    y = ny;
                    maxDist = max(maxDist, x * x + y * y);
                }
            }
        }
        return maxDist;
    }
};






























#pragma GCC optimize("Ofast,unroll-loops,inline")
#pragma GCC target("avx2,bmi,bmi2")

static const int _ = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

// Используем огромный разреженный массив как хэш-таблицу.
// 65536 — это степень двойки, маска будет летать.
long long ht[65536]; 
const long long EMPTY = -1e15;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Быстрое зануление через memset — это SIMD уровень.
        for(int i = 0; i < 65536; ++i) ht[i] = EMPTY;

        for (const auto& obs : obstacles) {
            long long key = ((long long)obs[0] << 32) | (obs[1] & 0xFFFFFFFFLL);
            int h = (unsigned int)(key ^ (key >> 32)) & 65535; // Маска вместо %
            while (ht[h] != EMPTY) h = (h + 1) & 65535;
            ht[h] = key;
        }

        // Направления в константах, чтобы не лезть в память лишний раз
        int x = 0, y = 0, dir = 0;
        int maxDistSq = 0;

        for (int cmd : commands) {
            if (cmd < 0) {
                // Магия: (dir + 1) & 3 — это поворот вправо, (dir + 3) & 3 — влево.
                if (cmd == -1) dir = (dir + 1) & 3;
                else dir = (dir + 3) & 3;
            } else {
                // Кэшируем смещения прямо здесь
                int dx = (dir == 1) ? 1 : (dir == 3 ? -1 : 0);
                int dy = (dir == 0) ? 1 : (dir == 2 ? -1 : 0);
                
                while (cmd--) {
                    int nx = x + dx;
                    int ny = y + dy;
                    long long key = ((long long)nx << 32) | (ny & 0xFFFFFFFFLL);
                    
                    // Ультра-быстрый поиск
                    int h = (unsigned int)(key ^ (key >> 32)) & 65535;
                    bool hit = false;
                    while (ht[h] != EMPTY) {
                        if (ht[h] == key) { hit = true; break; }
                        h = (h + 1) & 65535;
                    }
                    
                    if (hit) break;
                    x = nx; y = ny;
                }
                int cur = x * x + y * y;
                if (cur > maxDistSq) maxDistSq = cur;
            }
        }
        return maxDistSq;
    }
};































#include <memory_resource>
pmr::unsynchronized_pool_resource pool;
class Solution {
public:
    static int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const long long M=60001, lb=-30000;
        pmr::unordered_set<long long> obSet(&pool);
        obSet.reserve(obstacles.size());
        for(auto& ob: obstacles){
            const long long x=ob[0]-lb, y=ob[1]-lb;
            obSet.insert(x*M+y);
        }

        const int dir[4][2]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
        int x=0, y=0, dx=0, dy=1, face=0, maxD2=0;
        for(int c: commands){
            switch(c){
                case -2: face=(face+1)%4; dx=dir[face][0]; dy=dir[face][1]; break;
                case -1: face=(face+3)%4; dx=dir[face][0]; dy=dir[face][1]; break;
                default:
                //    cout<<"\nc="<<c<<" face="<<face<<":";
                    for(int i=0; i<c; i++){
                        x+=dx, y+=dy;
                        if (obSet.count((x-lb)*M+y-lb)) {
                            x-=dx;  // previous move
                            y-=dy;
                            break;
                        }
                    //    cout<<"("<<x<<","<<y<<"),";
                        maxD2=max(maxD2, x*x+y*y);
                    }
            }
        }
        return maxD2;
    }
};


































enum DIRECTIONS {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
};
class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<int64_t> obstacles_map;
        for (const auto &pos : obstacles) {
            obstacles_map.insert(((int64_t)pos.at(0) << 32) | (uint32_t)pos.at(1));
        }

        int currX = 0;
        int currY = 0;
        enum DIRECTIONS current_direction = NORTH;
        int max_distance = 0;
        for (int command : commands) {
            if (command == -1) {
                current_direction = (enum DIRECTIONS)((current_direction + 1) % 4);
            }
            if (command == -2) {
                current_direction =  (enum DIRECTIONS)((4 + (current_direction - 1) % 4) % 4);
            }
            for (int curr = 0; curr < command; curr +=1) {
                int newX = currX;
                int newY = currY;
                if (current_direction == NORTH) newY+=1;
                else if (current_direction == SOUTH) newY-=1;
                else if (current_direction == EAST) newX+=1;
                else if (current_direction == WEST) newX-=1;

                if (obstacles_map.contains(((int64_t)newX << 32) | (uint32_t)newY))
                    break;

                currX = newX;
                currY = newY;
                int new_distance = currX*currX + currY*currY;
                if (new_distance > max_distance) max_distance = new_distance;
            }
        }

        return max_distance;
    }
};

































class Solution {
 public:
  int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    constexpr int kDirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int ans = 0;
    int d = 0;  // 0 := north, 1 := east, 2 := south, 3 := west
    int x = 0;  // the start x
    int y = 0;  // the start y
    unordered_set<pair<int, int>, PairHash> obstaclesSet;

    for (const vector<int>& obstacle : obstacles) {
      const int x = obstacle[0];
      const int y = obstacle[1];
      obstaclesSet.insert({x, y});
    }

    for (const int command : commands) {
      if (command == -1) {
        d = (d + 1) % 4;
      } else if (command == -2) {
        d = (d + 3) % 4;
      } else {
        for (int step = 0; step < command; ++step) {
          if (obstaclesSet.contains({x + kDirs[d][0], y + kDirs[d][1]}))
            break;
          x += kDirs[d][0];
          y += kDirs[d][1];
        }
      }
      ans = max(ans, x * x + y * y);
    }

    return ans;
  }

 private:
  struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
      return p.first ^ p.second;
    }
  };
};































class Solution {
public:
    static int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        const long long M=60001, lb=-30000;
        unordered_set<long long> obSet;
        obSet.reserve(obstacles.size());
        for(auto& ob: obstacles){
            long long x=ob[0]-lb, y=ob[1]-lb;
            obSet.insert(x*M+y);
        }

        const int dir[4][2]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
        int x=0, y=0, dx=0, dy=1, face=0, maxD2=0;
        for(int c: commands){
            switch(c){
                case -2: face=(face+1)%4; dx=dir[face][0]; dy=dir[face][1]; break;
                case -1: face=(face+3)%4; dx=dir[face][0]; dy=dir[face][1]; break;
                default:
                //    cout<<"\nc="<<c<<" face="<<face<<":";
                    for(int i=0; i<c; i++){
                        x+=dx, y+=dy;
                        if (obSet.count((x-lb)*M+y-lb)) {
                            x-=dx;  // previous move
                            y-=dy;
                            break;
                        }
                    //    cout<<"("<<x<<","<<y<<"),";
                        maxD2=max(maxD2, x*x+y*y);
                    }
            }
        }
        return maxD2;
    }
};




































class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // lambda functions

        auto f = [](int x, int y) {
            return x * 60010 + y;
        };

        unordered_set<int> st;
        for(auto &obs : obstacles){
            st.insert( f(obs[0], obs[1]) ) ;
        }

        vector<pair<int,int>> dir = { {0,1} , {1,0} , {0,-1}, {-1,0}};
        //                            north    east    south   west

        int x = 0 , y =0;
        int d = 0; //north
        long long max_dist = 0;

        for(int cmd : commands){
            if(cmd == -2){
                d = (d+3)%4 ;
            } else if (cmd == -1){
                d = (d+1)%4 ;
            } else {
                for(int i = 0; i<cmd; i++){
                    int nx = x + dir[d].first;
                    int ny = y + dir[d].second;

                    int key = f(nx , ny);

                    if(st.find(key) != st.end()){
                        break;
                    }

                    x = nx;
                    y = ny;

                    max_dist = max( max_dist, 1LL*x*x + 1LL* y*y);
                
                }
            }
        }
        
        return max_dist;
    }
};































class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        reverse(commands.begin(),commands.end());
        std::set<pair<int,int>> set;
        for(auto& n:obstacles)set.insert({n[0],n[1]});
        vector<pair<int,int>> moveMap{{0,1},{1,0},{0,-1},{-1,0}};
        int dir=0;
        int posX=0;
        int posY=0;
        int ans=0;
        while(commands.size()){
            if(commands.back()==0){
                commands.pop_back();
            }else if(commands.back()==-1){
                dir++;
                dir%=4;
                commands.pop_back();
            }else if(commands.back()==-2){
                dir+=3;
                dir%=4;
                commands.pop_back();
            }else{
                auto[moveX,moveY]=moveMap[dir];
                if(set.contains({moveX+posX,moveY+posY})){
                    commands.pop_back();                
                }else{
                    posX+=moveX;
                    posY+=moveY;
                    commands.back()--;
                }
            }
            ans=max(ans,posX*posX+posY*posY);
        }
        return ans;
    }
};
