2069. Walking Robot Simulation II



A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1, height - 1). The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). A robot is initially at cell (0, 0) facing direction "East".

The robot can be instructed to move for a specific number of steps. For each step, it does the following.

Attempts to move forward one cell in the direction it is facing.
If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and retries the step.
After the robot finishes moving the number of steps required, it stops and awaits the next instruction.

Implement the Robot class:

Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
void step(int num) Instructs the robot to move forward num steps.
int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".
 

Example 1:

example-1
Input
["Robot", "step", "step", "getPos", "getDir", "step", "step", "step", "getPos", "getDir"]
[[6, 3], [2], [2], [], [], [2], [1], [4], [], []]
Output
[null, null, null, [4, 0], "East", null, null, null, [1, 2], "West"]

Explanation
Robot robot = new Robot(6, 3); // Initialize the grid and the robot at (0, 0) facing East.
robot.step(2);  // It moves two steps East to (2, 0), and faces East.
robot.step(2);  // It moves two steps East to (4, 0), and faces East.
robot.getPos(); // return [4, 0]
robot.getDir(); // return "East"
robot.step(2);  // It moves one step East to (5, 0), and faces East.
                // Moving the next step East would be out of bounds, so it turns and faces North.
                // Then, it moves one step North to (5, 1), and faces North.
robot.step(1);  // It moves one step North to (5, 2), and faces North (not West).
robot.step(4);  // Moving the next step North would be out of bounds, so it turns and faces West.
                // Then, it moves four steps West to (1, 2), and faces West.
robot.getPos(); // return [1, 2]
robot.getDir(); // return "West"

 

Constraints:

2 <= width, height <= 100
1 <= num <= 105
At most 104 calls in total will be made to step, getPos, and getDir.




























  class Robot {
private:
    int w, h;
    int x, y;
    int dir; // 0=East, 1=North, 2=West, 3=South
    int perimeter;
    
    vector<string> dirs = {"East", "North", "West", "South"};
    vector<pair<int,int>> moves = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    
public:
    Robot(int width, int height) {
        w = width;
        h = height;
        x = 0;
        y = 0;
        dir = 0; // East
        perimeter = 2 * (w + h - 2);
    }
    
    void step(int num) {
        num %= perimeter;
        
        // Special case: full cycle → direction becomes South
        if (num == 0 && x == 0 && y == 0) {
            dir = 3;
            return;
        }
        
        while (num--) {
            int nx = x + moves[dir].first;
            int ny = y + moves[dir].second;
            
            // If out of bounds → turn left
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) {
                dir = (dir + 1) % 4;
                nx = x + moves[dir].first;
                ny = y + moves[dir].second;
            }
            
            x = nx;
            y = ny;
        }
    }
    
    vector<int> getPos() {
        return {x, y};
    }
    
    string getDir() {
        return dirs[dir];
    }
};






































#pragma GCC optimize("Ofast,unroll-loops,inline")
#include <vector>
#include <string>

static const int speedup = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class Robot {
    int w, h, p, curr;
    bool moved;
    // Используем массив строк, чтобы обращаться по индексу (0-3) без if-else
    const std::string dirs[4] = {"East", "North", "West", "South"};

public:
    Robot(int width, int height) : w(width), h(height), curr(0), moved(false) {
        p = (w + h - 2) << 1;
    }
    
    inline void step(int num) {
        moved = true;
        curr = (curr + num) % p;
    }
    
    inline std::vector<int> getPos() {
        if (curr < w) return {curr, 0};
        if (curr < w + h - 1) return {w - 1, curr - w + 1};
        if (curr < (w << 1) + h - 2) return { (w << 1) + h - 3 - curr, h - 1};
        return {0, p - curr};
    }
    
    inline std::string getDir() {
        if (!moved) return dirs[0];
        if (curr == 0) return dirs[3]; // Робот вернулся в начало — всегда South
        
        // Математическое определение направления без тяжелых веток
        if (curr < w) return dirs[0];
        if (curr < w + h - 1) return dirs[1];
        if (curr < (w << 1) + h - 2) return dirs[2];
        return dirs[3];
    }
};































class Robot {
public:
  Robot(int width, int height) : width(width), height(height) {}
  
