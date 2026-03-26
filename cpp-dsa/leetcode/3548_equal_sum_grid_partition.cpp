//  https://leetcode.com/problems/equal-sum-grid-partition-ii/description/?envType=daily-question&envId=2026-03-26






3548. Equal Sum Grid Partition II




You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:

Each of the two resulting sections formed by the cut is non-empty.
The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total (from either section).
If a cell is discounted, the rest of the section must remain connected.
Return true if such a partition exists; otherwise, return false.

Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.

 

Example 1:

Input: grid = [[1,4],[2,3]]

Output: true

Explanation:



A horizontal cut after the first row gives sums 1 + 4 = 5 and 2 + 3 = 5, which are equal. Thus, the answer is true.
Example 2:

Input: grid = [[1,2],[3,4]]

Output: true

Explanation:



A vertical cut after the first column gives sums 1 + 3 = 4 and 2 + 4 = 6.
By discounting 2 from the right section (6 - 2 = 4), both sections have equal sums and remain connected. Thus, the answer is true.
Example 3:

Input: grid = [[1,2,4],[2,3,5]]

Output: false

Explanation:



A horizontal cut after the first row gives 1 + 2 + 4 = 7 and 2 + 3 + 5 = 10.
By discounting 3 from the bottom section (10 - 3 = 7), both sections have equal sums, but they do not remain connected as it splits the bottom section into two parts ([2] and [5]). Thus, the answer is false.
Example 4:

Input: grid = [[4,1,8],[3,2,6]]

Output: false

Explanation:

No valid cut exists, so the answer is false.

 

Constraints:

1 <= m == grid.length <= 105
1 <= n == grid[i].length <= 105
2 <= m * n <= 105
1 <= grid[i][j] <= 105










































#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        long long total = 0;
        unordered_map<int, int> freq;
        for (auto& row : grid)
            for (int x : row) { total += x; freq[x]++; }

        {
            long long topSum = 0;
            unordered_map<int, int> topFreq;
            unordered_map<int, int> botFreq = freq;

            for (int i = 0; i < m - 1; i++) {
                for (int j = 0; j < n; j++) {
                    int val = grid[i][j];
                    topSum += val;
                    topFreq[val]++;
                    botFreq[val]--;
                }
                long long botSum = total - topSum;
                if (topSum == botSum) return true;

                long long diff = topSum - botSum;
                if (diff > 0) {
                    if (canRemove(grid, 0, i, 0, n-1, diff, topFreq))
                        return true;
                } else {
                    if (canRemove(grid, i+1, m-1, 0, n-1, -diff, botFreq))
                        return true;
                }
            }
        }

        {
            long long leftSum = 0;
            unordered_map<int, int> leftFreq;
            unordered_map<int, int> rightFreq = freq;

            for (int j = 0; j < n - 1; j++) {
                for (int i = 0; i < m; i++) {
                    int val = grid[i][j];
                    leftSum += val;
                    leftFreq[val]++;
                    rightFreq[val]--;
                }
                long long rightSum = total - leftSum;
                if (leftSum == rightSum) return true;

                long long diff = leftSum - rightSum;
                if (diff > 0) {
                    if (canRemove(grid, 0, m-1, 0, j, diff, leftFreq))
                        return true;
                } else {
                    if (canRemove(grid, 0, m-1, j+1, n-1, -diff, rightFreq))
                        return true;
                }
            }
        }

        return false;
    }

private:
    bool canRemove(vector<vector<int>>& grid,
                   int r1, int r2, int c1, int c2,
                   long long val,
                   unordered_map<int,int>& mp) {

        if (val <= 0 || val > 100000) return false;
        int v = (int)val;
        auto it = mp.find(v);
        if (it == mp.end() || it->second <= 0) return false;

        int rows = r2 - r1 + 1;
        int cols = c2 - c1 + 1;

        if (rows == 1 && cols == 1) return false;

        if (rows >= 2 && cols >= 2) return true;

        if (rows == 1) return grid[r1][c1] == v || grid[r1][c2] == v;

        return grid[r1][c1] == v || grid[r2][c1] == v;
    }
};


















#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int exists[100001];
int timer = 0;

