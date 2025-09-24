#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll M = 52;

ll encode(char c)
{
	if ('a' <= c && c <= 'z')
		return c - 'a';
	return c - 'A' + 26;
}

ll count(ll n, ll m, set<pair<short, short> > &invalids)
{
	array<ll, M> pre;
	for (ll i = 0; i < m; i++) {
		pre[i] = 1;
	}

	for (ll i = 1; i < n; i++) {
		array<ll, M> cur;
		for (ll i = 0; i < m; i++) {
			cur[i] = 0;
		}

		for (ll j = 0; j < m; j++) {
			for (ll k = 0; k < m; k++) {
				if (invalids.count(make_pair(j, k)))
					continue;
				cur[k] = (cur[k] + pre[j]) % MOD;
			}
		}
		pre = cur;
	}

	ll res = 0;
	for (ll i = 0; i < m; i++) {
		res = (res + pre[i]) % MOD;
	}
	return res;
}

typedef vector<vector<ll> > Matrix;

Matrix identity_mat(ll m)
{
	Matrix res(m, vector<ll>(m, 0));

	for (ll i = 0; i < m; i++) {
		res[i][i] = 1;
	}

	return res;
}

Matrix mul(Matrix &a, Matrix &b)
{
	ll m = a.size();
	Matrix res(m, vector<ll>(m, 0));

	for (ll i = 0; i < m; i++) {
		for (ll j = 0; j < m; j++) {
			res[i][j] = 0;
			for (ll k = 0; k < m; k++) {
				res[i][j] += a[i][k] * b[k][j] % MOD;
				res[i][j] %= MOD;
			}
		}
	}

	return res;
}

Matrix pow(Matrix a, ll b)
{
	Matrix res = identity_mat(a.size());

	while (b) {
		if (b & 1) {
			res = mul(res, a);
		}
		a = mul(a, a);
		b /= 2;
	}

	return res;
}

ll count(ll n, ll m, Matrix adj)
{
	Matrix nth_adj = pow(adj, n - 1);

	ll res = 0;
	for (ll i = 0; i < m; i++) {
		for (ll j = 0; j < m; j++) {
			res += nth_adj[i][j];
            res %= MOD;
		}
	}

	return res;
}

void solve()
{
	ll n, m, k;
	cin >> n >> m >> k;

	vector<vector<ll> > adj(m, vector<ll>(m, 1));
	char a, b;
	for (ll i = 0; i < k; i++) {
		cin >> a >> b;
		adj[encode(a)][encode(b)] = 0;
	}

	cout << count(n, m, adj);
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
