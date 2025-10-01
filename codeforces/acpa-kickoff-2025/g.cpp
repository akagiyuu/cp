#include<bits/stdc++.h>
const int MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void solve() {
    int n;
    long long x;
    std::cin >> n >> x;
    std::vector<long long> p(13);
    for (int i = 0; i <= 12; ++i) {
        std::cin >> p[i];
    }

    long long inv100 = modInverse(100);

    std::vector<long long> c(13);
    for (int i = 0; i <= 12; ++i) {
        c[i] = (p[i] * inv100) % MOD;
    }

    int k_min = 0;
    while (k_min <= 12 && p[k_min] == 0) {
        k_min++;
    }
    
    if ((long long)n * k_min > x) {
        std::cout << 0 << std::endl;
        return;
    }

    x -= (long long)n * k_min;
    
    std::vector<long long> c_new;
    for (int i = k_min; i <= 12; ++i) {
        c_new.push_back(c[i]);
    }

    int deg = c_new.size() - 1;

    std::vector<long long> q(x + 1);
    
    q[0] = power(c_new[0], n);
    
    if (x == 0) {
        std::cout << q[0] << std::endl;
        return;
    }

    std::vector<long long> inv_m(x + 1);
    inv_m[1] = 1;
    for (int i = 2; i <= x; i++) {
        inv_m[i] = MOD - (MOD / i) * inv_m[MOD % i] % MOD;
    }

    long long inv_c0 = modInverse(c_new[0]);
    long long N = n;

    for (long long m = 1; m <= x; ++m) {
        long long S = 0;
        for (int j = 1; j <= std::min((int)m, deg); ++j) {
            long long term1 = ((N + 1) % MOD * j) % MOD;
            term1 = (term1 - (m % MOD) + MOD) % MOD;
            
            long long term2 = (c_new[j] * q[m - j]) % MOD;
            S = (S + (term1 * term2) % MOD) % MOD;
        }
        
        long long inv_m_val = inv_m[m];
        q[m] = (S * inv_m_val) % MOD;
        q[m] = (q[m] * inv_c0) % MOD;
    }

    std::cout << q[x] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
