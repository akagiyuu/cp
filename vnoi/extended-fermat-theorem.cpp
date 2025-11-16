#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

static ll modmul(ll a, ll b, ll mod)
{
	__int128 res = (__int128)a * b;
	res %= mod;
	return (ll)res;
}
static ll modpow(ll a, ll e, ll mod)
{
	ll r = 1 % mod;
	a %= mod;
	while (e) {
		if (e & 1)
			r = modmul(r, a, mod);
		a = modmul(a, a, mod);
		e >>= 1;
	}
	return r;
}

static ll egcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0) {
		x = (a >= 0 ? 1 : -1);
		y = 0;
		return llabs(a);
	}
	ll x1, y1;
	ll g = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}
static ll invmod(ll a, ll m)
{
	ll x, y;
	ll g = egcd(a, m, x, y);
	if (g != 1 && g != -1)
		return -1;
	x %= m;
	if (x < 0)
		x += m;
	return x;
}

// Legendre symbol (a|p), p must be odd prime. Returns 1, -1, or 0.
static int legendre(ll a, ll p)
{
	if (a % p == 0)
		return 0;
	ll t = modpow(a, (p - 1) / 2, p);
	if (t == 1)
		return 1;
	if (t == p - 1)
		return -1;
	return 0; // shouldn't happen
}

// Tonelli-Shanks: square root of n modulo odd prime p (returns -1 if none)
static ll tonelli_shanks(ll n, ll p)
{
	n %= p;
	if (n < 0)
		n += p;
	if (n == 0)
		return 0;
	if (p == 2)
		return n;
	if (legendre(n, p) != 1)
		return -1;
	if (p % 4 == 3)
		return modpow(n, (p + 1) / 4, p);
	ll Q = p - 1;
	ll S = 0;
	while ((Q & 1) == 0) {
		Q >>= 1;
		++S;
	}
	ll z = 2;
	while (legendre(z, p) != -1)
		++z;
	ll c = modpow(z, Q, p);
	ll R = modpow(n, (Q + 1) / 2, p);
	ll t = modpow(n, Q, p);
	ll M = S;
	while (t != 1) {
		ll i = 1;
		ll tt = modmul(t, t, p);
		while (i < M) {
			if (tt == 1)
				break;
			tt = modmul(tt, tt, p);
			++i;
		}
		ll b = modpow(c, 1LL << (M - i - 1), p);
		R = modmul(R, b, p);
		c = modmul(b, b, p);
		t = modmul(t, c, p);
		M = i;
	}
	return R;
}

// BSGS: finds smallest x >= 0 s.t. base^x = target (mod mod), or -1
static ll bsgs(ll base, ll target, ll mod)
{
	base %= mod;
	target %= mod;
	if (mod == 1)
		return 0;
	if (target == 1)
		return 0;
	ll cnt = 0;
	ll t = 1;
	ll g;
	while ((g = std::gcd(base, mod)) > 1) {
		if (target == t)
			return cnt;
		if (target % g != 0)
			return -1;
		target /= g;
		mod /= g;
		t = modmul(t, base / g, mod);
		++cnt;
	}
	unordered_map<ll, ll> vals;
	ll m = (ll)floor(sqrt((long double)mod)) + 1;
	ll e = 1;
	for (ll j = 0; j < m; j++) {
		if (!vals.count(e))
			vals[e] = j;
		e = modmul(e, base, mod);
	}
	ll factor = modpow(base, m, mod);
	ll cur = target;
	for (ll i = 0; i <= m; i++) {
		if (vals.count(cur)) {
			ll ans = i * m + vals[cur] - cnt;
			if (ans >= 0)
				return ans;
		}
		cur = modmul(cur, factor, mod);
	}
	return -1;
}

// trial division factorization
static vector<pair<ll, int> > factor_small(ll n)
{
	vector<pair<ll, int> > f;
	for (ll p = 2; p * p <= n; ++p) {
		if (n % p == 0) {
			int c = 0;
			while (n % p == 0) {
				n /= p;
				++c;
			}
			f.emplace_back(p, c);
		}
	}
	if (n > 1)
		f.emplace_back(n, 1);
	return f;
}