static const int __ = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
    bool solve(const vector<vector<int>>& grid, bool horizontal, bool forward) {
        int m = grid.size();
        int n = grid[0].size();
        int R = horizontal ? m : n;
        int C = horizontal ? n : m;

        vector<long long> lineSums(R, 0);
        long long totalSum = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                lineSums[horizontal ? i : j] += grid[i][j];
                totalSum += grid[i][j];
            }
        }

        long long s1 = 0;
        timer++; 

        for (int i = 0; i < R - 1; ++i) {
            int idx = forward ? i : (R - 1 - i);
            s1 += lineSums[idx];
            
            if (horizontal) {
                for (int j = 0; j < n; ++j) exists[grid[idx][j]] = timer;
            } else {
                for (int j = 0; j < m; ++j) exists[grid[j][idx]] = timer;
            }

            long long s2 = totalSum - s1;
            if (s1 == s2) return true;

            if (s1 > s2) {
                long long diff = s1 - s2;
                if (diff <= 100000 && exists[diff] == timer) {
                    // ПРОВЕРКА СВЯЗНОСТИ (Жесткая):
                    int cur_m = horizontal ? (i + 1) : m;
                    int cur_n = horizontal ? n : (i + 1);
                    
                    if (cur_m > 1 && cur_n > 1) {
                        // 2x2 и больше — любая клетка из сета (уже проверено exists) подходит
                        return true;
                    } else {
                        // Полоска: клетка ОБЯЗАНА быть на одном из двух краев секции
                        if (cur_m == 1) { // Горизонтальная полоска
                            // Края секции зависят от направления обхода (forward)
                            int left_col = forward ? 0 : 0; // всегда 0
                            int right_col = forward ? i : (n - 1); // Конец текущей секции
                            // ВНИМАНИЕ: Если горизонтальный разрез при m=1, секция - это кусок строки.
                            // ВЕРТИКАЛЬНЫЙ разрез при m=1: секция это grid[0][start...end]
                            if (horizontal) { // i+1 строк, m > 1. Но cur_m=1 значит m=1 (невозможно по R-1)
                                // Этого случая почти не бывает при R-1, но для порядка:
                                if (grid[idx][0] == diff || grid[idx][n-1] == diff) return true;
                            } else { // Вертикальный разрез, m=1. Секция от 0 до i (или от R-1-i до R-1)
                                int start = forward ? 0 : (n - 1 - i);
                                int end = forward ? i : (n - 1);
                                if (grid[0][start] == diff || grid[0][end] == diff) return true;
                            }
                        } else { // Вертикальная полоска (cur_n == 1)
                            if (horizontal) { // Горизонтальный разрез, n=1.
                                int start = forward ? 0 : (m - 1 - i);
                                int end = forward ? i : (m - 1);
                                if (grid[start][0] == diff || grid[end][0] == diff) return true;
                            } else { // i+1 столбцов, n > 1. cur_n=1 значит n=1.
                                if (grid[0][idx] == diff || grid[m-1][idx] == diff) return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        if (solve(grid, true, true)) return true;
        if (solve(grid, true, false)) return true;
        if (solve(grid, false, true)) return true;
        if (solve(grid, false, false)) return true;
        return false;
    }
};



























using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        const int MAXV = 100000;
        long long totalRowSum = 0LL, totalColSum = 0LL;
        vector<long long> prefixRowWise(n, 0LL), prefixColWise(m, 0LL);

        static int minRow[MAXV + 1], maxRow[MAXV + 1];
        static int minCol[MAXV + 1], maxCol[MAXV + 1];
        fill(minRow, minRow + MAXV + 1, -1);
        fill(maxRow, maxRow + MAXV + 1, -1);
        fill(minCol, minCol + MAXV + 1, -1);
        fill(maxCol, maxCol + MAXV + 1, -1);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int v = grid[i][j];
                long long val = v;
                prefixRowWise[i] += val;
                prefixColWise[j] += val;

                if (minRow[v] == -1) {
                    minRow[v] = maxRow[v] = i;
                    minCol[v] = maxCol[v] = j;
                } else {
                    minRow[v] = min(minRow[v], i);
                    maxRow[v] = max(maxRow[v], i);
                    minCol[v] = min(minCol[v], j);
                    maxCol[v] = max(maxCol[v], j);
                }
            }
        }

        for (auto r : prefixRowWise) totalRowSum += r;
        totalColSum = totalRowSum;

        long long currentRowUpperSum = 0;
        for (int i = 0; i < n - 1; ++i) {
            currentRowUpperSum += prefixRowWise[i];
            long long lowerSegmentSum = totalRowSum - currentRowUpperSum;
            if (currentRowUpperSum == lowerSegmentSum) return true;
            if (currentRowUpperSum > lowerSegmentSum) {
                long long diff = currentRowUpperSum - lowerSegmentSum;
                if (diff <= MAXV && minRow[diff] != -1) {
                    if (i == 0 || m == 1) {
                        if (diff == grid[0][0] || diff == grid[0][m - 1] || diff == grid[i][0]) return true;
                    } else if (minRow[diff] <= i) {
                        return true;
                    }
                }
            } else {
                long long diff = lowerSegmentSum - currentRowUpperSum;
                if (diff <= MAXV && maxRow[diff] != -1) {
                    if (i == n - 2 || m == 1) {
                        if (diff == grid[i + 1][0] || diff == grid[i + 1][m - 1] || diff == grid[n - 1][0]) return true;
                    } else if (maxRow[diff] > i) {
                        return true;
                    }
                }
            }
        }

        long long currentColLeftSum = 0;
        for (int j = 0; j < m - 1; ++j) {
            currentColLeftSum += prefixColWise[j];
            long long rightSegmentSum = totalColSum - currentColLeftSum;
            if (currentColLeftSum == rightSegmentSum) return true;
            if (currentColLeftSum > rightSegmentSum) {
                long long diff = currentColLeftSum - rightSegmentSum;
                if (diff <= MAXV && minCol[diff] != -1) {
                    if (j == 0 || n == 1) {
                        if (diff == grid[0][0] || diff == grid[n - 1][0] || diff == grid[0][j]) return true;
                    } else if (minCol[diff] <= j) {
                        return true;
                    }
                }
            } else {
                long long diff = rightSegmentSum - currentColLeftSum;
                if (diff <= MAXV && maxCol[diff] != -1) {
                    if (j == m - 2 || n == 1) {
                        if (diff == grid[0][j + 1] || diff == grid[n - 1][j + 1] || diff == grid[0][m - 1]) return true;
                    } else if (maxCol[diff] > j) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
} fastio;



































using namespace std;

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        const int MAXV = 100000;
        long long totalRowSum = 0LL, totalColSum = 0LL;
        vector<long long> prefixRowWise(n, 0LL), prefixColWise(m, 0LL);

        static int minRow[MAXV + 1], maxRow[MAXV + 1];
        static int minCol[MAXV + 1], maxCol[MAXV + 1];
        fill(minRow, minRow + MAXV + 1, -1);
        fill(maxRow, maxRow + MAXV + 1, -1);
        fill(minCol, minCol + MAXV + 1, -1);
        fill(maxCol, maxCol + MAXV + 1, -1);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int v = grid[i][j];
                long long val = v;
                prefixRowWise[i] += val;
                prefixColWise[j] += val;

                if (minRow[v] == -1) {
                    minRow[v] = maxRow[v] = i;
                    minCol[v] = maxCol[v] = j;
                } else {
                    minRow[v] = min(minRow[v], i);
                    maxRow[v] = max(maxRow[v], i);
                    minCol[v] = min(minCol[v], j);
                    maxCol[v] = max(maxCol[v], j);
                }
            }
        }

        for (auto r : prefixRowWise) totalRowSum += r;
        totalColSum = totalRowSum;

        long long currentRowUpperSum = 0;
        for (int i = 0; i < n - 1; ++i) {
            currentRowUpperSum += prefixRowWise[i];
            long long lowerSegmentSum = totalRowSum - currentRowUpperSum;
            if (currentRowUpperSum == lowerSegmentSum) return true;
            if (currentRowUpperSum > lowerSegmentSum) {
                long long diff = currentRowUpperSum - lowerSegmentSum;
                if (diff <= MAXV && minRow[diff] != -1) {
                    if (i == 0 || m == 1) {
                        if (diff == grid[0][0] || diff == grid[0][m - 1] || diff == grid[i][0]) return true;
                    } else if (minRow[diff] <= i) {
                        return true;
                    }
                }
            } else {
                long long diff = lowerSegmentSum - currentRowUpperSum;
                if (diff <= MAXV && maxRow[diff] != -1) {
                    if (i == n - 2 || m == 1) {
                        if (diff == grid[i + 1][0] || diff == grid[i + 1][m - 1] || diff == grid[n - 1][0]) return true;
                    } else if (maxRow[diff] > i) {
                        return true;
                    }
                }
            }
        }

        long long currentColLeftSum = 0;
        for (int j = 0; j < m - 1; ++j) {
            currentColLeftSum += prefixColWise[j];
            long long rightSegmentSum = totalColSum - currentColLeftSum;
            if (currentColLeftSum == rightSegmentSum) return true;
            if (currentColLeftSum > rightSegmentSum) {
                long long diff = currentColLeftSum - rightSegmentSum;
                if (diff <= MAXV && minCol[diff] != -1) {
                    if (j == 0 || n == 1) {
                        if (diff == grid[0][0] || diff == grid[n - 1][0] || diff == grid[0][j]) return true;
                    } else if (minCol[diff] <= j) {
                        return true;
                    }
                }
            } else {
                long long diff = rightSegmentSum - currentColLeftSum;
                if (diff <= MAXV && maxCol[diff] != -1) {
                    if (j == m - 2 || n == 1) {
                        if (diff == grid[0][j + 1] || diff == grid[n - 1][j + 1] || diff == grid[0][m - 1]) return true;
                    } else if (maxCol[diff] > j) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
} fastio;


































class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        const int MAXV = 100000;
        long long totalRowSum = 0LL, totalColSum = 0LL;
        vector<long long> prefixRowWise(n, 0LL), prefixColWise(m, 0LL);

        static int minRow[MAXV + 1], maxRow[MAXV + 1];
        static int minCol[MAXV + 1], maxCol[MAXV + 1];
        fill(minRow, minRow + MAXV + 1, -1);
        fill(maxRow, maxRow + MAXV + 1, -1);
        fill(minCol, minCol + MAXV + 1, -1);
        fill(maxCol, maxCol + MAXV + 1, -1);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int v = grid[i][j];
                long long val = v;
                prefixRowWise[i] += val;
                prefixColWise[j] += val;

                if (minRow[v] == -1) {
                    minRow[v] = maxRow[v] = i;
                    minCol[v] = maxCol[v] = j;
                } else {
                    minRow[v] = min(minRow[v], i);
                    maxRow[v] = max(maxRow[v], i);
                    minCol[v] = min(minCol[v], j);
                    maxCol[v] = max(maxCol[v], j);
                }
            }
        }

        for (auto r : prefixRowWise) totalRowSum += r;
        totalColSum = totalRowSum;

        long long currentRowUpperSum = 0;
        for (int i = 0; i < n - 1; ++i) {
            currentRowUpperSum += prefixRowWise[i];
            long long lowerSegmentSum = totalRowSum - currentRowUpperSum;
            if (currentRowUpperSum == lowerSegmentSum) return true;
            if (currentRowUpperSum > lowerSegmentSum) {
                long long diff = currentRowUpperSum - lowerSegmentSum;
                if (diff <= MAXV && minRow[diff] != -1) {
                    if (i == 0 || m == 1) {
                        if (diff == grid[0][0] || diff == grid[0][m - 1] || diff == grid[i][0]) return true;
                    } else if (minRow[diff] <= i) {
                        return true;
                    }
                }
            } else {
                long long diff = lowerSegmentSum - currentRowUpperSum;
                if (diff <= MAXV && maxRow[diff] != -1) {
                    if (i == n - 2 || m == 1) {
                        if (diff == grid[i + 1][0] || diff == grid[i + 1][m - 1] || diff == grid[n - 1][0]) return true;
                    } else if (maxRow[diff] > i) {
                        return true;
                    }
                }
            }
        }

        long long currentColLeftSum = 0;
        for (int j = 0; j < m - 1; ++j) {
            currentColLeftSum += prefixColWise[j];
            long long rightSegmentSum = totalColSum - currentColLeftSum;
            if (currentColLeftSum == rightSegmentSum) return true;
            if (currentColLeftSum > rightSegmentSum) {
                long long diff = currentColLeftSum - rightSegmentSum;
                if (diff <= MAXV && minCol[diff] != -1) {
                    if (j == 0 || n == 1) {
                        if (diff == grid[0][0] || diff == grid[n - 1][0] || diff == grid[0][j]) return true;
                    } else if (minCol[diff] <= j) {
                        return true;
                    }
                }
            } else {
                long long diff = rightSegmentSum - currentColLeftSum;
                if (diff <= MAXV && maxCol[diff] != -1) {
                    if (j == m - 2 || n == 1) {
                        if (diff == grid[0][j + 1] || diff == grid[n - 1][j + 1] || diff == grid[0][m - 1]) return true;
                    } else if (maxCol[diff] > j) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};



















