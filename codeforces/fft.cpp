#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static double PI = acos(-1.0);

struct C {
	double r, i;

	C() = default;
	C(double _r, double _i = 0.0)
		: r(_r)
		, i(_i)
	{
	}

	inline C operator+(const C &o) const
	{
		return { r + o.r, i + o.i };
	}

	inline C operator-(const C &o) const
	{
		return { r - o.r, i - o.i };
	}

	inline C operator*(const C &o) const
	{
		return { r * o.r - i * o.i, r * o.i + i * o.r };
	}

	inline C operator*(double x) const
	{
		return { r * x, i * x };
	}
};

static vector<C> roots;
static vector<int> rev;

inline C conj(const C &x)
{
	return { x.r, -x.i };
}

void init_fft(int n)
{
	int lg = __builtin_ctz((unsigned)n);

	// Only need roots[0 .. n/2-1]
	roots.resize(n >> 1);

	// Generate all roots using recurrence instead of n sin/cos calls.
	const double angle = 2.0 * PI / n;
	const C step(cos(angle), sin(angle));

	roots[0] = C(1.0, 0.0);

	for (int i = 1; i < n / 2; ++i)
		roots[i] = roots[i - 1] * step;

	rev.resize(n);
	rev[0] = 0;

	for (int i = 1; i < n; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
}

inline void fft(vector<C> &a, bool invert)
{
	const int n = (int)a.size();

	for (int i = 0; i < n; ++i) {
		int j = rev[i];
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		const int step = n / len;
		const int half = len >> 1;

		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < half; ++j) {
				C w = roots[j * step];

				if (invert)
					w.i = -w.i;

				C u = a[i + j];
				C v = a[i + j + half] * w;

				a[i + j] = u + v;
				a[i + j + half] = u - v;
			}
		}
	}

	if (invert) {
		const double inv_n = 1.0 / n;

		for (C &x : a) {
			x.r *= inv_n;
			x.i *= inv_n;
		}
	}
}

struct FastInput {
	static constexpr int SZ = 1 << 16;

	char buf[SZ];
	int pos = 0, len = 0;

	inline char get()
	{
		if (pos == len) {
			len = fread(buf, 1, SZ, stdin);
			pos = 0;
			if (!len)
				return 0;
		}
		return buf[pos++];
	}

	inline int nextInt()
	{
		char c;
		do {
			c = get();
		} while (c <= ' ');

		int x = 0;

		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = get();
		}

		return x;
	}
};

struct FastOutput {
	static constexpr int SZ = 1 << 16;

	char buf[SZ];
	int pos = 0;

	~FastOutput()
	{
		flush();
	}

	inline void flush()
	{
		if (pos) {
			fwrite(buf, 1, pos, stdout);
			pos = 0;
		}
	}

	inline void put(char c)
	{
		if (pos == SZ)
			flush();

		buf[pos++] = c;
	}

	inline void writeLongLong(ll x)
	{
		if (x == 0) {
			put('0');
			return;
		}

		char s[24];
		int len = 0;

		if (x < 0) {
			put('-');
			x = -x;
		}

		while (x) {
			s[len++] = char('0' + x % 10);
			x /= 10;
		}

		while (len--)
			put(s[len]);
	}
};

int main()
{
	FastInput in;
	FastOutput out;

	const int n = in.nextInt();

	vector<int> A(n);
	for (int &x : A)
		x = in.nextInt();

	const int m = in.nextInt();

	const int need = n + m - 1;

	int sz = 1;
	while (sz < need)
		sz <<= 1;

	init_fft(sz);

	vector<C> c(sz);

	// Pack A + iB
	for (int i = 0; i < n; ++i)
		c[i].r = A[i];

	for (int i = 0; i < m; ++i)
		c[i].i = in.nextInt();

	fft(c, false);

	/*
        c[k] = FA[k] + i FB[k]

        For j = -k mod N:
            FA[k] = (F[k] + conj(F[j])) / 2
            FB[k] = (F[k] - conj(F[j])) / (2i)

        Process k and j together so we do NOT need:
            vector<C> f = c;
    */
	for (int k = 0; k <= sz / 2; ++k) {
		int j = (sz - k) & (sz - 1);

		C x = c[k];
		C y = c[j];

		C cy = conj(y);
		C cx = conj(x);

		// FFT(A), FFT(B) at k
		C ak = (x + cy) * 0.5;
		C bk = (x - cy);

		// (x - conj(y)) / (2i) = -(i/2)(...)
		double br = bk.i * 0.5;
		double bi = -bk.r * 0.5;

		bk = C(br, bi);

		C pk = ak * bk;

		if (k == j) {
			c[k] = pk;
			continue;
		}

		// FFT(A), FFT(B) at j
		C aj = (y + cx) * 0.5;
		C bj = (y - cx);

		double jr = bj.i * 0.5;
		double ji = -bj.r * 0.5;

		bj = C(jr, ji);

		C pj = aj * bj;

		c[k] = pk;
		c[j] = pj;
	}

	fft(c, true);

	for (int i = 0; i < need; ++i) {
		if (i)
			out.put(' ');

		out.writeLongLong(llround(c[i].r));
	}

	out.put('\n');
}
