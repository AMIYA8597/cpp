// 69. Sqrt(x)



// Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.

// You must not use any built-in exponent function or operator.

// For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
 

// Example 1:

// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
// Example 2:

// Input: x = 8
// Output: 2
// Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.
 

// Constraints:

// 0 <= x <= 231 - 1

















class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x;
        long long low = 1, high = x / 2, ans = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (mid * mid == x) {
                return mid;  
            } else if (mid * mid < x) {
                ans = mid; 
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};



























class Solution {
public:
    long mySqrt(int x) {
    //     if(x==0 || x==1)
    //     return x;
    //     long ans=0,i;
    //     for(i=1;i<=x;i++){
    //         if(i>INT_MAX)
    //         return 0;
    //         // if(i*i>INT_MAX)
    //         // return 0;
    //         else if(i*i>x){
    //             break;
    //         }
    //     }
    //     return (i-1);
    // }
    // if(x<0)
    // return 0;
    // if(x==0 ||x==1)
    // return x;
    // for(int i=1;i<=x;i++){
    //     // int sqr = i*i;
    //     // if(i*i>INT_MAX)
    //     // return 0;
    //     if(i*i>x)
    //     return i-1;
    // }
    // return 0;
    // ---------------------
    // by binary search method
    int start=0,end=x;
    long mid = start+(end-start)/2;
    long square;
    while(start<=end){
        mid = start+(end-start)/2;
        long square = mid*mid;
        if(square==x){
            return mid;
        }else if (square<x){
            start = mid +1;
        }else{
            end = mid-1;
        }
    }
    square=mid*mid;
    if(square<x)
    return mid;
    else
    return mid-1;
    }
};





























class Solution {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) return x;

        int lo = 1;
        int hi = x/2;
        int mid;

        while (lo <= hi) {
            mid = lo + (hi - lo)/2;
            if (mid == x / mid) {
                return mid;
            } else if (mid > x / mid) {
                hi = mid - 1;
            } else { 
                lo = mid + 1;
            }
        }
        return hi;
    }
};



























class Solution {
public:
    int mySqrt(int x) {
        int st = 1 ;
        int end = x ;
        int ans = -1 ; 

        if(x==0 || x <0){
            return 0 ; 
        }
        while(st <= end ){
            int mid = st + (end -st )/2 ;
            if(1LL * mid * mid <=x){

                ans = mid ;
                st = mid + 1 ;
            }else{
                end = mid - 1;
            }
        }
        return ans ; 
    }
};


























class Solution {
public:
    int mySqrt(int x) {
        
        uint32_t curr = 1;

        while (curr * curr <=x)
        {
            curr++;
        }

        return curr - 1;

    }
};