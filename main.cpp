// Problem 100 - TOmorrow的完美数 (ACMOJ 2791)
// Reads m and m integers; for each, prints 1 if sum of proper divisors equals n (perfect number), else 0.
// Constraints: m <= 10, n <= 1e12. Use efficient divisor summation via prime factorization.

#include <bits/stdc++.h>
using namespace std;

// Compute sum of proper divisors of n (excluding n itself).
// For n > 1, sum of divisors function via prime factorization: 
// If n = p1^a1 * p2^a2 * ..., sigma(n) = prod ((p_i^{a_i+1} - 1)/(p_i - 1)).
// Proper divisors sum = sigma(n) - n.
// For n == 1, proper divisors sum is 0.

static inline bool mul_overflow_u128(__uint128_t a, __uint128_t b, __uint128_t &res) {
    // Multiplication overflow check for __uint128_t not needed here, but keep helper if extended.
    res = a * b;
    return false;
}

// Safely compute p^k using 128-bit intermediate to avoid overflow; return unsigned long long (<= 1e12 range).
static inline unsigned long long pow_u64_u128(unsigned long long p, unsigned long long k) {
    __uint128_t base = p;
    __uint128_t result = 1;
    while (k) {
        if (k & 1) result *= base;
        if (k >>= 1) base *= base;
    }
    return (unsigned long long)result;
}

// Factor using trial division up to cbrt(n) and then handle remaining.
// For n up to 1e12, trial division up to 1e6 is acceptable for m <= 10.
static inline unsigned long long sum_proper_divisors(unsigned long long n) {
    if (n <= 1) return 0ULL;
    unsigned long long original_n = n;
    unsigned long long sum = 1ULL; // product accumulator for sigma(n), start at 1

    // Count factors of 2
    if ((n & 1ULL) == 0ULL) {
        unsigned long long cnt = 0;
        while ((n & 1ULL) == 0ULL) { n >>= 1; ++cnt; }
        // contribution: (2^{cnt+1} - 1)/(2 - 1) = 2^{cnt+1} - 1
        unsigned long long term = (pow_u64_u128(2ULL, cnt + 1) - 1ULL);
        sum *= term;
    }

    // Odd factors
    for (unsigned long long f = 3ULL; f * f <= n; f += 2ULL) {
        if (n % f == 0ULL) {
            unsigned long long cnt = 0ULL;
            while (n % f == 0ULL) { n /= f; ++cnt; }
            // term = (f^{cnt+1} - 1)/(f - 1)
            // compute using geometric series sum safely
            __uint128_t p = f;
            __uint128_t num = 1;
            // fast pow for f^{cnt+1}
            num = 1;
            __uint128_t base = p;
            unsigned long long exp = cnt + 1ULL;
            __uint128_t powv = 1;
            while (exp) {
                if (exp & 1ULL) powv *= base;
                if (exp >>= 1ULL) base *= base;
            }
            num = powv - 1;
            unsigned long long denom = f - 1ULL;
            unsigned long long term = (unsigned long long)(num / denom);
            sum *= term;
        }
    }

    // Remaining prime factor
    if (n > 1ULL) {
        // n is prime
        // contribution: (n^2 - 1)/(n - 1) = n + 1
        sum *= (n + 1ULL);
    }

    // proper divisors sum
    unsigned long long proper = sum - original_n;
    return proper;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;
    vector<unsigned long long> a(m);
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        unsigned long long n = a[i];
        unsigned long long s = sum_proper_divisors(n);
        cout << (s == n ? 1 : 0) << '\n';
    }
    return 0;
}

