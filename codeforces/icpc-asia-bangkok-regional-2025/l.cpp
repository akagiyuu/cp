#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = (ll)9e18;

struct Point {
	ll x, y, cost;
	int id;
};
struct Node {
	Point p;
	int l = -1, r = -1;
	ll mnx, mxx, mny, mxy;
	ll min_cost;
};

vector<Point> pts;
vector<Node> tree;

bool cmp_axis(int axis, const Point &a, const Point &b)
{
	if (axis == 0)
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}

int build(int L, int R, int axis)
{
	if (L > R)
		return -1;
	int M = (L + R) / 2;
	nth_element(pts.begin() + L, pts.begin() + M, pts.begin() + R + 1,
		    [&](const Point &a, const Point &b) { return cmp_axis(axis, a, b); });
	Node node;
	node.p = pts[M];
	node.l = build(L, M - 1, axis ^ 1);
	node.r = build(M + 1, R, axis ^ 1);

	node.mnx = node.mxx = node.p.x;
	node.mny = node.mxy = node.p.y;
	node.min_cost = node.p.cost;

	if (node.l != -1) {
		node.mnx = min(node.mnx, tree[node.l].mnx);
		node.mxx = max(node.mxx, tree[node.l].mxx);
		node.mny = min(node.mny, tree[node.l].mny);
		node.mxy = max(node.mxy, tree[node.l].mxy);
		node.min_cost = min(node.min_cost, tree[node.l].min_cost);
	}
	if (node.r != -1) {
		node.mnx = min(node.mnx, tree[node.r].mnx);
		node.mxx = max(node.mxx, tree[node.r].mxx);
		node.mny = min(node.mny, tree[node.r].mny);
		node.mxy = max(node.mxy, tree[node.r].mxy);
		node.min_cost = min(node.min_cost, tree[node.r].min_cost);
	}

	tree.push_back(node);
	return (int)tree.size() - 1;
}

inline ll pointValue(const Point &p, ll qx, ll qy, ll A, ll B)
{
	return A * llabs(p.x - qx) + B * llabs(p.y - qy) + p.cost;
}

inline ll boxLowerBound(const Node &nd, ll qx, ll qy, ll A, ll B)
{
	ll d = 0;
	if (qx < nd.mnx)
		d += A * (nd.mnx - qx);
	else if (qx > nd.mxx)
		d += A * (qx - nd.mxx);
	if (qy < nd.mny)
		d += B * (nd.mny - qy);
	else if (qy > nd.mxy)
		d += B * (qy - nd.mxy);
	return d + nd.min_cost; // add subtree min cost as extra lower bound
}

void query_rec(int idx, ll qx, ll qy, ll A, ll B, ll &bestVal, int &bestId)
{
	if (idx == -1)
		return;
	const Node &nd = tree[idx];
	ll val = pointValue(nd.p, qx, qy, A, B);
	if (val < bestVal || (val == bestVal && nd.p.id < bestId)) {
		bestVal = val;
		bestId = nd.p.id;
	}
	ll dl = (nd.l == -1 ? INF : boxLowerBound(tree[nd.l], qx, qy, A, B));
	ll dr = (nd.r == -1 ? INF : boxLowerBound(tree[nd.r], qx, qy, A, B));

	if (dl < dr) {
		if (dl <= bestVal)
			query_rec(nd.l, qx, qy, A, B, bestVal, bestId);
		if (dr <= bestVal)
			query_rec(nd.r, qx, qy, A, B, bestVal, bestId);
	} else {
		if (dr <= bestVal)
			query_rec(nd.r, qx, qy, A, B, bestVal, bestId);
		if (dl <= bestVal)
			query_rec(nd.l, qx, qy, A, B, bestVal, bestId);
	}
}

void solve()
{
	int n, q, a, b;
	cin >> n >> q >> a >> b;
	pts.resize(n);
	for (int i = 0; i < n; ++i) {
		ll x, y, c;
		cin >> x >> y >> c; // input: x y cost
		pts[i] = { x, y, c, i + 1 };
	}
	tree.reserve(n);
	int root = build(0, n - 1, 0);

	while (q--) {
		ll X, Y;
		cin >> X >> Y;
		ll bestVal = INF;
		int bestId = INT_MAX;
		query_rec(root, X, Y, a, b, bestVal, bestId);
		cout << bestVal << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
