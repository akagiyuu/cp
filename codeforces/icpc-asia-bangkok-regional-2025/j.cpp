#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using ld  = long double;

struct TaylorApproximator {
    int degree;                          // number of terms M (use e.g. 10)
    vector<ld> centers;                  // T[k] (each in [0,1] typically)
    vector<vector<ld>> poly;             // poly[k][j] = coefficient for (u^j) at center k
    vector<vector<ld>> prefix;           // prefix[p][i] = sum_{0..i} a[i]^p
    vector<vector<ld>> C;                // binomial coefficients up to degree

    // constructor - centers size = K
    TaylorApproximator(int degree_, const vector<ld>& centers_)
        : degree(degree_), centers(centers_)
    {
        int K = centers.size();
        poly.assign(K, vector<ld>(degree, 0.0L));
        build_nck();
    }

    // Build binomial table C up to degree-1
    void build_nck()
    {
        C.assign(degree, vector<ld>(degree, 0.0L));
        for (int i = 0; i < degree; ++i) {
            C[i][0] = 1.0L;
            for (int j = 1; j <= i; ++j)
                C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }

    // Example builder for sqrt(1 + (T + u)) expansion used in your original solution.
    // It sets poly[k][j] consistent with your recurrence.
    void build_taylor_sqrt()
    {
        for (size_t k = 0; k < centers.size(); ++k) {
            ld T = centers[k];
            poly[k][0] = powl(1.0L + T, 0.5L);
            for (int j = 1; j < degree; ++j) {
                // derived recurrence for binomial coefficients from (1+x)^{1/2}
                ld binom_diff = (3.0L - 2.0L * (ld)j) / (2.0L * (ld)j);
                poly[k][j] = binom_diff * poly[k][j-1] / (1.0L + T);
            }
        }
    }

    // Generic: allow user to provide a builder lambda:
    //   builder(k, degree, poly_row, centers[k])
    void build_generic(const function<void(int,int,vector<ld>&,ld)>& builder)
    {
        for (size_t k = 0; k < centers.size(); ++k) {
            builder((int)k, degree, poly[k], centers[k]);
        }
    }

    // Build prefix sums of powers for input array a (size n).
    // prefix[p][i] = sum_{j=0..i} a[j]^p  for p = 0..degree-1
    void build_prefix(const vector<ld>& a)
    {
        int n = (int)a.size();
        prefix.assign(degree, vector<ld>(n, 0.0L));
        for (int j = 0; j < n; ++j) {
            // p=0
            prefix[0][j] = (j == 0 ? 1.0L : prefix[0][j-1] + 1.0L);
            // compute powers iteratively to avoid pow()
            ld cur = a[j];
            for (int p = 1; p < degree; ++p) {
                if (j == 0) prefix[p][0] = cur;
                else prefix[p][j] = prefix[p][j-1] + cur;
                cur *= a[j];
            }
        }
    }

    // helper: sum_range(l..r) of power pw
    inline ld sum_range(int l, int r, int pw) const
    {
        if (l > r) return 0.0L;
        if (l == 0) return prefix[pw][r];
        return prefix[pw][r] - prefix[pw][l-1];
    }

    // Core: compute contribution for indices j in [l..r] using expansion around center index `center_idx`.
    // ai is the denominator a[i], t = centers[center_idx].
    ld calc_segment(int l, int r, ld ai, int center_idx) const
    {
        if (l > r) return 0.0L;
        const vector<ld>& P = poly[center_idx];

        // precompute inv_ai^j iteratively to avoid pow in inner loop
        ld inv_ai = 1.0L / ai;
        vector<ld> inv_pow(degree);
        inv_pow[0] = 1.0L;
        for (int j = 1; j < degree; ++j) inv_pow[j] = inv_pow[j-1] * inv_ai;

        ld t = centers[center_idx];
        // We'll need powers of (-t)^{i-j}. Precompute pow_neg_t[k] = (-t)^k
        vector<ld> pow_neg_t(degree);
        pow_neg_t[0] = 1.0L;
        for (int k = 1; k < degree; ++k) pow_neg_t[k] = pow_neg_t[k-1] * (-t);

        ld res = 0.0L;
        for (int i = 0; i < degree; ++i) {
            // inner sum over j = 0..i: poly[i] * C[i][j] * (-t)^{i-j} * sum_range(l,r,j) / ai^j
            ld Pi = P[i];
            if (Pi == 0.0L) continue;
            ld partial = 0.0L;
            for (int j = 0; j <= i; ++j) {
                ld s_j = sum_range(l, r, j);
                if (s_j == 0.0L) continue;
                // C[i][j], pow_neg_t[i-j], inv_pow[j]
                partial += C[i][j] * pow_neg_t[i-j] * s_j * inv_pow[j];
            }
            res += Pi * partial;
        }
        return res;
    }
};

// ----------------- Example usage: reproduces your original algorithm but generic -----------------

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ld> a(n);
    for (int i = 0; i < n; ++i) {
        double tmp; cin >> tmp; a[i] = (ld)tmp;
    }
    sort(a.begin(), a.end());

    // PARAMETERS: change these as you like
    const int DEGREE = 10;                // M in your original code
    // centers: the Taylor expansion centers T[0..K-1]
    vector<ld> centers = { 0.0L, 0.5L, 1.0L }; 

    // splits: boundaries expressed as fractions of a[i], length must be centers.size()+1
    // segments: [ splits[k], splits[k+1] ) uses centers[k]
    // original code uses splits = {0, 1/3, 2/3, 1}
    vector<ld> splits = { 0.0L, 1.0L/3.0L, 2.0L/3.0L, 1.0L };

    // Create approximator and build polynomials for sqrt using your original recurrence.
    TaylorApproximator approx(DEGREE, centers);
    approx.build_taylor_sqrt();

    // If you want to plug your own builder, use:
    // approx.build_generic([](int k, int deg, vector<ld>& P, ld center){ /* fill P[0..deg-1] */ });

    // Precompute prefixes of powers
    approx.build_prefix(a);

    // Now main loop: for each i, split j < i into segments according to splits*ai
    ld result = 0.0L;
    for (int i = 1; i < n; ++i) {
        ld ai = a[i];

        // find segment endpoints (indices)
        vector<int> ends;
        ends.reserve(splits.size());
        for (size_t s = 1; s < splits.size(); ++s) {
            // upper_bound of splits[s]*ai in a -> returns first > value, subtract 1 to get last <=
            ld val = splits[s] * ai;
            int idx = int(upper_bound(a.begin(), a.begin() + i, val) - a.begin()) - 1;
            ends.push_back(idx);
        }
        // ends now contains K values where K = centers.size(): end index for each segment
        // segment k spans [ (k==0?0:ends[k-1]+1) .. ends[k] ]
        ld cur = 0.0L;
        int prev = -1;
        for (size_t k = 0; k < centers.size(); ++k) {
            int l = prev + 1;
            int r = ends[k];
            if (l <= r) {
                cur += approx.calc_segment(l, r, ai, (int)k);
            }
            prev = r;
        }

        cur *= sqrtl(ai);
        result += cur;
    }

    cout.setf(std::ios::fixed);
    cout << setprecision(6) << (double)result << "\n";
    return 0;
}
