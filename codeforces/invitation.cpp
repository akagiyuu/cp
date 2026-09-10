#include <bits/stdc++.h>
#include <assert.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int N = 1e5 + 7;
const int MOD = 998244353;
const int ROOT = 3;

int fact[N], ifact[N];

int add(int x, int y) {
	x += y;
	if(x >= MOD) x-= MOD;
	return x;
}
int sub(int x, int y) {
	x -= y;
	if(x < 0) x += MOD;
	return x;
}
int powmod(int x, int e) {
	int res = 1;
	while(e) {
		if(e & 1) res = res * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return res;
}
int inverse(int x) {
	return powmod(x, MOD - 2);
}
void build() {
	fact[0] = 1;
	for(int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for(int i = N - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
void fft(vector<int> &a, bool invert) {
	int n = a.size();
	assert((n & (n - 1)) == 0);
	int lg = __builtin_ctz(n);
	for (int i = 0; i < n; ++i) {
		int j = 0;
		for (int k = 0; k < lg; ++k) if ((i&1<<k)!=0) j |= 1ll << (lg-k-1);
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len *= 2) {
		int wlen = powmod(ROOT, (MOD - 1) / len);
		if (invert) wlen = inverse(wlen);
		for (int i = 0; i < n; i += len) {
			int w = 1;
			for (int j = 0; j < len / 2; ++j) {
				int u = a[i + j];
				int v = a[i + j + len / 2] * w % MOD;
				a[i + j] = add(u, v);
				a[i + j + len / 2] = sub(u, v);
				w = w * wlen % MOD;
			}
		}
	}
	if (invert) {
		int mul = inverse(n);
		for (auto &x : a) x = x * mul % MOD;
	}
}
void multiply(vector<int> &a, vector<int> &b) {
	int N = a.size() + b.size() - 1;
	int sz = 1;
	while(sz < N) sz <<= 1;
	a.resize(sz, 0);
	b.resize(sz, 0);

	fft(a, false);
	fft(b, false);
	for(int i = 0; i < sz; i++) a[i] = a[i] * b[i] % MOD;
	fft(a, true);
	a.resize(N);
}

struct Event {
	int x;
	int type;
};

vector<int> count(const vector<pi> &a) {
	int n = a.size();
	vector<int> res(n + 1, 0);
	vector<Event> ev;
	for(auto [l, r] : a) {
		ev.push_back(Event { .x = l, .type = 1 });
		ev.push_back(Event { .x = r + 1, .type = -1 });
	}
	sort(ev.begin(), ev.end(), [](const Event &a, const Event &b) {
		return a.x < b.x;
	});
	vector<int> freq(n + 1, 0);
	int i = 0, cnt = 0, m = ev.size();
	while(i < m) {
		int x = ev[i].x;
		while(i < m && ev[i].x == x) {
			cnt += ev[i].type;
			i++;
		}
		if(cnt == 0) continue;
		int len = ev[i].x - x;
		freq[cnt] = add(freq[cnt], len);
	}
	vector<int> inv_p(ifact, ifact + n + 1);
	vector<int> c(n + 1, 0);
	for(int i = 0; i <= n; i++) c[i] = fact[n - i]  * freq[n - i] % MOD;
	multiply(c, inv_p);
	for(int k = 1; k <= n; k++) {
		res[k] = ifact[k] * c[n - k] % MOD;
	}
	return res;
 }

void solve()
{
	int n;
	cin >> n;
	vector<pi> a(n);
	for(int i = 0; i < n; i++) cin >> a[i].fi >> a[i].se;
	auto cnt = count(a);
	vector<pi> b;
	for(int i = 0; i < n; i++) {
		auto [l, r] = a[i];
		r--;
		if(l <= r) b.push_back({l, r});
	}
	auto dup_cnt = count(b);
	dup_cnt.resize(n + 1, 0);
	for(int k = 1; k <= n; k++) cout << sub(cnt[k], dup_cnt[k]) << ' ';
	cout << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