static ll vp(ll x, ll p)
{
	if (x == 0)
		return INT64_MAX;
	ll c = 0;
	while (x % p == 0) {
		x /= p;
		++c;
	}
	return c;
}

static ll find_primitive_root(ll p, int e)
{
	if (p == 2) {
		if (e == 1)
			return 1;
		if (e == 2)
			return 3;
		return 5;
	}
	ll mod = 1;
	for (int i = 0; i < e; i++)
		mod *= p;
	ll phi = mod / p * (p - 1);
	auto fac = factor_small(phi);
	vector<ll> primes;
	for (auto &pr : fac)
		primes.push_back(pr.first);
	for (ll g = 2; g < mod; ++g) {
		bool ok = true;
		for (auto q : primes) {
			if (modpow(g, phi / q, mod) == 1) {
				ok = false;
				break;
			}
		}
		if (ok)
			return g;
	}
	return -1;
}

// Solve x^k = a (mod p^E) where gcd(a,p)=1
static vector<ll> solve_unit_prime_power(ll p, int E, ll k, ll a)
{
	ll mod = 1;
	for (int i = 0; i < E; i++)
		mod *= p;
	if (mod == 1)
		return { 0 };
	if (p == 2) {
		if (E == 1)
			return { a % 2 };
		if (E == 2) {
			vector<ll> sols;
			for (ll x = 1; x < 4; x += 2)
				if (modpow(x, k, 4) == (a % 4))
					sols.push_back(x % 4);
			return sols;
		}
		ll mod2 = mod;
		ll g = 5;
		ll order = 1LL << (E - 2);
		bool a_is_minus1 = (a % mod2 == (mod2 - 1));
		if (a_is_minus1 && (k % 2 == 0))
			return {};
		vector<ll> sols;
		for (int u = 0; u < 2; ++u) {
			if (((k % 2) * u) % 2 != (a_is_minus1 ? 1 : 0))
				continue;
			ll target = a % mod2;
			if (u == 1)
				target = (ll)((mod2 - 1) % mod2);
			ll A = bsgs(g, target, mod2);
			if (A == -1)
				continue;
			ll d = std::gcd((ll)k, order);
			if (A % d != 0)
				continue;
			ll base = order / d;
			ll kk = k / d;
			ll Adiv = A / d;
			ll invkk = invmod(kk % base, base);
			if (invkk == -1)
				continue;
			ll y0 = modmul(Adiv, invkk, base);
			for (int t = 0; t < d; t++) {
				ll y = (y0 + t * base) % order;
				ll x = modmul(modpow(g, y, mod2), (u ? mod2 - 1 : 1), mod2);
				sols.push_back(x);
			}
		}
		sort(sols.begin(), sols.end());
		sols.erase(unique(sols.begin(), sols.end()), sols.end());
		return sols;
	}
	// Special-case: square root modulo prime (Tonelli-Shanks) is faster and avoids discrete-log pitfalls
	if (E == 1 && k == 2) {
		ll pmod = p;
		ll root = tonelli_shanks(a % pmod, pmod);
		if (root == -1)
			return {};
		ll other = (pmod - root) % pmod;
		if (root == other)
			return { root };
		if (root < other)
			return { root, other };
		return { other, root };
	}
	ll phi = 1;
	for (int i = 0; i < E - 1; i++)
		phi *= p;
	phi *= (p - 1);
	ll g = find_primitive_root(p, E);
	if (g == -1)
		return {};
	ll A = bsgs(g, a % mod, mod);
	if (A == -1)
		return {};
	ll d = std::gcd((ll)k, phi);
	if (A % d != 0)
		return {};
	ll base = phi / d;
	ll kk = k / d;
	ll Adiv = A / d;
	ll invkk = invmod(kk % base, base);
	if (invkk == -1)
		return {};
	ll y0 = modmul(Adiv, invkk, base);
	vector<ll> sols;
	for (int t = 0; t < d; t++) {
		ll y = (y0 + t * base) % phi;
		ll x = modpow(g, y, mod);
		sols.push_back(x);
	}
	sort(sols.begin(), sols.end());
	sols.erase(unique(sols.begin(), sols.end()), sols.end());
	return sols;
}

