#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<ll> prefix_a(3 * n);
	prefix_a[0] = a[0];
	for (int i = 1; i < 3 * n; i++) {
		prefix_a[i] = prefix_a[i - 1] + a[i % n];
	}

	vector<ll> prefix_ia(3 * n);
	prefix_ia[0] = 0;
	for (int i = 1; i < 3 * n; i++) {
		prefix_ia[i] = prefix_ia[i - 1] + i * a[i % n];
	}

	auto cal = [prefix_a, prefix_ia](int x, int k) {
		if (x < k) {
			ll left = prefix_ia[k] - (x == 0 ? 0 : prefix_ia[x - 1]);
			ll right = prefix_a[k] - (x == 0 ? 0 : prefix_a[x - 1]);
			return left - x * right;
		} else {
			ll left = prefix_a[x] - (k == 0 ? 0 : prefix_a[k - 1]);
			ll right = prefix_ia[x] - (k == 0 ? 0 : prefix_ia[k - 1]);
			return x * left - right;
		}
	};

	ll min_dist = LONG_LONG_MAX;
	for (int x = n; x < 2 * n; x++) {
		ll cur_dist = cal(x, x - n / 2) + cal(x, x + (n - 1) / 2);
		min_dist = min(cur_dist, min_dist);
	}
	cout << min_dist << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