  void step(int num) {
    // cout << "stepping: " << num << " at perimeter_index: " << perimeter_index << '\n';
    perimeter_index = (perimeter_index + num) % perimeter_cycle_length();
    // auto pos = getPos();
    // cout << "new perimeter_index: " << perimeter_index << " (" << pos[0] << ", " << pos[1] << ")\n";
    if (perimeter_index == ll_index() || perimeter_index > ul_index()) {
      dir_index = south;
    } else if (perimeter_index <= lr_index()) {
      dir_index = east;
    } else if (perimeter_index <= ur_index()) {
      dir_index = north;
    } else {
      dir_index = west;
    }
  }
  
  vector<int> getPos() {
    if (perimeter_index <= lr_index()) {
      return {perimeter_index, 0};
    } else if (perimeter_index <= ur_index()) {
      auto offset = perimeter_index - lr_index();
      return {width - 1, offset};
    } else if (perimeter_index <= ul_index()) {
      auto offset = perimeter_index - ur_index();
      return {width - 1 - offset, height - 1};
    } else {
      auto offset = perimeter_index - ul_index();
      return {0, height - 1 - offset};
    }
  }
  
  string getDir() {
    return dirs[dir_index];
  }

private:
  int width;
  int height;
  int perimeter_index = 0;
  int dir_index = 0;
  static constexpr inline int east = 0;
  static constexpr inline int north = 1;
  static constexpr inline int west = 2;
  static constexpr inline int south = 3;
  static constexpr inline array<string, 4> dirs = {
      "East", "North", "West", "South"
  };

  int perimeter_cycle_length() {
     return (width + height - 2) << 1;
  }

  int ll_index() {
    return 0;
  }

  int lr_index() {
    return width - 1;
  }

  int ur_index() {
    return lr_index() + height - 1;
  }

  int ul_index() {
    return ur_index() + width - 1;
  }

};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */

































class Robot {
private:
    vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    vector<string> stringdir = {"East", "North", "West", "South"};
    int currdir;
    int posx, posy;
    int height, width;
    int perimeter;

public:
    Robot(int width, int height) : currdir(0), posx(0), posy(0), height(height), width(width) {
        perimeter = 2*height+2*width-4;
    }
    
    void step(int num) {
        num = num % (perimeter);
        if (num == 0) num = perimeter;

        int dx = dirs[currdir][0];
        int dy = dirs[currdir][1];
        int newposx = posx + dx*num;
        int newposy = posy + dy*num;

        if (newposx < 0){
            posx = 0;
            currdir = (currdir+1)%4;
            step(-newposx);
            return;
        }
        else if (newposx > width-1){
            posx = width - 1;
            currdir = (currdir+1)%4;
            step(newposx-posx);
            return;
        }
        else if (newposy < 0){
            posy = 0;
            currdir = (currdir+1)%4;
            step(-newposy);
            return;
        }
        else if (newposy > height-1){
            posy = height - 1;
            currdir = (currdir+1)%4;
            step(newposy-posy);
            return;
        }
        posx = newposx;
        posy = newposy;
    }
    
    vector<int> getPos() {
        return {posx, posy};
    }
    