// Solve x^k ≡ a (mod p^E) (handles valuations)
static vector<ll> solve_prime_power(ll p, int E, ll k, ll a)
{
	ll mod = 1;
	for (int i = 0; i < E; i++)
		mod *= p;
	if (mod == 1)
		return { 0 };
	a %= mod;
	if (a < 0)
		a += mod;
	if (a == 0) {
		ll need = (E + k - 1) / k;
		if (need > E)
			return {};
		vector<ll> res;
		ll start = 1;
		for (int i = 0; i < need; i++)
			start *= p;
		ll cnt = 1;
		for (int i = 0; i < E - need; i++)
			cnt *= p;
		for (ll t = 0; t < cnt; t++)
			res.push_back((start * t) % mod);
		sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());
		return res;
	}
	ll t = vp(a, p);
	if (k != 0 && (t % k != 0))
		return {};
	ll s = (k == 0 ? 0 : t / k);
	ll reduced_mod_power = E - s;
	ll reduced_mod = 1;
	for (int i = 0; i < reduced_mod_power; i++)
		reduced_mod *= p;
	ll a_unit = a;
	for (int i = 0; i < s; i++)
		a_unit /= p;
	a_unit %= reduced_mod;
	if (a_unit < 0)
		a_unit += reduced_mod;
	auto unit_sols = solve_unit_prime_power(p, reduced_mod_power, k, a_unit);
	vector<ll> sols;
	for (auto u : unit_sols) {
		ll x = u;
		for (int i = 0; i < s; i++)
			x = (x * p) % mod;
		sols.push_back(x % mod);
	}
	sort(sols.begin(), sols.end());
	sols.erase(unique(sols.begin(), sols.end()), sols.end());
	return sols;
}

// CRT for coprime moduli
static pair<ll, ll> crt_pair(ll a1, ll m1, ll a2, ll m2)
{
	ll A = m1, B = m2, C = (a2 - a1) % B;
	if (C < 0)
		C += B;
	ll x, y;
	ll g = egcd(A, B, x, y);
	if (C % g != 0)
		return { -1, -1 };
	ll mod = (m1 / g) * m2;
	__int128 mult = (__int128)x * (C / g) % (B / g);
	if (mult < 0)
		mult += (B / g);
	ll t = (ll)mult;
	__int128 res = (__int128)m1 * t + a1;
	ll ans = (ll)((res % mod + mod) % mod);
	return { ans, mod };
}

// Main exported function:
// Returns vector of solutions x (0 <= x < m) satisfying x^exp ≡ r (mod m).
// If empty, no solution.
int discrete_root(ll exp, ll r, ll m)
{
	if (m == 1)
		return -1;
	if (exp < 0)
		return -1; // negative exponents not supported here
	r %= m;
	if (r < 0)
		r += m;
	auto fac = factor_small(m);
	vector<pair<ll, int> > pows = fac;
	// solve each prime power
	vector<vector<ll> > residues;
	vector<ll> mods;
	for (auto &pe : pows) {
		ll p = pe.first;
		int E = pe.second;
		ll modp = 1;
		for (int i = 0; i < E; i++)
			modp *= p;
		auto sols = solve_prime_power(p, E, exp, r);
		if (sols.empty())
			return -1;
		residues.push_back(sols);
		mods.push_back(modp);
	}
	// combine by CRT
	vector<pair<ll, ll> > cur;
	cur.push_back({ 0, 1 });
	for (size_t i = 0; i < residues.size(); ++i) {
		vector<pair<ll, ll> > nxt;
		for (auto &c : cur) {
			for (auto r0 : residues[i]) {
				auto comb = crt_pair(c.first, c.second, r0, mods[i]);
				if (comb.first == -1)
					continue;
				nxt.push_back(comb);
			}
		}
		cur.swap(nxt);
		if (cur.empty())
			return -1;
	}
	return (cur[0].first % m + m) % m;
}

void solve()
{
	ll n, mod, a;
	cin >> n >> mod;
	for (ll i = 0; i < n + 1; i++) {
		cin >> a;
	}
	ll x = discrete_root(2, 4, 1000000009);
	if (x == -1) {
		cout << "NO SOLUTION\n";
	} else {
		for (ll i = 0; i < n; i++) {
			cout << 1 << " ";
		}
		cout << x << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
