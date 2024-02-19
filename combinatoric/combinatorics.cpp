#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
const ll MOD = (ll)1e9 + 7;

/* ============== dependencies ============== */
/*
Problem:
    x^n mod M
Time:
    O(log n)
*/
ll modExp(ll x, ll n, ll M) {
    ll res = 1;
    x %= M;
    while (n > 0) {
        if (n & 1) res = (res * x) % M;
        n >>= 1;
        x = (x * x) % M;
    }
    return res;
}
/*
Problem:
    find modular inverse from x modulo m
    6^-1 mod 17 = 3
    *used when 36/6 mod 17 ==> (36 mod 17) * (6^-1 mod 17) mod 17
Constraints:
    - x and m are coprime
    - m is prime
Time:
    O(log n) --> based on modExp
Usage:
    ll inv = modInv(x, MOD);
*/
ll modInv(ll x, ll M) {
    ll ans = modExp(x, M - 2, M);
    return ans;
}

/* ============== Binomial Coefficients ============== */
/*
Problem:
    generating 0!, 1!, 2!, ..., n! with modulo M and their modular inverse
    facts = [1, 1, 2, 6, 24, 120, ..., n! mod M]
    factsInv = [1^-1 mod M, 1^-1 mod M, 2^-1 mod M, 6^-1 mod M, ..., (n! mod M)^-1 mod M]
Time:
    O(n log n)
Usage:
    > vl facts(n + 1), factsInv(n + 1);
    > genFactsAndFactsInv(n, facts, factsInv);
*/
void genFactsAndFactsInv(int n, vl &facts, vl &factsInv) {
    facts[0] = 1;
    factsInv[0] = modInv(facts[0], MOD);
    for (int i = 1; i <= n; i++) {
        facts[i] = (facts[i - 1] * i) % MOD;
        factsInv[i] = modInv(facts[i], MOD);
    }
}

/* ============== Catalan Number ============== */
/*
Problem:
    calculate number of valid paranthesis expression
    n left parentheses and n right parentheses
    the parenthesis expression have length of 2n
Dependencies:
    - call genFactsAndFactsInv() first with length 2n
Time:
    O(2n) --> precalculating genFactsAndFactsInv()
    O(1) --> calculate Catalan number
Usage:
    > vl facts(2 * n + 1), factsInv(2 * n + 1);
    > genFactsAndFactsInv(2 * n, facts, factsInv);
    > ll ans = catalanNum(n, facts, factsInv);
*/
ll catalanNum(ll n, vl &facts, vl &factsInv) {
    ll x = 2 * n, y = n;
    ll bot = (factsInv[y] * factsInv[x - y]) % MOD;
    ll top = facts[x];
    ll ans = (top * bot) % MOD;
    ans = (ans * modInv(n + 1, MOD)) % MOD;
    return ans;
}

/* ============== Derangements ============== */
/*
Problem:
    calculate number of derangements of element {1, 2, ..., n}
    --> permutations where no element remains in its original palce
    n = 3 --> 2 derangements: (2, 3, 1) and (3, 1, 2)
Time:
    O(n)
*/
ll derangements(ll n) {
    vl dp(n + 1);
    dp[1] = 0;
    dp[2] = 1;
    for (ll i = 3; i <= n; i++) {
        dp[i] = ((i - 1) * ((dp[i - 1] + dp[i - 2]) % MOD)) % MOD;
    }
    return dp[n];
}
