#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef vector<vector<ll> > Matrix;

const ll p = 998244353;
const ll phi_p = p - 1;
const ll primitive_root_p = 3;

Matrix init_mat(ll n)
{
	Matrix res(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++) {
		res[i][i] = 1;
	}
	return res;
}

Matrix multiply(const Matrix &a, const Matrix &b)
{
	ll n = a.size();
	Matrix res(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			for (ll k = 0; k < n; k++) {
				res[i][j] = (res[i][j] + a[i][k] * b[k][j] % phi_p) % phi_p;
			}
		}
	}
	return res;
}

Matrix powmod(Matrix &a, ll exp)
{
	ll n = a.size();
	Matrix res = init_mat(n);
	while (exp) {
		if (exp & 1)
			res = multiply(res, a);
		a = multiply(a, a);
		exp >>= 1;
	}
	return res;
}

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

// ll cal_primitive_root()
// {
// 	ll phi = phi_p;
// 	for (ll g = 2; g < p; g++) {
// 		bool is_primitive = true;
// 		for (ll i = 2; i * i <= phi; i++) {
// 			if (phi % i != 0)
// 				continue;
// 			while (phi % i == 0)
// 				phi /= i;
// 			if (pow(g, phi_p / i) == 1) {
// 				is_primitive = false;
// 				break;
// 			}
// 		}
// 		if (is_primitive)
// 			return g;
// 	}
// 	return -1;
// }

ll discrete_log(ll a, ll b, ll m)
{
	ll n = sqrt(m) + 1;
	unordered_map<ll, ll> rhs;
	ll cur = b;
	for (ll q = 0; q <= n; q++) {
		rhs[cur] = q;
		cur = cur * a % m;
	}

	ll an = powmod(a, n);
	cur = 1;
	for (ll p = 1; p <= n; p++) {
		cur = cur * an % m;
		if (rhs.find(cur) != rhs.end()) {
			return n * p - rhs[cur];
		}
	}
	return -1;
}

ll solve()
{
	ll k;
	cin >> k;
	Matrix mat(k, vector<ll>(k, 0));
	for (ll i = 0; i < k - 1; i++) {
		mat[i][i + 1] = 1;
	}
	for (ll i = k - 1; i >= 0; i--) {
		cin >> mat[k - 1][i];
	}

	ll n, b;
	cin >> n >> b;
	if (b == 0)
		return 0;

	auto tmp = powmod(mat, n - k);
	ll a = tmp[k - 1][k - 1];
	ll y = discrete_log(powmod(primitive_root_p, a), b, p);
	if (y == -1)
		return -1;
	return powmod(primitive_root_p, y);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve();
}
