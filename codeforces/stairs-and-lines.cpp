#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll NBIT = 7;
const ll MAX_MASK = 1 << 7;

typedef array<array<ll, MAX_MASK>, MAX_MASK> Matrix;

Matrix id()
{
	Matrix res;
    for (ll i = 0; i < MAX_MASK; i++) {
        for (ll j = 0; j < MAX_MASK; j++) {
            res[i][j] = 0;
        }
    }
	for (ll i = 0; i < MAX_MASK; i++) {
		res[i][i] = 1;
	}
	return res;
}

Matrix mul(Matrix &a, Matrix &b)
{
	Matrix res;
	for (ll i = 0; i < MAX_MASK; i++) {
		for (ll j = 0; j < MAX_MASK; j++) {
			res[i][j] = 0;
			for (ll k = 0; k < MAX_MASK; k++) {
				res[i][j] += a[i][k] * b[k][j] % MOD;
				res[i][j] %= MOD;
			}
		}
	}
	return res;
}

Matrix binpow(Matrix &a, ll b)
{
	Matrix res = id( );
	while (b) {
		if (b & 1)
			res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

array<ll, MAX_MASK> mul(Matrix &a, array<ll, MAX_MASK> &b)
{
	array<ll, MAX_MASK> res;
	for (ll i = 0; i < MAX_MASK; i++) {
		res[i] = 0;
		for (ll j = 0; j < MAX_MASK; j++) {
			res[i] += a[i][j] * b[j] % MOD;
			res[i] %= MOD;
		}
	}
	return res;
}

ll ith_bit(ll n, ll i)
{
	return (n >> i) & 1;
}

Matrix build(ll h)
{
	Matrix res;
	for (ll i = 0; i < MAX_MASK; i++) {
		for (ll j = 0; j < MAX_MASK; j++) {
			res[i][j] = 0;
		}
	}

	ll cur_max_mask = 1 << h;
	ll force = MAX_MASK - cur_max_mask;
	for (ll left = 0; left < cur_max_mask; left++) {
		for (ll right = 0; right < cur_max_mask; right++) {
			ll count = 0;

			for (ll horizontal = 1; horizontal < cur_max_mask; horizontal += 2) {
				ll mask = horizontal | cur_max_mask;
				ll is_valid = true;
				for (ll i = 0; i < h; i++) {
					ll edge_count = ith_bit(left, i) + ith_bit(right, i) + ith_bit(mask, i) +
							ith_bit(mask, i + 1);
					if (edge_count == 4) {
						is_valid = false;
						break;
					}
				}
				if (is_valid)
					count++;
			}

			res[force | left][force | right] = count;
		}
	}
	return res;
}

void solve()
{
	array<ll, NBIT> w;
	for (ll i = 0; i < NBIT; i++) {
		cin >> w[i];
	}
	array<ll, MAX_MASK> dp;
	for (ll i = 0; i < MAX_MASK; i++) {
		dp[i] = 0;
	}
	dp[MAX_MASK - 1] = 1;
	for (ll h = 1; h <= NBIT; h++) {
		if (w[h - 1] == 0)
			continue;
		Matrix s = build(h);
		s = binpow(s, w[h - 1]);
		dp = mul(s, dp);
	}
	cout << dp[MAX_MASK - 1];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
