#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

ll get_gcd(ll a, ll b)
{
	ll new_a = max(a, b);
	ll new_b = min(a, b);
	while (new_b != 0) {
		ll temp = new_a % new_b;
		new_a = new_b;
		new_b = temp;
	}
	return new_a;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	ll count = 0;
	for (int sub_length = 2; sub_length <= n; sub_length++) {
		ll cur_sync_count = a[n - 1] == a[n - sub_length] ? 1 : 0;
		count += cur_sync_count;
		for (int i = n - 2; i - sub_length + 1 >= 0; i--) {
			if (a[i] == a[i - sub_length + 1]) {
				cur_sync_count += 1;
			} else {
				cur_sync_count = 0;
			}
			count += cur_sync_count;
		}
	}

	count *= 2;
	count += n * (n + 1) / 2;

	ll sample_space = n * n;
	ll gcd = get_gcd(count, sample_space);

	cout << count / gcd << "/" << sample_space / gcd;
}
