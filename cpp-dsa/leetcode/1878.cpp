// 1878. Get Biggest Three Rhombus Sums in a Grid
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix grid​​​.

// A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:


// Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.

// Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.

 

// Example 1:


// Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 20 + 3 + 200 + 5 = 228
// - Red: 200 + 2 + 10 + 4 = 216
// - Green: 5 + 200 + 4 + 2 = 211
// Example 2:


// Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [20,9,8]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 4 + 2 + 6 + 8 = 20
// - Red: 9 (area 0 rhombus in the bottom right corner)
// - Green: 8 (area 0 rhombus in the bottom middle)
// Example 3:

// Input: grid = [[7,7,7]]
// Output: [7]
// Explanation: All three possible rhombus sums are the same, so return [7].
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 50
// 1 <= grid[i][j] <= 105
















class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        set<int, greater<int>> sums;
        for(int i =0; i<m; i++) {
            for(int j =0; j<n; j++) {
                sums.insert(grid[i][j]);

                for(int k =1; ; k++) {
                    if(i-k <0 || i+k >= m || j-k <0 || j+k >= n)
                    break;
                    int sum =0;
                    int x = i-k, y =j;

                    for(int t =0; t< k; t++) {
                        sum +=grid[x+t] [y+t];
                    }

                    for(int t =0; t< k; t++) {
                        sum +=grid[i+t] [j+k-t];
                    }

                    for(int t =0; t< k; t++) {
                        sum +=grid[i+k-t] [j-t];
                    }

                    for(int t =0; t< k; t++) {
                        sum +=grid[i-t] [j-k+t];
                    }

                    sums.insert(sum);
                }
            }
        }

        vector<int> ans;

        for(int x: sums) {
            ans.push_back(x);
            if(ans.size() == 3)
            break;
        }

        return ans;

    }
};









































// diag[diagonal_id][index]
// 50x50 grid, max i+j is 98, max i-j is 49
unsigned diag[150][51], antid[150][51]; 
const int OFFSET=50;

class Solution {
public:
    static inline int rhombusSum(int i, int j, int d, vector<vector<int>>& grid) {
        if (d==0) return grid[i][j];
        
        const int l=j-d, r=j+d, u=i-d, b=i+d ;
        
        // Diagonals with corner (\) 
        // sum=diag[id][end]-diag[id][start]
        const int i0=u-j+OFFSET, i1=i-l+OFFSET;
        int sum=diag[i0][r+1]-diag[i0][j];
        sum+=diag[i1][j+1]-diag[i1][l];
        
        // Anti-diagonals without corners (/) 
        const int j0=u+j, j1=b+j;
        sum+=antid[j0][i]-antid[j0][u+1];
        sum+=antid[j1][b]-antid[j1][i+1];

        return sum;
    }

    static vector<int> getBiggestThree(vector<vector<int>>& grid) {
        const int m=grid.size(), n=grid[0].size();
        
        memset(diag, 0, sizeof(diag));
        memset(antid, 0, sizeof(antid));

        for (int i=0; i< m; i++) {
            for (int j = 0; j < n; j++) {
                const int i0=i-j+OFFSET, j0=i+j;
                const int x=grid[i][j];
                // diag over j, antid over i
                diag[i0][j+1]=diag[i0][j]+x;
                antid[j0][i+1]=antid[j0][i]+x;
            }
        }

  
        int dM=min(m, n)/2; 
        vector<int> x(3, -1);
        for (int d=0; d<=dM; d++) {
            for (int i=d; i<m-d; i++) {
                for (int j=d; j<n-d; j++) {
                    const int y=rhombusSum(i, j, d, grid);

                    // Skip if y is already in our top 3 
                    if (y==x[0] || y==x[1] || y==x[2]) continue;

                    if (y>x[0]) {
                        x[2]=x[1];
                        x[1]=exchange(x[0], y);
                    }
                    else if (y>x[1]) 
                        x[2]=exchange(x[1], y);
                    else if (y>x[2]) 
                        x[2]=y;
                }
            }
        }
        for(int i=2; i>=0; i--) 
            if (x[i]==-1) x.pop_back();
        return x;
    }
};







































