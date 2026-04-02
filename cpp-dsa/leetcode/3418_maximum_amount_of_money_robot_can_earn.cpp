3418. Maximum Amount of Money Robot Can Earn
Medium
Topics
premium lock icon
Companies
Hint
You are given an m x n grid. A robot starts at the top-left corner of the grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1). The robot can move either right or down at any point in time.

The grid contains a value coins[i][j] in each cell:

If coins[i][j] >= 0, the robot gains that many coins.
If coins[i][j] < 0, the robot encounters a robber, and the robber steals the absolute value of coins[i][j] coins.
The robot has a special ability to neutralize robbers in at most 2 cells on its path, preventing them from stealing coins in those cells.

Note: The robot's total coins can be negative.

Return the maximum profit the robot can gain on the route.

 

Example 1:

Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]

Output: 8

Explanation:

An optimal path for maximum coins is:

Start at (0, 0) with 0 coins (total coins = 0).
Move to (0, 1), gaining 1 coin (total coins = 0 + 1 = 1).
Move to (1, 1), where there's a robber stealing 2 coins. The robot uses one neutralization here, avoiding the robbery (total coins = 1).
Move to (1, 2), gaining 3 coins (total coins = 1 + 3 = 4).
Move to (2, 2), gaining 4 coins (total coins = 4 + 4 = 8).
Example 2:

Input: coins = [[10,10,10],[10,10,10]]

Output: 40

Explanation:

An optimal path for maximum coins is:

Start at (0, 0) with 10 coins (total coins = 10).
Move to (0, 1), gaining 10 coins (total coins = 10 + 10 = 20).
Move to (0, 2), gaining another 10 coins (total coins = 20 + 10 = 30).
Move to (1, 2), gaining the final 10 coins (total coins = 30 + 10 = 40).
 

Constraints:

m == coins.length
n == coins[i].length
1 <= m, n <= 500
-1000 <= coins[i][j] <= 1000











































class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();

        const int NEG_INF = INT_MIN / 2;
        vector<vector<array<int,3>>> dp(m, vector<array<int,3>>(n, {NEG_INF, NEG_INF, NEG_INF}));

        dp[0][0][0] = coins[0][0];
        dp[0][0][1] = (coins[0][0] < 0) ? 0 : coins[0][0];
        dp[0][0][2] = (coins[0][0] < 0) ? 0 : coins[0][0];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                
                int c = coins[i][j];
                
                for (int k = 0; k <= 2; k++) {
                    int best_prev = NEG_INF;
                    if (i > 0 && dp[i-1][j][k] != NEG_INF)
                        best_prev = max(best_prev, dp[i-1][j][k]);
                    if (j > 0 && dp[i][j-1][k] != NEG_INF)
                        best_prev = max(best_prev, dp[i][j-1][k]);
                    
                    if (best_prev == NEG_INF) {
                        if (k > 0 && c < 0) {
                            int prev_k1 = NEG_INF;
                            if (i > 0 && dp[i-1][j][k-1] != NEG_INF)
                                prev_k1 = max(prev_k1, dp[i-1][j][k-1]);
                            if (j > 0 && dp[i][j-1][k-1] != NEG_INF)
                                prev_k1 = max(prev_k1, dp[i][j-1][k-1]);
                            if (prev_k1 != NEG_INF)
                                dp[i][j][k] = prev_k1;
                        }
                        continue;
                    }
                    
                    dp[i][j][k] = best_prev + c;
                    
                    if (k > 0 && c < 0) {
                        int prev_k1 = NEG_INF;
                        if (i > 0 && dp[i-1][j][k-1] != NEG_INF)
                            prev_k1 = max(prev_k1, dp[i-1][j][k-1]);
                        if (j > 0 && dp[i][j-1][k-1] != NEG_INF)
                            prev_k1 = max(prev_k1, dp[i][j-1][k-1]);
                        if (prev_k1 != NEG_INF)
                            dp[i][j][k] = max(dp[i][j][k], prev_k1);
                    }
                }
            }
        }
        
        return max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
    }
};




























