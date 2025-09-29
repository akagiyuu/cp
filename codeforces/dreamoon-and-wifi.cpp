#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll nCk(ll n, ll k)
{
	if (k < 0)
		return 0;
	if (k > n)
		return 0;
	ll res = 1;
	for (ll i = n - k + 1; i <= n; i++) {
		res *= i;
	}
	for (ll i = 2; i <= k; i++) {
		res /= i;
	}
	return res;
}

void solve()
{
	string s1, s2;
	cin >> s1 >> s2;
	ll n = s1.size();
	ll p = 0, q = 0;
	for (ll i = 0; i < n; i++) {
		if (s1[i] == '+')
			p++;
	}
	for (ll i = 0; i < n; i++) {
		if (s2[i] == '+')
			p--;
		if (s2[i] == '?')
			q++;
	}

	long double res = (long double)nCk(q, p) / (long double)(1 << q);
	cout << setprecision(10) << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
