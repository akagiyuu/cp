#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>

using namespace std;

typedef unsigned long long ll;

ll MOD = 1000000007;

bool is_spell_applicable(ll n, ll a, ll b)
{
	return a <= n && ((n % (1ll << b)) == 0);
}

ll solve(ll n, const vector<ll> &as, const vector<ll> &bs)
{
	queue<ll> q;
	q.push(0);
	ll count = 0;
	while (!q.empty()) {
		ll cur = q.front();
		q.pop();
		if (cur == n) {
			count += 1;
			continue;
		}
		for (int i = 0; i < as.size(); i++) {
			ll next = cur + as[i];
			if (next > n || !is_spell_applicable(next, as[i], bs[i])) {
				continue;
			}
			q.push(next);
		}
	}
    return count;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<ll> as(m);
	vector<ll> bs(m);
	for (int i = 0; i < m; i++) {
		cin >> as[i] >> bs[i];
	}
	if (n == 0) {
		cout << 0;
		return 0;
	}
	cout << solve(n, as, bs);
}
