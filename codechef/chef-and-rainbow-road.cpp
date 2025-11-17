#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MOD = 998244353;
const int ROOT = 3;

i64 modpow(i64 a, long long e){
    a %= MOD; if (a < 0) a += MOD;
    i64 r = 1;
    while (e){
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}
int invmod(int x){ return (int)modpow(x, MOD-2); }
inline int addmod(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
inline int submod(int a,int b){ a-=b; if(a<0) a+=MOD; return a; }

void fft(vector<int>& a, bool invert){
    int n = (int)a.size();
    assert((n & (n-1)) == 0);
    for (int i=1,j=0;i<n;i++){
        int bit = n>>1;
        for (; j & bit; bit >>=1) j ^= bit;
        j ^= bit;
        if (i<j) swap(a[i], a[j]);
    }
    for (int len=2; len<=n; len<<=1){
        int wlen = (int)modpow(ROOT, (MOD - 1) / len);
        if (invert) wlen = invmod(wlen);
        for (int i=0;i<n;i+=len){
            int w = 1;
            for (int j=0;j<len/2;j++){
                int u = a[i+j];
                int v = (int)((long long)a[i+j+len/2] * w % MOD);
                a[i+j] = addmod(u, v);
                a[i+j+len/2] = submod(u, v);
                w = (int)((long long)w * wlen % MOD);
            }
        }
    }
    if (invert){
        int mul = invmod(n);
        for (auto &x: a) x = (int)((long long)x * mul % MOD);
    }
}

// fixed convolution: choose FFT size based on full linear convolution length
vector<int> convolution(const vector<int>& A, const vector<int>& B, int need){
    if (need <= 0) return {};
    if (A.empty() || B.empty()) return {};
    int fullLen = (int)A.size() + (int)B.size() - 1;
    int retLen = min(need, fullLen);
    int n = 1;
    while (n < fullLen) n <<= 1; // IMPORTANT: use fullLen, not 'need'
    vector<int> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i=0;i<n;i++) fa[i] = (int)((long long)fa[i] * fb[i] % MOD);
    fft(fa, true);
    fa.resize(retLen);
    return fa;
}

vector<int> poly_mul(const vector<int>& a, const vector<int>& b){
    if (a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1;
    return convolution(a,b,need);
}

void trim(vector<int>& v){
    while (!v.empty() && v.back() == 0) v.pop_back();
    if (v.empty()) v.push_back(0);
}

vector<int> build_Q_dnc(const vector<int>& a, int l, int r, int cap){
    if (l == r){
        vector<int> res(2);
        res[0] = 1;
        res[1] = (MOD - a[l]) % MOD;
        if ((int)res.size() > cap) res.resize(cap);
        return res;
    }
    int mid = (l + r) >> 1;
    vector<int> L = build_Q_dnc(a, l, mid, cap);
    vector<int> R = build_Q_dnc(a, mid+1, r, cap);
    int need = min(cap, (int)L.size() + (int)R.size() - 1);
    return convolution(L, R, need);
}

// polynomial inverse (Newton) : res = 1 / a mod x^{need}
vector<int> poly_inv(const vector<int>& a, int need){
    assert(need > 0 && !a.empty());
    assert(a[0] != 0);
    vector<int> res(1, invmod(a[0]));
    int cur = 1;
    while (cur < need){
        int n = min(2*cur, need);
        vector<int> pr = convolution(a, res, n);
        pr.resize(n);
        for (int i=0;i<n;i++) pr[i] = submod(0, pr[i]);
        pr[0] = addmod(pr[0], 2);
        res = convolution(res, pr, n);
        res.resize(n);
        cur = n;
    }
    res.resize(need);
    return res;
}

// Bostan-Mori for P/Q (returns k-th coefficient, 0-based)
int bostan(vector<int> P, vector<int> Q, long long k){
    trim(P); trim(Q);
    if ((int)P.size() >= (int)Q.size()) P.resize((int)Q.size()-1);
    while (k > 0){
        vector<int> Qneg = Q;
        for (int i=1;i<(int)Qneg.size();i+=2) Qneg[i] = (MOD - Qneg[i]) % MOD;
        vector<int> U = poly_mul(P, Qneg);
        vector<int> V = poly_mul(Q, Qneg);
        int parity = (int)(k & 1);
        vector<int> Pn, Qn;
        for (int i=parity;i<(int)U.size(); i+=2) Pn.push_back(U[i]);
        for (int i=0;i<(int)V.size(); i+=2) Qn.push_back(V[i]);
        if (Pn.empty()) Pn.push_back(0);
        if (Qn.empty()) Qn.push_back(0);
        P = move(Pn); Q = move(Qn);
        trim(P); trim(Q);
        if ((int)P.size() >= (int)Q.size()) P.resize((int)Q.size()-1);
        k >>= 1;
    }
    int num = P.size()? P[0]%MOD : 0;
    int den = Q.size()? Q[0]%MOD : 1;
    return (int)((long long)num * invmod(den) % MOD);
}

// multipoint evaluation of polynomial f at points xs using product tree + remainders
vector<int> multipoint_eval(const vector<int>& f, const vector<int>& xs){
    int m = xs.size();
    if (m == 0) return {};
    // product tree
    vector<vector<int>> tree(4*m);
    function<void(int,int,int)> build = [&](int node,int l,int r){
        if (l==r){
            // (X - xs[l]) = [ -xs[l], 1 ]
            tree[node] = { (MOD - xs[l]) % MOD, 1 };
            return;
        }
        int mid = (l+r)>>1;
        build(node<<1, l, mid);
        build(node<<1|1, mid+1, r);
        tree[node] = poly_mul(tree[node<<1], tree[node<<1|1]);
    };
    build(1, 0, m-1);

    vector<int> res(m);
    // polynomial division remainder: rem = A % B (using convolution-based division)
    auto poly_rem = [&](const vector<int>& A, const vector<int>& B){
        int n = (int)A.size(), mB = (int)B.size();
        if (n < mB) {
            vector<int> tmp = A; trim(tmp); return tmp;
        }
        // quotient = rev( trunc( rev(A) * inv( rev(B) ) ) )
        vector<int> revA(A.rbegin(), A.rend()), revB(B.rbegin(), B.rend());
        int need = n - mB + 1;
        vector<int> invRevB = poly_inv(revB, need);
        vector<int> quot = convolution(revA, invRevB, need);
        quot.resize(need);
        reverse(quot.begin(), quot.end());
        vector<int> prod = poly_mul(B, quot);
        vector<int> rem(n);
        for (int i=0;i<n;i++){
            int pv = (i < (int)prod.size()) ? prod[i] : 0;
            rem[i] = submod(A[i], pv);
        }
        trim(rem);
        return rem;
    };

    function<void(int,int,int,const vector<int>&)> solve = [&](int node,int l,int r,const vector<int>& poly){
        if (l==r){
            // evaluate poly at xs[l] with Horner
            long long val = 0;
            for (int i = (int)poly.size()-1; i>=0; --i) val = (val * 1 + poly[i]) % MOD;
            res[l] = (int)val;
            return;
        }
        int mid = (l+r)>>1;
        vector<int> leftRem = poly_rem(poly, tree[node<<1]);
        vector<int> rightRem = poly_rem(poly, tree[node<<1|1]);
        solve(node<<1, l, mid, leftRem);
        solve(node<<1|1, mid+1, r, rightRem);
    };
    solve(1, 0, m-1, f);
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, q;
    if (!(cin >> m >> n >> q)) return 0;
    vector<int> a(n);
    for (int i=0;i<n;i++){ cin >> a[i]; a[i] %= MOD; if (a[i]<0) a[i]+=MOD; }
    vector<long long> Ks(q);
    long long Kmax = 0;
    for (int i=0;i<q;i++){ cin >> Ks[i]; Kmax = max(Kmax, Ks[i]); }

    // quick special: if any a[i] == 0 then prefix = 0 => answers are 0
    int prefix = 1;
    bool any_zero = false;
    for (int v : a){
        if (v == 0) any_zero = true;
        prefix = (int)((long long)prefix * v % MOD);
    }
    if (any_zero){
        for (int i=0;i<q;i++) cout << 0 << '\n';
        return 0;
    }

    // thresholds
    const long long K_SMALL = 2000000; // tune
    const int D_SMALL = 600;           // distinct threshold for partial fractions

    unordered_map<int,int> freq;
    freq.reserve(n*2);
    for (int v: a) ++freq[v];
    int D = (int)freq.size();
    bool all_multiplicity_one = true;
    for (auto &pr : freq) if (pr.second > 1) { all_multiplicity_one = false; break; }

    // Branch 1: small Kmax -> build truncated Q and invert
    if (Kmax <= K_SMALL){
        int need = (int)Kmax; // we need coefficients up to K-1 where Kmax is maximum K
        int cap = need + 1;
        vector<int> Q = build_Q_dnc(a, 0, n-1, cap);
        Q.resize(cap);
        vector<int> invQ = poly_inv(Q, cap);
        for (int i=0;i<q;i++){
            long long K = Ks[i];
            if (K <= 0){ cout << 0 << '\n'; continue; }
            long long idx = K - 1;
            if (idx < 0 || idx >= cap){ cout << 0 << '\n'; continue; }
            int coeff = invQ[(int)idx];
            cout << (int)((long long)prefix * coeff % MOD) << '\n';
        }
        return 0;
    }

    // Branch 2: partial fractions only if distinct small and all multiplicities are 1
    if (D <= D_SMALL && all_multiplicity_one){
        int cap = n + 1;
        vector<int> Q = build_Q_dnc(a, 0, n-1, cap);
        Q.resize(cap);
        // Q'(x)
        vector<int> Qp(max(1, (int)Q.size()-1));
        for (int i=1;i<(int)Q.size();++i) Qp[i-1] = (int)((long long)Q[i]*i % MOD);

        // collect unique values (non-zero guaranteed earlier)
        vector<int> uniqVals; uniqVals.reserve(D);
        for (auto &pr : freq) uniqVals.push_back(pr.first);

        // pts = inv(v)
        vector<int> pts; pts.reserve(uniqVals.size());
        for (int v : uniqVals) pts.push_back((int)invmod(v));

        vector<int> ev = multipoint_eval(Qp, pts); // ev[i] = Q'(1/v)

        // residues c_v = -v * inv(Q'(1/v))
        unordered_map<int,int> resid;
        for (int i=0;i<(int)uniqVals.size();++i){
            int v = uniqVals[i];
            int qprime = ev[i];
            if (qprime == 0) resid[v] = 0;
            else resid[v] = (int)((MOD - (long long)v * invmod(qprime) % MOD) % MOD);
        }

        // answer queries: sum_v c_v * v^{K-1} * prefix
        for (int i=0;i<q;i++){
            long long K = Ks[i];
            if (K <= 0){ cout << 0 << '\n'; continue; }
            long long powidx = K-1;
            int ans = 0;
            for (int v : uniqVals){
                int c = resid[v];
                if (c == 0) continue;
                int p = (int)modpow(v, powidx);
                ans = (ans + (long long)c * p) % MOD;
            }
            ans = (int)((long long)prefix * ans % MOD);
            cout << ans << '\n';
        }
        return 0;
    }

    // Branch 3: general Bostan-Mori fallback
    {
        int cap = n + 1;
        vector<int> Q = build_Q_dnc(a, 0, n-1, cap);
        Q.resize(cap);
        vector<int> P(1,1);
        for (int i=0;i<q;i++){
            long long K = Ks[i];
            long long k = K - 1;
            if (k < 0){ cout << 0 << '\n'; continue; }
            int coeff = bostan(P, Q, k);
            int ans = (int)((long long)prefix * coeff % MOD);
            cout << ans << '\n';
        }
        return 0;
    }

    return 0;
}
