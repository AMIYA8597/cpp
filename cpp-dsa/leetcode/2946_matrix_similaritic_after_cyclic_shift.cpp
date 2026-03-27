2946. Matrix Similarity After Cyclic Shifts


You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.

The following proccess happens k times:

Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.


Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.


Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

 

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4

Output: false

Explanation:

In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).



Example 2:

Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2

Output: true

Explanation:



Example 3:

Input: mat = [[2,2],[2,2]], k = 3

Output: true

Explanation:

As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.

 

Constraints:

1 <= mat.length <= 25
1 <= mat[i].length <= 25
1 <= mat[i][j] <= 25
1 <= k <= 50




































  class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();

        k = k % n;

        for (int i =0; i< m; i++) {
            for (int j =0; j< n; j++) {
                int newVal;
                if (i % 2 ==0) {
                    newVal = mat[i][(j + k) %n];
                } else {
                    newVal = mat[i][(j-k+n) % n];
                } if (newVal !=mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};
























class Solution {
public:
    bool is_possible(int k , int n , int m , vector<vector<int>> & mat){
        for(int i=0 ; i<n ; i++){
            vector<int>val(k , 0);
            for(int idx=0 ; idx<k ; idx++){
                val[idx] = mat[i][idx];
            }
            for(int j = k ; j<m ; j++){
                if(mat[i][j] != val[j%k])return false;
            }
        }
        return true;
    }
    int gcd(int a , int b ){
        if(a==0)return b;
        return gcd(b % a , a);
    }
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int n=mat.size() , m=mat[0].size();
        if(k > m) k = k % m;
        if(m == k || k == 0)return true;
        int g_c_d = gcd(k , m);
        if(is_possible(k , n , m , mat) && g_c_d != 1)return true;
        for(int i=0 ; i<n ; i++){
            int ele_to_comp = mat[i][0];
            for(int j=1 ; j<m ; j++){
                if(mat[i][j] != ele_to_comp)return false;
            }
        }
        return true;
    }
};






































class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) 
    {
        int rows=mat.size();
        int cols=mat[0].size();
        vector<vector<int>>original=mat;
        k=k%cols;
        while(k>0)
        {
            for(int i=0;i<mat.size();i++)
            {
                if(i%2==0)
                {
                    int temp=mat[i][0];
                    for(int j=0;j<cols-1;j++)
                    {
                        mat[i][j]=mat[i][j+1];
                    }
                    mat[i][cols-1]=temp;
                }
                if(i%2!=0)
                {
                    int temp=mat[i][cols-1];
                    for(int j=cols-1;j>0;j--)
                    {
                        mat[i][j]=mat[i][j-1];
                    }
                    mat[i][0]=temp;
                }
            }
            k--;
        }
        if(mat==original) return true;

        return false;
    }
};






































class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k %= n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] != mat[i][(j + k) % n]) {
                    return false;
                }
            }
        }
        return true;
    }
};













  
