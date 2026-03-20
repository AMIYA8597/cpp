// 3070. Count Submatrices with Top-Left Element and Sum Less Than k




// You are given a 0-indexed integer matrix grid and an integer k.

// Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to k.

 

// Example 1:


// Input: grid = [[7,6,3],[6,6,1]], k = 18
// Output: 4
// Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.
// Example 2:


// Input: grid = [[7,2,9],[1,5,0],[2,6,6]], k = 20
// Output: 6
// Explanation: There are only 6 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 20.
 

// Constraints:

// m == grid.length 
// n == grid[i].length
// 1 <= n, m <= 1000 
// 0 <= grid[i][j] <= 1000
// 1 <= k <= 109





















class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<long long> col(n,0);
        int count = 0;
        for(int i = 0; i < m; i++) {
            long long curr =0;

            for(int j =0; j<n; j++) {
                col[j] += grid[i][j];
                curr += col[j];

                if(curr <= k) count++;
            }
        }
    return count;
    }
};






















































class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) 
    {
        int n=grid.size(),m=grid[0].size();

        for(int i=1; i<m; i++)
        {
            grid[0][i] += grid[0][i-1];
        }

        for(int i=1; i<n; i++)
        {
            int prefix=grid[i][0];
            grid[i][0] = grid[i-1][0] + prefix;
            for(int j=1; j<m; j++)
            {
                prefix+=grid[i][j];
                grid[i][j] = grid[i-1][j]+prefix;
            }
        }

        int ans=0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                if(grid[i][j] <= k) ans++;
            }
        }
        return ans;
        
    }
};































class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int countSubMatrix = 0;
        int tempSum = 0;
        int maxFound = false;

        int m = grid.size();
        int n = grid[0].size();
        vector<int> tempBuffer;
        if (m == 0 || n == 0) {
            return 0;
        }
        tempSum = 0;
        for (int j = 0; j < n; j++) 
        {
            tempBuffer.push_back(grid[0][j]);
            tempSum += grid[0][j];
            if (tempSum <= k) 
                countSubMatrix++;       
        }

        for (int i = 1; i < m; i++) {
            tempSum = 0;
            for (int j = 0; j < n; j++) {
                tempBuffer[j] += grid[i][j];
                tempSum +=tempBuffer[j];
                if (tempSum <= k) 
                    countSubMatrix++;
            }
        }

        /*for(int i = 0; i < m; i++) {
             tempSum = 0;
            for (int j = 0; j < n; j++) {
                for(int kndex = 0; kndex <= i; kndex++) {
                    tempSum += grid[kndex][j];
                    if (tempSum > k) {  
                        break;
                    }
                }
                if (tempSum <= k) {
                    countSubMatrix++;                    
                }
                else {
                    //maxFound = true;
                    break;
                }
            }
            if (maxFound) {
                break;
            }
        } */
        return countSubMatrix;
    }
};








































class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int countSubMatrix = 0;
        int tempSum = 0;
        int maxFound = false;

        int m = grid.size();
        int n = grid[0].size();
        vector<int> tempBuffer;
        if (m == 0 || n == 0) {
            return 0;
        }
        tempSum = 0;
        for (int j = 0; j < n; j++) 
        {
            tempBuffer.push_back(grid[0][j]);
            tempSum += grid[0][j];
            if (tempSum <= k) 
                countSubMatrix++;       
        }

        for (int i = 1; i < m; i++) {
            tempSum = 0;
            for (int j = 0; j < n; j++) {
                tempBuffer[j] += grid[i][j];
                tempSum +=tempBuffer[j];
                if (tempSum <= k) 
                    countSubMatrix++;
            }
        }

        /*for(int i = 0; i < m; i++) {
             tempSum = 0;
            for (int j = 0; j < n; j++) {
                for(int kndex = 0; kndex <= i; kndex++) {
                    tempSum += grid[kndex][j];
                    if (tempSum > k) {  
                        break;
                    }
                }
                if (tempSum <= k) {
                    countSubMatrix++;                    
                }
                else {
                    //maxFound = true;
                    break;
                }
            }
            if (maxFound) {
                break;
            }
        } */
        return countSubMatrix;
    }
};




























 class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int row = 0, col = 0;
        for (int sum = 0; row < m; ++row) {
            sum += grid[row][0];
            if (sum > k) break;
            grid[row][0] = sum;
        }
        for (int sum = 0; col < n; ++col) {
            sum += grid[0][col];
            if (sum > k) break;
            grid[0][col] = sum;
        }
        if (!row && !col) return 0;
        int res = row + col - 1;
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
                if (grid[i][j] <= k) ++res;
            }
        }
        return res;
    }
};