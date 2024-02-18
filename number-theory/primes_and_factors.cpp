#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
Problem:
    all pair factors from n
    84 = [{1, 84}, {2, 42}, {3, 28}, {4, 21}, {6, 14}, {7, 12}]
    9 = [{1, 9}, {3, 3}]
Time:
    O(sqrt(n))
Usage:
    n = number to find all pair factors
    > vector<pii> v;
    > pairFactors(n, v);
*/
void pairFactors(int n, vector<pii> &v) {
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            pii elm = n / i == i ? make_pair(i, i) : make_pair(i, n / i);
            v.push_back(elm);
        }
    }
}

/*
Problem:
    prime factorization from n
    84 = 2^2 . 3^1 . 7^1
    9 = 3^2
Time:
    O(sqrt(n))
Usage:
    n = number to find prime factorization
    > map<ll, ll> mp;
    > primeFactors(n, mp);
*/
void primeFactors(ll n, map<ll, ll> &mp) {
    while (n % 2 == 0) {
        if (mp.find(2) == mp.end()) {
            mp.insert({2, 1});
        } else {
            mp.at(2)++;
        }
        n /= 2;
    }
    for (ll i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            if (mp.find(i) == mp.end()) {
                mp.insert({i, 1});
            } else {
                mp.at(i)++;
            }
            n /= i;
        }
    }
    if (n > 2) {
        mp.insert({n, 1});
    }
}

/*
Problem:
    amount of factors of n
    84 = 12
    9 = 3
Time:
    O(sqrt(n)) --> from primeFactors() function
*/
ll numberOfFactors(int n) {
    map<ll, ll> mp;
    primeFactors(n, mp);
    ll numFactors = 1;
    for (auto it : mp) {
        numFactors *= (it.second + 1);
    }
    return numFactors;
}

/*
Problem:
    n is prime or not
Time:
    O(sqrt(n))
*/
bool isPrime(int n) {
    if (n == 2) {
        return true;
    }
    if ((n <= 1) || (n % 2 == 0)) {
        return false;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/*
Problem:
    build array is prime for number 2...n
Time:
    O(n)
Usage:
    > vi sieve(n + 1, 0);
    > sieveOfEratosthenes(n, sieve);
    sieve[k] = 0 --> k is prime
    sieve[k] != 0 --> k is not prime, one of prime factors is sieve[k]
*/
void sieveOfEratosthenes(int n, vi &sieve) {
    for (int i = 2; i <= n; i++) {
        if (sieve[i] == 0) {
            for (int j = 2 * i; j <= n; j += i) {
                sieve[j] = i;
            }
        }
    }
}

/*
Problem:
    gcd 8 and 6 = 2
Time:
    O(log (min(a, b)))
*/
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

/*
Problem:
    lcm 8 and 6 = 24
Time:
    O(log (min(a, b)))
*/
ll lcm(ll a, ll b) {
    return (a * b) / gcd(a, b);
}

/*
Problem:
    find Bézout's coefficient x y, from a b
    where gcd(a, b) = a.x + b.y
Time:
    O(log (min(a, b)))
Usage:
    > ll x = 1, y = 0;
    > ll gcd = extendedEuclid(a, b, x, y);
Notes:
    - gives pair x y that |X| + |Y| minimal and X <= Y
*/
ll extendedEuclid(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extendedEuclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