// https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/editorial
struct Answer {
    array<int, 3> ans{};

    void put(int x) {
        if (x > ans[0]) {
            tie(ans[0], ans[1], ans[2]) = tuple{x, ans[0], ans[1]};
        } else if (x != ans[0] && x > ans[1]) {
            tie(ans[1], ans[2]) = tuple{x, ans[1]};
        } else if (x != ans[0] && x != ans[1] && x > ans[2]) {
            ans[2] = x;
        }
    }

    vector<int> get() const {
        vector<int> ret;
        for (int num : ans) {
            if (num) {
                ret.push_back(num);
            }
        }
        return ret;
    }
};

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sum1(m + 1, vector<int>(n + 2));
        vector<vector<int>> sum2(m + 1, vector<int>(n + 2));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum1[i][j] = sum1[i - 1][j - 1] + grid[i - 1][j - 1];
                sum2[i][j] = sum2[i - 1][j + 1] + grid[i - 1][j - 1];
            }
        }
        Answer ans;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // a single cell is also a rhombus
                ans.put(grid[i][j]);
                for (int k = i + 2; k < m; k += 2) {
                    int ux = i, uy = j;
                    int dx = k, dy = j;
                    int lx = (i + k) / 2, ly = j - (k - i) / 2;
                    int rx = (i + k) / 2, ry = j + (k - i) / 2;
                    if (ly < 0 || ry >= n) {
                        break;
                    }
                    ans.put((sum2[lx + 1][ly + 1] - sum2[ux][uy + 2]) +
                            (sum1[rx + 1][ry + 1] - sum1[ux][uy]) +
                            (sum1[dx + 1][dy + 1] - sum1[lx][ly]) +
                            (sum2[dx + 1][dy + 1] - sum2[rx][ry + 2]) -
                            (grid[ux][uy] + grid[dx][dy] + grid[lx][ly] +
                             grid[rx][ry]));
                }
            }
        }
        return ans.get();
    }
};

































class Solution {
    vector<vector<int>> diag, anti;
    int row, col;
    int calcSum(int midR, int midC, int len) {
        if (!len)
            return diag[midR][midC] - (midR && midC ? diag[midR - 1][midC - 1] : 0);
        int topR = midR - len, topC = midC;
        int leftR = midR, leftC = midC - len;
        int bottomR = midR + len, bottomC = midC;
        int rightR = midR, rightC = midC + len;
          
        return diag[rightR][rightC] - (topR && topC ? diag[topR - 1][topC - 1] : 0)
                + diag[bottomR][bottomC] - (leftR && leftC ? diag[leftR - 1][leftC - 1] : 0)
                + anti[leftR - 1][leftC + 1] - anti[topR][topC]
                + anti[bottomR - 1][bottomC + 1] - anti[rightR][rightC];
    }
    void update(vector<int> &res, int val) {
        if (val == res[0] || val == res[1] || val == res[2] || val < res[2])
            return;
        res.push_back(val);
        sort(res.begin(), res.end(), greater<int>());
        if (res.size() > 3)
            res.pop_back();
    }
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        row = grid.size(), col = grid[0].size();
        diag = anti = vector<vector<int>>(row, vector<int>(col, 0));
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                diag[r][c] = grid[r][c] + (r && c ? diag[r - 1][c - 1] : 0);
                anti[r][c] = grid[r][c] + (r && c + 1 < col ? anti[r - 1][c + 1] : 0);
            }
        }

        vector<int> res(3, 0);
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                int limit = min({r, row - 1 - r, c, col - 1 - c});
                for (int len = 0; len <= limit; len++) {
                    update(res, calcSum(r, c, len));
                }
            }
        }
        while (!res.empty() && res.back() == 0)
            res.pop_back();


        return res;
    }
};














