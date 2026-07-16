#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;
const int N = 26;

pair<int, array<array<int, N>, N> > generate(int k, int comp_size, vector<pi> cnt)
{
	int ops_cnt = 0;
	array<array<int, N>, N> ops;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ops[i][j] = 0;
		}
	}
	while ((int)cnt.size() > k) {
		auto [c, v] = cnt.back();
		cnt.pop_back();
		for (int i = 0; i < (int)cnt.size() && v > 0; i++) {
			if (cnt[i].se >= comp_size)
				continue;
			int cur = min(v, comp_size - cnt[i].se);
			ops[c][cnt[i].fi] += cur;
			ops_cnt += cur;
			cnt[i].se += cur;
			v -= cur;
		}
	}

	int i = 0;
	for (int j = 0; j < k; j++) {
		if (cnt[j].se >= comp_size)
			continue;
		while (i < j && cnt[j].se < comp_size) {
			int cur = min(comp_size - cnt[j].se, cnt[i].se - comp_size);
			ops[cnt[i].fi][cnt[j].fi] += cur;
			ops_cnt += cur;
			cnt[i].se -= cur;
			cnt[j].se += cur;
			if (cnt[i].se > comp_size)
				break;
			i++;
		}
		assert(cnt[j].se == comp_size);
	}

	return { ops_cnt, ops };
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	array<int, N> cnt_raw;
	fill(cnt_raw.begin(), cnt_raw.end(), 0);
	for (auto c : s)
		cnt_raw[c - 'a']++;
	vector<pi> cnt;
	for (int i = 0; i < N; i++) {
		cnt.push_back({ i, cnt_raw[i] });
	}
	sort(cnt.begin(), cnt.end(), [](const pi &a, const pi &b) { return a.se > b.se; });

	int m = n;
	array<array<int, N>, N> ops;
	for (int i = 1; i <= N; i++) {
		if (n % i != 0)
			continue;
		auto cur = generate(i, n / i, cnt);
		if (cur.fi < m) {
			m = cur.fi;
			ops = cur.se;
		}
	}
	for (int i = 0; i < n; i++) {
		int cur = s[i] - 'a';
		for (int j = 0; j < N; j++) {
			if (ops[cur][j] == 0)
				continue;

			ops[cur][j]--;
			s[i] = j + 'a';
			break;
		}
	}
	cout << m << "\n";
	cout << s << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