class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        vector<vector<int>> dfs(vector<vector<int>>(coins[0].size()+1,vector<int>(3,INT_MIN/2)));



        for(int i =0 ;i < coins.size();i++){
            for(int j = 0;j < coins[0].size();j++){
                if(i == 0 && j == 0){
                    dfs[1][0] = coins[i][j];
                    dfs[1][1] = max(coins[i][j],0);
                    dfs[1][2] = max(coins[i][j],0);
                }
                else{
  
                    dfs[j+1][2] = max(coins[i][j] + max(dfs[j+1][2],dfs[j][2]),max(dfs[j+1][1],dfs[j][1]));
                    dfs[j+1][1] = max(coins[i][j] + max(dfs[j+1][1],dfs[j][1]),max(dfs[j+1][0],dfs[j][0]));
                    dfs[j+1][0] = coins[i][j]+max(dfs[j+1][0],dfs[j][0]);
                    
                }
            }
        }
        return max({dfs[coins[0].size()][0],dfs[coins[0].size()][1],dfs[coins[0].size()][2]});


    }
};






























class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        vector f(n + 1, vector<int>(3, INT_MIN));
        for(int k = 0; k < 3; k++){
            f[1][k] = 0;
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int x = coins[i][j];
                f[j + 1][2] = max(max(f[j + 1][2], f[j][2]) + x, max(f[j + 1][1], f[j][1])); // 優化空間後，要記得到序，否則後面的賦值會拿到新的值
                f[j + 1][1] = max(max(f[j + 1][1], f[j][1]) + x, max(f[j + 1][0], f[j][0]));
                f[j + 1][0] = max(f[j + 1][0], f[j][0]) + x;
            }
        }
        return f[n][2];
    }
    // time complexity: O(mn)
    // space complexity: O(n)
};











































class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size();
        int n = coins[0].size();
        vector dp(
            m, vector(n, array<int, 3>{INT_MIN / 2, INT_MIN / 2, INT_MIN / 2}));

        dp[0][0][0] = coins[0][0];
        for (int k = 1; k <= 2; k++) {
            dp[0][0][k] = max(coins[0][0], 0);
        }
        for (int j = 1; j < n; j++) {
            dp[0][j][0] = dp[0][j - 1][0] + coins[0][j];
            for (int k = 1; k <= 2; k++) {
                dp[0][j][k] = max(dp[0][j - 1][k] + coins[0][j],
                                  dp[0][j - 1][k - 1] + max(coins[0][j], 0));
            }
        }
        for (int i = 1; i < m; i++) {
            dp[i][0][0] = dp[i - 1][0][0] + coins[i][0];
            for (int k = 1; k <= 2; k++) {
                dp[i][0][k] = max(dp[i - 1][0][k] + coins[i][0],
                                  dp[i - 1][0][k - 1] + max(coins[i][0], 0));
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j][0] =
                    max(dp[i - 1][j][0], dp[i][j - 1][0]) + coins[i][j];
                for (int k = 1; k <= 2; k++) {
                    dp[i][j][k] =
                        max(max(dp[i - 1][j][k], dp[i][j - 1][k]) + coins[i][j],
                            max(dp[i - 1][j][k - 1], dp[i][j - 1][k - 1]));
                }
            }
        }

        return dp[m - 1][n - 1][2];
    }
};













































class Solution {
public:
	static const int k_minVal = -1000;
	static const int k_empty = std::numeric_limits<int>::min() - k_minVal;

