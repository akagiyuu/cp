#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

// ---------------------- math utils ----------------------
i64 mulmod(i64 a, i64 b, i64 m) { return (i64)((i128)a * b % m); }

i64 powmod(i64 a, i64 e, i64 m) {
    a %= m; if (a < 0) a += m;
    i64 r = 1 % m;
    while (e > 0) {
        if (e & 1) r = mulmod(r, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return r;
}

// extended gcd: returns g = gcd(a,b) and sets x,y with ax+by=g
i64 ext_gcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) { x = (a >= 0 ? 1 : -1); y = 0; return llabs(a); }
    i64 x1, y1;
    i64 g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

i64 inv_mod(i64 a, i64 m) {
    i64 x, y;
    i64 g = ext_gcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m; if (x < 0) x += m;
    return x;
}

// ---------------------- BSGS discrete log ----------------------
// Finds minimal x >= 0 with base^x ≡ target (mod mod), searching in subgroup of size 'order'.
// Returns -1 if no solution found.
i64 discrete_log(i64 base, i64 target, i64 mod, i64 order) {
    base %= mod; target %= mod;
    if (mod == 1) return 0;
    if (target == 1) return 0;
    i64 m = (i64)ceil(sqrt((long double)order));
    unordered_map<i64, i64> tbl; tbl.reserve(m * 2);

    i64 cur = 1 % mod;
    for (i64 j = 0; j < m; ++j) {
        if (!tbl.count(cur)) tbl[cur] = j;
        cur = mulmod(cur, base, mod);
    }

    i64 factor = powmod(base, m, mod);
    i64 factor_inv = inv_mod(factor, mod);
    if (factor_inv == -1) return -1; // should not happen if base coprime to mod

    cur = target % mod;
    for (i64 i = 0; i <= m; ++i) {
        auto it = tbl.find(cur);
        if (it != tbl.end()) return i * m + it->second;
        cur = mulmod(cur, factor_inv, mod);
    }
    return -1;
}

// ---------------------- factorization (trial) ----------------------
vector<pair<i64,int>> factorize(i64 n) {
    vector<pair<i64,int>> res;
    for (i64 p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) { n /= p; ++cnt; }
            res.emplace_back(p, cnt);
        }
    }
    if (n > 1) res.emplace_back(n, 1);
    return res;
}

// ---------------------- primitive root for p^e (odd p) ----------------------
i64 primitive_root_prime_power(i64 p, int e) {
    if (p == 2) {
        if (e == 1) return 1;
        if (e == 2) return 3;
        return 5;
    }
    i64 mod = 1;
    for (int i = 0; i < e; ++i) mod *= p;
    i64 phi = mod / p * (p-1);

    vector<i64> pf;
    i64 tmp = phi;
    for (i64 q = 2; q * q <= tmp; ++q) {
        if (tmp % q == 0) {
            pf.push_back(q);
            while (tmp % q == 0) tmp /= q;
        }
    }
    if (tmp > 1) pf.push_back(tmp);

    for (i64 g = 2; ; ++g) {
        if (std::gcd((i64)g, p) != 1) continue;
        bool ok = true;
        for (i64 q : pf) {
            if (powmod(g, phi / q, mod) == 1) { ok = false; break; }
        }
        if (ok) return g;
    }
}

