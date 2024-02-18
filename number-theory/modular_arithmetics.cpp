#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        x = (x * x) % M;
        n >>= 1;
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
