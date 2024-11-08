#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

// ll count_valid_park(ll n, vector<ll> &choosen)
// {
// 	if (choosen.size() == n) {
// 		vector<bool> is_possible(n, false);
// 		is_possible[0] = true;
// 		for (auto cur : choosen) {
// 			ll i;
// 			for (i = 0; i < cur; i++) {
// 				if (is_possible[i]) {
// 					break;
// 				}
// 			}
// 			while (i < cur) {
// 				is_possible[i] = true;
// 				i++;
// 			}
// 			for (i = cur + 1; i < n; i++) {
// 				if (is_possible[i]) {
// 					break;
// 				}
// 			}
// 			while (i < n) {
// 				is_possible[i] = true;
// 				i++;
// 			}
// 			is_possible[cur] = false;
// 		}
// 		if (!is_possible[n - 1] && choosen[0] != 0 && choosen[n - 1] != n - 1) {
//             cpp_dump(choosen);
// 		}
// 		return is_possible[n - 1] ? 1 : 0;
// 	}
// 	ll count = 0;
// 	for (ll i = 0; i < n; i++) {
// 		if (find(choosen.begin(), choosen.end(), i) != choosen.end()) {
// 			continue;
// 		}
// 		choosen.push_back(i);
// 		count += count_valid_park(n, choosen);
// 		choosen.pop_back();
// 	}
// 	return count;
// }

ll const N = 1e7;
ll fact_sum[N + 1];

void build()
{
	fact_sum[0] = 1;
	ll cur = 1;
	for (ll i = 1; i <= N; i++) {
		cur = cur * i % MOD;
		fact_sum[i] = (fact_sum[i - 1] + cur) % MOD;
	}
}

void solve()
{
	ll n;
	cin >> n;
	ll res = (fact_sum[n] - fact_sum[n - 1] + 2 + MOD) % MOD;
	res = (res + n * fact_sum[n - 2] % MOD) % MOD;
	res = (res - 3 * fact_sum[n - 1] % MOD + MOD) % MOD;
    cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	while (t--)
		solve();
}