    string getDir() {
        return stringdir[currdir];
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
































class Robot {
public:
    int dir = 0; //0 = east, 1 = north, 2 = west, 3 = south
    int stepp = 0;
    int x = 0, y = 0, w, h, xx;

    Robot(int width, int height) {
        w = width;
        h = height;
        xx = 2*((w-1) + (h-1));
    }
    
    void step(int num) {
        stepp+=num;
    }
    
    vector<int> getPos() {
        int z = stepp%xx;
        if(z<w){
            return {z, 0};
        }else if(z<(w+h-1)){
            return {w-1, z-w+1};
        }else if(z<(2*w+h-2)){
            return {2*w-z+h-3, h-1};
        }else{
            return {0, 2*h+2*w -z-4};
        }
    }
    
    string getDir() {
        if(stepp==0) return "East";
        int z = stepp%xx;

        if(z>0 && z<w) return "East";
        if(z>0 && z<(w+h-1)) return "North";
        else if(z>0 && z<(2*w+h-2)) return "West";
        else return "South";
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */



































static auto init = []() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return nullptr;
}();


class Robot {
public:
  Robot(int width, int height) : width(width), height(height) {}
  
  void step(int num) {
    perimeter_index = (perimeter_index + num) % perimeter_cycle_length();
    if (perimeter_index == ll_index() || perimeter_index > ul_index()) {
      dir_index = south;
    } else if (perimeter_index <= lr_index()) {
      dir_index = east;
    } else if (perimeter_index <= ur_index()) {
      dir_index = north;
    } else {
      dir_index = west;
    }
  }
  
  vector<int> getPos() {
    if (perimeter_index <= lr_index()) {
      return {perimeter_index, 0};
    } else if (perimeter_index <= ur_index()) {
      auto offset = perimeter_index - lr_index();
      return {width - 1, offset};
    } else if (perimeter_index <= ul_index()) {
      auto offset = perimeter_index - ur_index();
      return {width - 1 - offset, height - 1};
    } else {
      auto offset = perimeter_index - ul_index();
      return {0, height - 1 - offset};
    }
  }
  
  string getDir() {
    return dirs[dir_index];
  }

private:
  int width;
  int height;
  int perimeter_index = 0;
  int dir_index = 0;
  static constexpr int east = 0;
  static constexpr int north = 1;
  static constexpr int west = 2;
  static constexpr int south = 3;
  static constexpr inline array<string, 4> dirs = {
      "East", "North", "West", "South"
  };

  int perimeter_cycle_length() {
     return (width + height - 2) << 1;
  }

  int ll_index() {
    return 0;
  }

  int lr_index() {
    return width - 1;
  }

  int ur_index() {
    return lr_index() + height - 1;
  }

  int ul_index() {
    return ur_index() + width - 1;
  }

};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */


































#pragma GCC optimize("Ofast,unroll-loops,inline")
#include <vector>
#include <string>

static const int speedup = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    return 0;
}();

class Robot {
    int w, h, p;
    int curr;
    bool moved;
    // Статический вектор, чтобы не выделять память в куче при каждом вызове getPos
    std::vector<int> pos_res;

public:
    Robot(int width, int height) : w(width), h(height), curr(0), moved(false), pos_res(2) {
        p = (w + h - 2) << 1;
    }
    
    // Используем inline для исключения затрат на вызов функции
    inline void step(int num) {
        moved = true;
        curr = (curr + num) % p;
    }
    
    inline std::vector<int> getPos() {
        if (curr < w) {
            pos_res[0] = curr; pos_res[1] = 0;
        } else if (curr < w + h - 1) {
            pos_res[0] = w - 1; pos_res[1] = curr - w + 1;
        } else if (curr < (w << 1) + h - 2) {
            pos_res[0] = (w << 1) + h - 3 - curr; pos_res[1] = h - 1;
        } else {
            pos_res[0] = 0; pos_res[1] = p - curr;
        }
        return pos_res;
    }
    
    inline std::string getDir() {
        if (!moved) return "East";
        if (curr == 0) return "South";
        if (curr < w) return "East";
        if (curr < w + h - 1) return "North";
        if (curr < (w << 1) + h - 2) return "West";
        return "South";
    }
};






















static auto init = []() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return nullptr;
}();


class Robot {
public:
  Robot(int width, int height) : width(width), height(height) {}
  
  void step(int num) {
    perimeter_index = (perimeter_index + num) % perimeter_cycle_length();
    if (perimeter_index == ll_index() || perimeter_index > ul_index()) {
      dir_index = south;
    } else if (perimeter_index <= lr_index()) {
      dir_index = east;
    } else if (perimeter_index <= ur_index()) {
      dir_index = north;
    } else {
      dir_index = west;
    }
  }
  
  vector<int> getPos() {
    if (perimeter_index <= lr_index()) {
      return {perimeter_index, 0};
    } else if (perimeter_index <= ur_index()) {
      auto offset = perimeter_index - lr_index();
      return {width - 1, offset};
    } else if (perimeter_index <= ul_index()) {
      auto offset = perimeter_index - ur_index();
      return {width - 1 - offset, height - 1};
    } else {
      auto offset = perimeter_index - ul_index();
      return {0, height - 1 - offset};
    }
  }
  
  string getDir() {
    return dirs[dir_index];
  }

private:
  int width;
  int height;
  int perimeter_index = 0;
  int dir_index = 0;
  static constexpr inline int east = 0;
  static constexpr inline int north = 1;
  static constexpr inline int west = 2;
  static constexpr inline int south = 3;
  static constexpr inline array<string, 4> dirs = {
      "East", "North", "West", "South"
  };

  int perimeter_cycle_length() {
     return (width + height - 2) << 1;
  }

  int ll_index() {
    return 0;
  }

  int lr_index() {
    return width - 1;
  }

  int ur_index() {
    return lr_index() + height - 1;
  }

  int ul_index() {
    return ur_index() + width - 1;
  }

};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
