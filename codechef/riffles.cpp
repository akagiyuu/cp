#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

vector<ll> combine(vector<ll> &a, vector<ll> &b)
{
	ll n = a.size();
	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		res[i] = b[a[i]];
	}
	return res;
}

vector<ll> permute(ll n, ll k)
{
	vector<vector<ll> > dp(1, vector<ll>(n));
	for (ll i = 0; i < n; i += 2) {
		dp[0][i / 2] = i;
	}
	for (ll i = 1; i < n; i += 2) {
		dp[0][n / 2 + i / 2] = i;
	}
	for (ll i = 1; (1 << i) <= k; i++) {
		dp.push_back(combine(dp[i - 1], dp[i - 1]));
	}

	vector<ll> res(n);
	for (ll i = 0; i < n; i++) {
		res[i] = i;
	}
	for (ll i = 0; (1 << i) <= k; i++) {
        if((1 << i) & k) {
            res = combine(res, dp[i]);
        }
	}
	for (ll i = 0; i < n; i++) {
		res[i]++;
	}

	return res;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	auto res = permute(n, k);
	for (ll i = 0; i < n; i++) {
		cout << res[i] << " ";
	}
	cout << "\n";
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
