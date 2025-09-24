#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

typedef vector<vector<ll> > Matrix;

Matrix build_transition_matrix(vector<ll> &w)
{
	ll m = w.size();

	Matrix res(m, vector<ll>(m, 0));
	for (ll i = 0; i < m; i++) {
		for (ll j = 0; j < m; j++) {
			res[i][j] = w[(i + m - j) % m];
		}
	}

	return res;
}

Matrix identity_matrix(ll m)
{
	Matrix res(m, vector<ll>(m, 0));

	for (ll i = 0; i < m; i++) {
		res[i][i] = 1;
	}

	return res;
}

Matrix multiply(Matrix &a, Matrix &b)
{
	ll m = a.size();

	Matrix res(m, vector<ll>(m, 0));

	for (ll i = 0; i < m; i++) {
		for (ll j = 0; j < m; j++) {
			for (ll k = 0; k < m; k++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
			}
		}
	}

	return res;
}

vector<ll> multiply(Matrix &a, vector<ll> &b)
{
	ll m = a.size();
	vector<ll> res(m, 0);

	for (ll i = 0; i < m; i++) {
		for (ll j = 0; j < m; j++) {
			res[i] += a[i][j] * b[j];
		}
	}

	return res;
}

Matrix pow(Matrix &a, ll b)
{
	Matrix res = identity_matrix(a.size());

	while (b) {
		if (b & 1) {
			res = multiply(res, a);
		}
		a = multiply(a, a);
		b /= 2;
	}

	return res;
}

ll count(ll edge_count, vector<ll> &start, vector<ll> &mid, vector<ll> &end)
{
	ll n = start.size();
	ll m = mid.size();

	vector<ll> dp(m, 0);
	for (ll i = 0; i < n; i++) {
		dp[start[i] % m]++;
	}

	auto transition = build_transition_matrix(mid);
	auto all_transition = pow(transition, edge_count - 1);
	dp = multiply(all_transition, dp);

	vector<ll> ndp(m, 0);
	for (ll i = 0; i < n; i++) {
		ll val = end[i];

		for (ll r = 0; r < m; r++) {
			ndp[(val + r) % m] += dp[r];
			ndp[(val + r) % m] %= MOD;
		}
	}

    return ndp[0];
}

void solve()
{
	ll n, l, m;
	cin >> n >> l >> m;
	vector<ll> start(n), mid(n), rmid(m, 0), end(n);
	for (ll i = 0; i < n; i++) {
		cin >> start[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> mid[i];
		rmid[mid[i] % m]++;
	}
	for (ll i = 0; i < n; i++) {
		cin >> end[i];
		end[i] += mid[i];
	}
	cout << count(l - 1, start, rmid, end) << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