	int mark1( std::vector<std::vector<int>>& coins )
	{
		const auto coinsRowSize = coins.size();
		const auto coinsColumnSize = coins[0].size();

		auto dp = std::vector<std::vector<std::array<int, 3>>>{};
		dp.resize( coinsRowSize + 1 );
		//dp[0].resize( coinsColumnSize + 1 );
		for ( auto rowIndex = 0; rowIndex < dp.size(); ++rowIndex )
		{
			auto& row = dp[rowIndex];
			row.resize( coinsColumnSize + 1 );
			for ( auto columnIndex = 0; columnIndex < row.size(); ++columnIndex )
			{
				row[columnIndex].fill( k_empty );
			}
		}

		dp[0][0].fill( 0 );
		dp[1][0].fill( 0 );
		dp[0][1].fill( 0 );

		const auto dpRowSize = dp.size();
		const auto dpColumnSize = dp[0].size();
		for ( auto rowIndex = 1; rowIndex < dp.size(); ++rowIndex )
		{
			for ( auto columnIndex = 1; columnIndex < dpColumnSize; ++columnIndex )
			{
				auto val = coins[rowIndex - 1][columnIndex - 1];
				dp[rowIndex][columnIndex][0] = std::max( dp[rowIndex][columnIndex - 1][0], dp[rowIndex - 1][columnIndex][0] ) + val;
				if ( val < 0 )
				{
					// disable this robber as the first one ever

					const auto prevColIgnoreThis1 = dp[rowIndex][columnIndex - 1][0];
					const auto prevRowIgnoreThis1 = dp[rowIndex - 1][columnIndex][0];

					const auto prevColUseThis1 = dp[rowIndex][columnIndex - 1][1] + val;
					const auto prevRowUseThis1 = dp[rowIndex - 1][columnIndex][1] + val;

					const auto prevColIgnoreThis2 = dp[rowIndex][columnIndex - 1][1];
					const auto prevRowIgnoreThis2 = dp[rowIndex - 1][columnIndex][1];

					const auto prevColUseThis2 = dp[rowIndex][columnIndex - 1][2] + val;
					const auto prevRowUseThis2 = dp[rowIndex - 1][columnIndex][2] + val;

					dp[rowIndex][columnIndex][1] = std::max( std::max( prevColIgnoreThis1, prevRowIgnoreThis1 ), std::max( prevColUseThis1, prevRowUseThis1 ) );
					dp[rowIndex][columnIndex][2] = std::max( std::max( prevColIgnoreThis2, prevRowIgnoreThis2 ), std::max( prevColUseThis2, prevRowUseThis2 ) );
				}
				else
				{
					dp[rowIndex][columnIndex][1] = std::max( dp[rowIndex][columnIndex - 1][1], dp[rowIndex - 1][columnIndex][1] ) + val;
					dp[rowIndex][columnIndex][2] = std::max( dp[rowIndex][columnIndex - 1][2], dp[rowIndex - 1][columnIndex][2] ) + val;
				}
			}
		}

		return dp[dpRowSize - 1][dpColumnSize - 1][2];
	}

    int maximumAmount(vector<vector<int>>& coins) {
        return mark1( coins );
    }
};









































class Solution {
public:
int maximumAmount(vector<vector<int>>& v) 
{
    int NEG=-1e9, n=v.size(), m=v[0].size();
    int dp[n+1][m+1][3];
    memset(dp, -5e5-2, sizeof(dp));
    for(int t=0;t<=2;t++)
    {
        if(v[n-1][m-1]<0 && t>0) dp[n-1][m-1][t]=0;
        else dp[n-1][m-1][t]=v[n-1][m-1];
    }
    for(int i=n-1 ; i>=0 ; i--)
    {
        for(int j=m-1 ; j>=0 ; j--)
        {
            if(i==n-1 && j==m-1) continue;
            for(int t=0 ; t<=2 ; t++)
            {
                int ans=NEG;
                int nxt=max(dp[i+1][j][t], dp[i][j+1][t]);
                if(nxt!=NEG)
                    ans=max(ans, v[i][j]+nxt);
                if(v[i][j]<0 && t>0)
                    ans=max(ans,
                        max(dp[i+1][j][t-1], 
                        dp[i][j+1][t-1]));
                dp[i][j][t]=ans;
            }
        }
    }
    return dp[0][0][2];
}};
















































class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins[0].size();
        vector dp(n + 1, vector<int>(3, INT_MIN / 2));

        for (int i = 0; i < 3; i++) {
            dp[1][i] = 0;
        }
        for (auto& row : coins) {
            for (int j = 1; j <= n; j++) {
                int x = row[j - 1];
                dp[j][2] = max(
                    {dp[j - 1][2] + x, dp[j][2] + x, dp[j - 1][1], dp[j][1]});
                dp[j][1] = max(
                    {dp[j - 1][1] + x, dp[j][1] + x, dp[j - 1][0], dp[j][0]});
                dp[j][0] = max(dp[j - 1][0], dp[j][0]) + x;
            }
        }

        return dp[n][2];
    }
};





















