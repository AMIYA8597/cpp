// E. Townhall Wizard Squads
// time limit per test2 seconds
// memory limit per test512 megabytes
// The chief of a mighty Townhall is preparing a squad of wizards for the next raid. Each wizard has a power level from 0
//  to N−1
// . The wizards must be arranged in non-decreasing order of power in the Townhall barracks.

// For example, for N=3
// , the arrangement [0,1,2]
//  is allowed, but [2,0,1]
//  is not allowed.

// The chief wonders: how many different ways can he arrange his wizard squad? Since the number can be very large, output the answer modulo 998244353
// .

// Input
// The first line contains an integer T
//  (1≤T≤1000)
//  — the number of raids.

// Each of the next T
//  lines contains a single integer N
//  (1≤N≤2⋅105)
//  — the number of wizards in the squad for that raid.

// It is guaranteed that the sum of N
//  over all test cases does not exceed 2⋅105
// .

// Output
// For each test case, output a single integer — the number of valid wizard arrangements modulo 998244353
// .

// Example
// InputCopy
// 4
// 1
// 2
// 3
// 10000
// OutputCopy
// 1
// 3
// 10
// 658363258
// Note
// For N=1
// , the only valid arrangement is [0]
// .

// For N=2
// , valid arrangements are [0,0]
// , [0,1]
// , [1,1]
// .

// For N=3
// , valid arrangements are [0,0,0]
// , [0,0,1]
// , [0,0,2]
// , [0,1,1]
// , [0,1,2]
// , [0,2,2]
// , [1,1,1]
// , [1,1,2]
// , [1,2,2]
// , [2,2,2]
// .




























#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 400000; // since we need up to 2N-1 for N ≤ 2e5

long long fact[MAXN + 1], invfact[MAXN + 1];

// Fast modular exponentiation
long long modpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invfact[MAXN] = modpow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; i--)
        invfact[i - 1] = invfact[i] * i % MOD;
}

// nCr mod MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << nCr(2 * N - 1, N) << "\n";
    }
    return 0;
}