// ---------------------- linear congruence solver ----------------------
// Solve k * x ≡ b (mod m). Returns all solutions modulo m (distinct)
vector<i64> solve_linear_congruence(i64 k, i64 b, i64 m) {
    i64 x, y;
    i64 g = ext_gcd(k, m, x, y);
    if (b % g != 0) return {};
    i64 m0 = m / g;
    i128 x0big = (i128)x * (b / g);
    i64 x0 = (i64)(x0big % m);
    if (x0 < 0) x0 += m;
    vector<i64> res;
    for (int i = 0; i < g; ++i) res.push_back((x0 + (i128)i * m0) % m);
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

// ---------------------- solve x^k ≡ a (mod p^e) ----------------------
vector<i64> solve_prime_power(i64 a, i64 k, i64 p, int e) {
    i64 mod = 1;
    for (int i = 0; i < e; ++i) mod *= p;
    a %= mod; if (a < 0) a += mod;
    if (mod == 1) return {0};

    // trivial a == 0 case
    if (a == 0) {
        int need = (e + (int)k - 1) / (int)k;
        i64 base = 1;
        for (int i = 0; i < need; ++i) base *= p;
        i64 cnt = 1;
        for (int i = 0; i < e - need; ++i) cnt *= p;
        vector<i64> res; res.reserve(cnt);
        for (i64 t = 0; t < cnt; ++t) res.push_back(mulmod(t, base, mod));
        sort(res.begin(), res.end()); res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }

    if (p == 2) {
        // brute force for small e
        if (e <= 20) {
            vector<i64> res;
            for (i64 x = 0; x < mod; ++x) if (powmod(x, k, mod) == a) res.push_back(x);
            sort(res.begin(), res.end()); res.erase(unique(res.begin(), res.end()), res.end());
            return res;
        }
        // For larger powers of two, more work required (not implemented here).
        return {};
    }

    // odd p: multiplicative group mod p^e is cyclic of order phi = p^{e-1}*(p-1)
    i64 phi = 1;
    for (int i = 0; i < e - 1; ++i) phi *= p;
    phi *= (p - 1);

    i64 g = primitive_root_prime_power(p, e);
    i64 y = discrete_log(g, a, mod, phi);
    if (y == -1) return {};

    auto sols_t = solve_linear_congruence(k, y, phi);
    vector<i64> res;
    res.reserve(sols_t.size());
    for (i64 t : sols_t) res.push_back(powmod(g, t, mod));
    sort(res.begin(), res.end()); res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

// ---------------------- CRT pairwise combine ----------------------
// find x ≡ r1 (mod m1), x ≡ r2 (mod m2)
// returns (x mod lcm, lcm) or (0,-1) if inconsistent
pair<i64,i64> crt_pair(i64 r1, i64 m1, i64 r2, i64 m2) {
    i64 s, t;
    i64 g = ext_gcd(m1, m2, s, t);
    if ((r2 - r1) % g != 0) return {0, -1};
    i64 l = m1 / g * m2;
    i128 mul = (i128)(r2 - r1) / g * s;
    i64 tmp = (i64)(mul % (m2 / g));
    i128 x = (i128)r1 + (i128)m1 * tmp;
    i64 ans = (i64)(x % l); if (ans < 0) ans += l;
    return {ans, l};
}

// combine arbitrary congruences incrementally (handles non-coprime)
pair<i64,i64> combine_crt(const vector<pair<i64,i64>>& congruences) {
    i64 r = 0, m = 1;
    for (auto &c : congruences) {
        auto pr = crt_pair(r, m, c.first % c.second, c.second);
        if (pr.second == -1) return {0, -1};
        r = pr.first; m = pr.second;
    }
    return {r % m, m};
}

// ---------------------- discrete root modulo composite n ----------------------
vector<i64> discrete_root_composite(i64 a, i64 k, i64 n) {
    if (n == 1) return {0};
    auto fac = factorize(n);
    vector<vector<i64>> all_sols;
    vector<i64> mods;
    for (auto &pe : fac) {
        i64 p = pe.first; int e = pe.second;
        i64 mod = 1; for (int i = 0; i < e; ++i) mod *= p;
        auto sols = solve_prime_power(a, k, p, e);
        if (sols.empty()) return {};
        all_sols.push_back(move(sols));
        mods.push_back(mod);
    }

    // Cartesian product + CRT combine
    vector<pair<i64,i64>> cur; // (res, mod)
    cur.emplace_back(0, 1);
    for (size_t i = 0; i < all_sols.size(); ++i) {
        vector<pair<i64,i64>> next;
        next.reserve(cur.size() * all_sols[i].size());
        for (auto &base : cur) {
            for (i64 r : all_sols[i]) {
                auto pr = crt_pair(base.first, base.second, r, mods[i]);
                if (pr.second != -1) next.push_back(pr);
            }
        }
        cur.swap(next);
        if (cur.empty()) return {};
    }
    vector<i64> ans;
    for (auto &p : cur) ans.push_back(p.first % n);
    sort(ans.begin(), ans.end()); ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}

// ---------------------- main / problem-specific logic ----------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        // Original format: read 3 moduli, then 3 remainders
        vector<i64> m(3), a(3);
        for (int i = 0; i < 3; ++i) cin >> m[i];
        for (int i = 0; i < 3; ++i) cin >> a[i];

        vector<pair<i64,i64>> congr;
        congr.reserve(3);
        for (int i = 0; i < 3; ++i) congr.emplace_back(a[i] % m[i], m[i]);

        auto pr = combine_crt(congr);
        if (pr.second == -1) { // inconsistent CRT
            cout << -1 << '\n';
            continue;
        }
        i64 R = pr.first; i64 M = pr.second;

        auto roots = discrete_root_composite(R, 3, M); // original used k=3
        if (roots.empty()) {
            cout << -1 << '\n';
        } else {
            // print smallest non-negative solution (you can change to print all)
            cout << roots[0] << '\n';
        }
    }
    return 0;
}
