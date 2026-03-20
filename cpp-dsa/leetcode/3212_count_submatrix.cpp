// 3212. Count Submatrices With Equal Frequency of X and Y




// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:

// grid[0][0]
// an equal frequency of 'X' and 'Y'.
// at least one 'X'.
 

// Example 1:

// Input: grid = [["X","Y","."],["Y",".","."]]

// Output: 3

// Explanation:



// Example 2:

// Input: grid = [["X","X"],["X","Y"]]

// Output: 0

// Explanation:

// No submatrix has an equal frequency of 'X' and 'Y'.

// Example 3:

// Input: grid = [[".","."],[".","."]]

// Output: 0

// Explanation:

// No submatrix has at least one 'X'.

 

// Constraints:

// 1 <= grid.length, grid[i].length <= 1000
// grid[i][j] is either 'X', 'Y', or '.'.

















































class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> sum(n, vector<int>(m,0));
        vector<vector<int>>XCount(n, vector<int>(m, 0));

        for (int i =0; i<n; i++) {
            for (int j =0;j<m;j++) {
                int val =0;
                if (grid[i][j] =='X') val = 1;
                else if (grid[i][j]== 'Y') val =-1;

                sum[i][j] = val;
                XCount[i][j] = (grid[i][j] == 'X');
                if (i > 0) {
                    sum[i][j] += sum[i - 1][j];
                    XCount[i][j] +=XCount[i - 1][j];
                }
                if (j > 0) {
                    sum[i][j] += sum[i][j-1];
                    XCount[i][j] +=XCount[i][j-1];
                }
                if (i > 0 && j > 0) {
                    sum[i][j] -= sum[i - 1][j - 1];
                    XCount[i][j] -=XCount[i - 1][j - 1];
                }
            }
        }
        int ans =0;

        for (int i =0; i<n;i++) {
            for (int j=0; j<m; j++) {
                if (sum[i][j] == 0 && XCount[i][j] > 0) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

































class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& A) {
        int n = A.size(), m = A[0].size(), res = 0;
        vector<pair<int,int>> dp(m); // Create a DP array to store (hasX, diffCount) for each column
        
        // Iterate through each row
        for(auto& vec : A) {
            int sum = 0, fl = 0; // Initialize sum and flag for the current row
            
            // Iterate through each column in the current row
            for(int i = 0; i < m; i++) {
                if(vec[i] == 'X') {
                    fl = 1;  // Set flag if 'X' is encountered
                    sum++;   // Increment sum for 'X'
                } else if(vec[i] == 'Y') {
                    sum--;   // Decrement sum for 'Y'
                }
                
                dp[i].first |= fl;  // Update dp[i].first to indicate the presence of 'X' up to the current column
                dp[i].second += sum; // Update dp[i].second to maintain the cumulative difference
                
                // Check if the current submatrix meets the criteria
                if(dp[i].first and dp[i].second == 0) {
                    res++; // Increment the result counter if conditions are met
                }
            }
        }
        return res; // Return the count of valid submatrices
    }
};
























class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& A) {
        int n = A.size(), m = A[0].size(), res = 0;
        vector<pair<int,int>> dp(m); // Create a DP array to store (hasX, diffCount) for each column
        
        // Iterate through each row
        for(auto& vec : A) {
            int sum = 0, fl = 0; // Initialize sum and flag for the current row
            
            // Iterate through each column in the current row
            for(int i = 0; i < m; i++) {
                if(vec[i] == 'X') {
                    fl = 1;  // Set flag if 'X' is encountered
                    sum++;   // Increment sum for 'X'
                } else if(vec[i] == 'Y') {
                    sum--;   // Decrement sum for 'Y'
                }
                
                dp[i].first |= fl;  // Update dp[i].first to indicate the presence of 'X' up to the current column
                dp[i].second += sum; // Update dp[i].second to maintain the cumulative difference
                
                // Check if the current submatrix meets the criteria
                if(dp[i].first and dp[i].second == 0) {
                    res++; // Increment the result counter if conditions are met
                }
            }
        }
        return res; // Return the count of valid submatrices
    }
};






























class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        const int rows = grid.size();
        const int cols = grid[0].size();
        std::vector<int> xCount(cols);
        std::vector<int> yCount(cols);
        auto count = 0;
        for (auto row = 0; row < rows; ++row) {
            auto rowX = 0;
            auto rowY = 0;
            for (auto col = 0; col < cols; ++col) {
                rowX += grid[row][col] == 'X';
                rowY += grid[row][col] == 'Y';
                xCount[col] += rowX;
                yCount[col] += rowY;
                if (xCount[col] && xCount[col] == yCount[col]) ++count;
            }
        }
        return count;
    }
};






































class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        vector<pair<int,int>>prefix(m,{0,0});
        for(int i=0;i<n;i++){
            int x = 0 , y = 0;
            for(int j=0;j<m;j++){
                if(grid[j][i] == 'X') prefix[j].first++;
                else if(grid[j][i] =='Y') prefix[j].second++;
                x+=prefix[j].first;
                y+=prefix[j].second;
                if(x && x == y) ans++;
            }
        }
        return ans;
        
    }
};


































class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<int> colX(n,0), colY(n,0);
        int ans = 0;

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 'X') colX[j]++;
                if(grid[i][j] == 'Y') colY[j]++;
            }

            int x = 0, y = 0;

            for(int j = 0; j < n; j++){
                x += colX[j];
                y += colY[j];

                if(x == y && x > 0) ans++;
            }
        }

        return ans;
    }
};















































