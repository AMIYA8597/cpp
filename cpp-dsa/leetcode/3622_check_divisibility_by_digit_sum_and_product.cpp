3622. Check Divisibility by Digit Sum and Product
Easy
Topics
premium lock icon
Companies
Hint
You are given a positive integer n. Determine whether n is divisible by the sum of the following two values:

The digit sum of n (the sum of its digits).

The digit product of n (the product of its digits).

Return true if n is divisible by this sum; otherwise, return false.

 

Example 1:

Input: n = 99

Output: true

Explanation:

Since 99 is divisible by the sum (9 + 9 = 18) plus product (9 * 9 = 81) of its digits (total 99), the output is true.

Example 2:

Input: n = 23

Output: false

Explanation:

Since 23 is not divisible by the sum (2 + 3 = 5) plus product (2 * 3 = 6) of its digits (total 11), the output is false.

 

Constraints:

1 <= n <= 106
















































class Solution {
public:
    bool checkDivisibility(int n) {
        int x = n;
        int digitSum = 0;
        int digitProduct = 1;

        while (x > 0) {
            int digit = x % 10;

            digitSum += digit;
            digitProduct *= digit;

            x /= 10;
        }

        return n % (digitSum + digitProduct) == 0;
    }
};

















class Solution {
public:
    bool checkDivisibility(int n) {
        int v = n;
        int digit_s = 0;
        int digit_p = 1;
        int digit;
        while(v) {
            digit = v % 10;
            digit_s += digit;
            digit_p *= digit;
            v /= 10;
        }
        cout << digit_s << "+" << digit_p << "\n";
        return n % (digit_s + digit_p) == 0;
    }
};























class Solution {
public:
    bool checkDivisibility(int n) {
        long long sum = 0;
        long long pro = 1;
        int num = n;
        while(num>0){
            int digit = num%10;
            num=num/10;
            sum+=digit;
            pro*= digit;
            
        }
        cout<<sum<<" "<<pro;
        return (n%(sum+pro))==0?true:false;
    }
};




























class Solution {
public:
    bool checkDivisibility(int n) {
        int sum = 0;
        int prod = 1;
        int og = n;
        while(n>0){
            int rem = n%10;
            sum+=rem;
            prod*=rem;
            n/=10;
        }
        if(og%(sum+prod)==0) return true;
        return false;
    }
};
















class Solution {
public:
    bool checkDivisibility(int n) {
        int sum=0, prod=1;
        int temp=n;
        while(n != 0){
            int k = n % 10;
            sum+=k;
            prod*=k;
            n/=10; 
        }
        
        cout<<sum<<endl;
        cout<<prod<<endl;

        int res= sum+prod;

        if(temp % res ==0) return true;

        else return false;

        return true;
    }
};
