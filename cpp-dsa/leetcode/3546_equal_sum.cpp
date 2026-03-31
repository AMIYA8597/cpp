3546. Equal Sum Grid Partition I
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:

Each of the two resulting sections formed by the cut is non-empty.
The sum of the elements in both sections is equal.
Return true if such a partition exists; otherwise return false.

 

Example 1:

Input: grid = [[1,4],[2,3]]

Output: true

Explanation:



A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.

Example 2:

Input: grid = [[1,3],[2,4]]

Output: false

Explanation:

No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is false.

 

Constraints:

1 <= m == grid.length <= 105
1 <= n == grid[i].length <= 105
2 <= m * n <= 105
1 <= grid[i][j] <= 105






































class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        long long totalSum = 0;
        
        // Step 1: Calculate total sum
        for (auto &row : grid) {
            for (int val : row) {
                totalSum += val;
            }
        }
        
        // If total sum is odd, can't split equally
        if (totalSum % 2 != 0) return false;
        
        long long target = totalSum / 2;
        
        // Step 2: Try horizontal cuts
        long long prefixSum = 0;
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                prefixSum += grid[i][j];
            }
            if (prefixSum == target) return true;
        }
        
        // Step 3: Compute column sums
        vector<long long> colSum(n, 0);
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                colSum[j] += grid[i][j];
            }
        }
        
        // Step 4: Try vertical cuts
        prefixSum = 0;
        for (int j = 0; j < n - 1; j++) {
            prefixSum += colSum[j];
            if (prefixSum == target) return true;
        }
        
        return false;
    }

    
};




























class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        long long total = 0;

        // total sum
        for (auto &row : grid) {
            for (auto &val : row) {
                total += val;
            }
        }

        // if odd → impossible
        if (total % 2 != 0) return false;

        long long target = total / 2;

        // 🔹 check horizontal cut
        long long curr = 0;
        for (int i = 0; i < m - 1; i++) {  // m-1 because last row not allowed
            for (int j = 0; j < n; j++) {
                curr += grid[i][j];
            }
            if (curr == target) return true;
        }

        // 🔹 check vertical cut
        curr = 0;
        for (int j = 0; j < n - 1; j++) {  // n-1 because last column not allowed
            for (int i = 0; i < m; i++) {
                curr += grid[i][j];
            }
            if (curr == target) return true;
        }

        return false;
    }
};



























class Solution {
public:

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int M = grid.size();
        int N = grid[0].size();
        long long totalSum = 0;
        vector<long long> rowSum(M, 0);
        vector<long long> colSum(N, 0);
        for(int x = 0; x < M; x++)
        {
            for(int y = 0; y < N; y++)
            {
                totalSum += grid[x][y];
            }
        }
            if(totalSum % 2 != 0)
        {
            return false;
        }
        long long halfSum = totalSum / 2;
        long long currentRow = 0;

        for(int x = 0; x < M; x++)
        {
            for(int y = 0; y < N; y++)
            {
                currentRow += grid[x][y];
                totalSum += grid[x][y];
            }
            if(currentRow == halfSum)
            {
                return true;
            }
            rowSum[x] = currentRow;
        }
                // We can't partition an odd total sum into two separate parts
        long long currentCol = 0;
        for(int y = 0; y < N; y++)
        {
            for(int x = 0; x < M; x++)
            {
                currentCol += grid[x][y];
                if(currentCol == halfSum)
                {
                    return true;
                }
            }

            colSum[y] = (currentCol);
        }


        for(const auto& sum : rowSum)
        {
            if (sum == halfSum)
            {
                return true;
            }
        }
        for(const auto& sum : colSum)
        {
            if (sum == halfSum)
            {
                return true;
            }
        }
        return false;

    }
};

























class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();

        vector<long long> row(n,0), col(m,0);

        // compute row and column sums
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                row[i] += grid[i][j];
                col[j] += grid[i][j];
            }
        }

        // check horizontal cut
        long long total = 0;
        for(auto x : row) total += x;

        long long prefix = 0;

        for(int i=0;i<n-1;i++){
            prefix += row[i];
            if(prefix == total - prefix)
                return true;
        }

        // check vertical cut
        total = 0;
        for(auto x : col) total += x;

        prefix = 0;

        for(int i=0;i<m-1;i++){
            prefix += col[i];
            if(prefix == total - prefix)
                return true;
        }

        return false;
    }
};

















class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long sum[m + 1][n + 1];
        long long total = 0;
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] =
                    sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + grid[i][j];
                total += grid[i][j];
            }
        }
        for (int i = 0; i < m - 1; i++) {
            if (total == sum[i + 1][n] * 2) {
                return true;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            if (total == sum[m][i + 1] * 2) {
                return true;
            }
        }
        return false;
    }
};




















class Solution {
public:
    #define ll long long int
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size(),m = grid[0].size();
        vector<ll> prefRow(n,0),prefCol(m,0);
        ll totalSum = 0;
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++)
            {
                prefRow[i] += grid[i][j];
                prefCol[j] += grid[i][j];
                totalSum += grid[i][j];
            }
        }

        ll sum1 = 0ll;
        for(int i = 0;i < n;i++)
        {
            sum1 += prefRow[i];
            if(sum1 == totalSum - sum1)
            return true;
            if(sum1 > totalSum - sum1)
            break;
        }

        sum1 = 0ll;
        for(int j = 0;j < m;j++)
        {
            sum1 += prefCol[j];
            if(sum1 == totalSum - sum1)
            return true;
            if(sum1 > totalSum - sum1)
            break;
        }

        return false;
    }
};
