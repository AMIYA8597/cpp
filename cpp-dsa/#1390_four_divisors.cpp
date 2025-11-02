// 1390. Four Divisors


// Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.

 

// Example 1:

// Input: nums = [21,4,7]
// Output: 32
// Explanation: 
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.
// Example 2:

// Input: nums = [21,21]
// Output: 64
// Example 3:

// Input: nums = [1,2,3,4,5]
// Output: 0
 

// Constraints:

// 1 <= nums.length <= 104
// 1 <= nums[i] <= 105

























class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        const int MAX = 100000;
        vector<bool> isPrime(MAX + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i <= MAX; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= MAX; j += i)
                    isPrime[j] = false;
            }
        }

        long long totalSum = 0;

        for (int num : nums) {
            if (num < 6) continue;

            int p = round(cbrt(num));
            while (1LL * p * p * p < num) p++;
            while (1LL * p * p * p > num) p--;
            if (1LL * p * p * p == num && isPrime[p]) {
                totalSum += (1LL + p + 1LL * p * p + 1LL * p * p * p);
                continue;
            }

            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) {
                    int q = num / i;
                    if (q != i && q <= MAX && isPrime[i] && isPrime[q]) {
                        totalSum += (1LL + i + q + num);
                    }
                    break;
                }
            }
        }

        return (int)totalSum;
    }
    // }
};


























class Solution {
public:
    bool isFour(int n) {
        int res = 0;
        int bound = floor(sqrt(n));
        for(int i = 1; i <= bound;i++){
            if(n%i == 0) {
                res++;
                if(n/i != i) res++;
            }
            
        }
        return res == 4;
    }
    int sum(int n) {
        int res = 0;
        int bound = floor(sqrt(n));
        for(int i = 1; i <= bound;i++){
            if(n%i == 0) {
                res+=i;
                if(n/i != i) res+=n/i;
            }
            
        }
        return res;
    }
    int sumFourDivisors(vector<int>& nums) {
        int res = 0;

        for(int n : nums){
            if(isFour(n)){
                res += sum(n);
            }
        }

        return res;
    } 
};

















class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int sum = 0;
        for(int n : nums){
            int prev_d = 0;
            for(int i = 2; i * i <= n; i++){
                if(n % i == 0 && prev_d == 0){
                    prev_d = i;
                    printf("n %d, prevd %d\n", n, i);
                } else if(n % i == 0) {
                    prev_d = 0;
                    break;
                }
            }
            if(prev_d > 0 && prev_d == n / prev_d) continue;
            if(prev_d > 0){ 
                printf("successful n: %d\n", n);
                sum += 1 + n + prev_d + n/prev_d;
            }
        }

        return sum;
    }
};

























class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        vector<vector<int>> v;
        int totalsum=0;
        for(int i=0;i<nums.size();i++)
        {
          vector<int> div;
          int sum=0;
          for(int j=1;j*j<=nums[i];j++)
          {
              if(nums[i]%j == 0)
              {
                int k = nums[i]/j;
                div.push_back(j);
                if(k!=j)
                {
                   div.push_back(k);
                sum+=(k+j);
                }
               
              }
             
          }
           if(div.size()==4)
           {
            totalsum+=sum;
           }
        }
        return totalsum;
    }
};