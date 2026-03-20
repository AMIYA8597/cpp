3567. Minimum Absolute Difference in Sliding Submatrix



You are given an m x n integer matrix grid and an integer k.

For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.

Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.

Note: If all elements in the submatrix have the same value, the answer will be 0.

A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
 

Example 1:

Input: grid = [[1,8],[3,-2]], k = 2

Output: [[2]]

Explanation:

There is only one possible k x k submatrix: [[1, 8], [3, -2]].
Distinct values in the submatrix are [1, 8, 3, -2].
The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
Example 2:

Input: grid = [[3,-1]], k = 1

Output: [[0,0]]

Explanation:

Both k x k submatrix has only one distinct element.
Thus, the answer is [[0, 0]].
Example 3:

Input: grid = [[1,-2,3],[2,3,5]], k = 2

Output: [[1,2]]

Explanation:

There are two possible k × k submatrix:
Starting at (0, 0): [[1, -2], [2, 3]].
Distinct values in the submatrix are [1, -2, 2, 3].
The minimum absolute difference in the submatrix is |1 - 2| = 1.
Starting at (0, 1): [[-2, 3], [3, 5]].
Distinct values in the submatrix are [-2, 3, 5].
The minimum absolute difference in the submatrix is |3 - 5| = 2.
Thus, the answer is [[1, 2]].
 

Constraints:

1 <= m == grid.length <= 30
1 <= n == grid[i].length <= 30
-105 <= grid[i][j] <= 105
1 <= k <= min(m, n)



























































class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> ans(m - k + 1, vector<int>(n - k + 1, 0));
            for (int i = 0;i<= m-k; i++) {
                for (int j =0;j<=n-k;j++) {
                    vector<int> vals;
                    vals.reserve( k * k);

                    for (int x = i; x < i + k; x++) {
                        for (int y =j; y < j + k; y++) {
                            vals.push_back(grid[x][y]);
                        }
                    }

                    sort(vals.begin(), vals.end());
                    vals.erase(unique(vals.begin(), vals.end()), vals.end());

                    // if (vals.size() <= 1) {
                    //     ans[i][j] = 0;
                    //     continue;
                    // }

                    int minDiff = INT_MAX;
                    for (int t =1; t< vals.size();t++) {
                        minDiff = min(minDiff, vals[t] - vals[t - 1]);
                    }
                    ans[i][j] = (minDiff == INT_MAX ? 0 : minDiff);
                }
            }
            return ans;
        }
};





























class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m-k+1, vector<int>(n-k+1, 0));
        for(int i=0; i<=m-k; i++){
            for(int j=0; j<=n-k; j++){
                vector<int> temp;
                for(int r=i; r<i+k; r++){
                    for(int c=j; c<j+k; c++){
                        temp.push_back(grid[r][c]);
                    }
                }
                sort(temp.begin(), temp.end());
                int diff = INT_MAX;
                for(int x=1; x<temp.size(); x++){
                    if(temp[x] != temp[x-1]) diff = min(diff, abs(temp[x] - temp[x-1]));
                }
                ans[i][j] = (diff == INT_MAX) ? 0 : diff;
            }
        }
        return ans;
    }
};




































class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int v) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>ans(m-v+1, vector<int>(n-v+1, 0));
        for(int i = 0; i<=m-v; i++){
            for(int j = 0; j<=n-v; j++){
                vector<int>temp;
                for(int k = i; k<i+v; k++){
                    for(int l = j; l<j+v; l++){
                        temp.push_back(grid[k][l]);
                    }
                }
                int diff = INT_MAX;
                sort(temp.begin(), temp.end());
                for(int m = 1; m<temp.size(); m++){
                    if(temp[m] != temp[m-1]) diff = min(diff, temp[m]-temp[m-1]);
                }
                ans[i][j] = (diff==INT_MAX)?0:diff;
            }
        }
        return ans;
    }
};

































class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m=grid.size();
        int n=grid[0].size();
        int rows=m-k+1;
        int cols=n-k+1;
        vector<vector<int>>ans(rows,vector<int>(cols,0));
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                vector<int>vals(k*k);
                int ind=0;
                for(int x=i;x<i+k;x++){
                    for(int y=j;y<j+k;y++){
                        vals[ind++]=grid[x][y];
                    }
                }
                sort(vals.begin(),vals.end());
                vector<int>uniq;
                uniq.reserve(k*k);
                uniq.push_back(vals[0]);
                for(int t=1;t<vals.size();t++){
                    if(vals[t]!=vals[t-1]){
                        uniq.push_back(vals[t]);
                    }
                }
                if(uniq.size()<=1){
                    ans[i][j]=0; 
                    continue;
                }
                int mini=INT_MAX;
                for(int t=1;t<uniq.size();t++){
                    int dif=uniq[t]-uniq[t-1];
                    if(dif<mini){
                        mini=dif;
                    }
                    if(mini==0) break;
                }
                ans[i][j]=mini;
            }
        }
        return ans;
    }
};

























class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> ans(m-k+1,vector<int>(n-k+1));

        for(int i=0;i<=m-k;i++){
            for(int j=0;j<=n-k;j++){
                vector<int> temp;

                for(int r = i;r<i+k;r++){
                    for(int c = j;c<j+k;c++){
                        temp.push_back(grid[r][c]);
                    }
                }
                sort(begin(temp),end(temp));
                int diff = INT_MAX;
                for(int x=0;x<temp.size()-1;x++){
                    if(temp[x]!=temp[x+1]){
                        diff = min(diff,abs(temp[x]-temp[x+1]));
                    }
                }
                if(diff==INT_MAX) ans[i][j]=0;
                else ans[i][j]=diff;
            }
        }
        return ans;
    }
};































class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> res(m - k + 1, vector<int>(n - k + 1));
        for (int i = 0; i + k <= m; i++) {
            for (int j = 0; j + k <= n; j++) {
                vector<int> kgrid;
                for (int x = i; x < i + k; x++) {
                    for (int y = j; y < j + k; y++) {
                        kgrid.push_back(grid[x][y]);
                    }
                }
                int kmin = INT_MAX;
                sort(kgrid.begin(), kgrid.end());
                for (int t = 1; t < kgrid.size(); t++) {
                    if (kgrid[t] == kgrid[t - 1]) {
                        continue;
                    }
                    kmin = min(kmin, kgrid[t] - kgrid[t - 1]);
                }
                if (kmin != INT_MAX) {
                    res[i][j] = kmin;
                }
            }
        }
        return res;
    }
};



