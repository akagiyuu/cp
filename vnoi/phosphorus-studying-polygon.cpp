#include <bits/stdc++.h>

using namespace std;

#define int long long

const double PI = acos(-1);
const double EPS = 1e-4;

typedef complex<double> P;
typedef vector<P> G;

double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
bool intersect(double l1, double r1, double l2, double r2)
{
	return l1 <= r2 + EPS && l2 <= r1 + EPS;
}
bool _intersect(const G &g1, const G &g2)
{
	int n = g1.size();
	int m = g2.size();

	for (int i = 0; i < n; i++) {
		P dir = g1[(i + 1) % n] - g1[i];
		P norm(dir.imag(), -dir.real());
		norm /= abs(norm);

		double l1, r1;
		l1 = r1 = dot(g1[0], norm);
		for (int i = 1; i < n; i++) {
			double cur = dot(g1[i], norm);
			l1 = min(l1, cur);
			r1 = max(r1, cur);
		}

		double l2, r2;
		l2 = r2 = dot(g2[0], norm);
		for (int i = 1; i < m; i++) {
			double cur = dot(g2[i], norm);
			l2 = min(l2, cur);
			r2 = max(r2, cur);
		}
		if (!intersect(l1, r1, l2, r2))
			return false;
	}
	return true;
}
bool intersect(const G &g1, const G &g2)
{
	return _intersect(g1, g2) && _intersect(g2, g1);
}

struct Polygon {
	int id;
	P center, rotation;
	G pts;
	double r, k, area;
	double x1, x2, y1, y2;

	Polygon()
	{
	}
	Polygon(int _id, int _x, int _y, int _r, int _k)
	{
		double angle = 2. * PI / (double)_k;
		double c = cos(angle);
		double s = sin(angle);

		id = _id;
		center = P(_x, _y);
		r = _r;
		k = _k;
		rotation = P(c, s);
		area = 0.5 * k * r * r * s;

		pts.resize(k);
		P p(0, r);

		pts[0] = center + p;
		x1 = x2 = pts[0].real();
		y1 = y2 = pts[0].imag();
		for (int i = 1; i < k; i++) {
			p = p * rotation;
			pts[i] = center + p;
			x1 = min(x1, pts[i].real());
			x2 = max(x2, pts[i].real());
			y1 = min(y1, pts[i].imag());
			y2 = max(y2, pts[i].imag());
		}
	}
};
struct Node {
	double x1, x2, y1, y2, max_area;
	int id;
	Node()
	{
	}
	Node(double _x1, double _x2, double _y1, double _y2, double _max_area, int _id = -1)
	{
		x1 = _x1;
		x2 = _x2;
		y1 = _y1;
		y2 = _y2;
		max_area = _max_area;
		id = _id;
	}
};
bool operator<(const Node &a, const Node &b)
{
	return a.max_area < b.max_area;
}

Node merge(const Node &a, const Node &b)
{
	double x1 = min(a.x1, b.x1);
	double x2 = max(a.x2, b.x2);
	double y1 = min(a.y1, b.y1);
	double y2 = max(a.y2, b.y2);
	auto max_area = max(a.max_area, b.max_area);
	return Node(x1, x2, y1, y2, max_area);
}
struct Tree {
	int n;
	vector<Node> tree;

	Tree(vector<Polygon> a)
	{
		n = a.size();
		tree.resize(4 * n);
		build(1, 0, n - 1, a);
	}
	void build(int id, int l, int r, vector<Polygon> &a)
	{
		if (l == r) {
			tree[id] = Node(a[l].x1, a[l].x2, a[l].y1, a[l].y2, a[l].area, a[l].id);
			return;
		}
		int mid = (l + r) / 2;
		build(2 * id, l, mid, a);
		build(2 * id + 1, mid + 1, r, a);
		tree[id] = merge(tree[2 * id], tree[2 * id + 1]);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<Polygon> a(n);
	for (int i = 0; i < n; i++) {
		int x, y, r, k;
		cin >> x >> y >> r >> k;
		a[i] = Polygon(i, x, y, r, k);
	}
	vector<Polygon> sorted_a = a;
	sort(sorted_a.begin(), sorted_a.end(),
	     [](const Polygon &a, const Polygon &b) { return a.center.real() < b.center.real(); });
	Tree t(sorted_a);
	while (q--) {
		int u;
		cin >> u;
		u--;
		Polygon poly = a[u];
		int res = u;
		priority_queue<pair<Node, int> > pq;
		pq.push({ t.tree[1], 1 });
		while (!pq.empty()) {
			auto [cur, tid] = pq.top();
			pq.pop();
			if (!intersect(cur.x1, cur.x2, poly.x1, poly.x2) ||
			    !intersect(cur.y1, cur.y2, poly.y1, poly.y2))
				continue;
			if (cur.max_area < a[res].area)
				continue;
			if (cur.id == -1) {
				pq.push({ t.tree[2 * tid], 2 * tid });
				pq.push({ t.tree[2 * tid + 1], 2 * tid + 1 });
				continue;
			}
			if (!intersect(a[cur.id].pts, poly.pts))
				continue;
			if (a[cur.id].area > a[res].area)
				res = cur.id;
			else if (a[cur.id].area == a[res].area)
				res = min(res, cur.id);
		}
		cout << res + 1 << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
