#include <bits/stdc++.h>
using namespace std;

const int MAXK = 10005; // max numbered cells (n*m <= 10000)

struct Orient {
	int top, bottom, north, south, west, east;
	bool operator<(Orient const &o) const
	{
		if (top != o.top)
			return top < o.top;
		if (bottom != o.bottom)
			return bottom < o.bottom;
		if (north != o.north)
			return north < o.north;
		if (south != o.south)
			return south < o.south;
		if (west != o.west)
			return west < o.west;
		return east < o.east;
	}
	bool operator==(Orient const &o) const
	{
		return top == o.top && bottom == o.bottom && north == o.north && south == o.south && west == o.west &&
		       east == o.east;
	}
};

Orient roll_north(const Orient &o)
{
	return { o.south, o.north, o.top, o.bottom, o.west, o.east };
}
Orient roll_south(const Orient &o)
{
	return { o.north, o.south, o.bottom, o.top, o.west, o.east };
}
Orient roll_east(const Orient &o)
{
	return { o.west, o.east, o.north, o.south, o.bottom, o.top };
}
Orient roll_west(const Orient &o)
{
	return { o.east, o.west, o.north, o.south, o.top, o.bottom };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	if (!(cin >> n >> m))
		return 0;
	vector<string> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	vector<vector<int> > cellIndex(n, vector<int>(m, -1));
	int K = 0;
	pair<int, int> startCell = { -1, -1 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] >= '1' && a[i][j] <= '6') {
				cellIndex[i][j] = K++;
			}
			if (a[i][j] == 's')
				startCell = { i, j };
		}
	}

	// generate orientations
	Orient base{ 1, 6, 2, 5, 3, 4 };
	vector<Orient> orients;
	map<tuple<int, int, int, int, int, int>, int> orientId;
	queue<Orient> q;
	q.push(base);
	while (!q.empty()) {
		Orient o = q.front();
		q.pop();
		auto key = make_tuple(o.top, o.bottom, o.north, o.south, o.west, o.east);
		if (orientId.count(key))
			continue;
		int id = orients.size();
		orients.push_back(o);
		orientId[key] = id;
		q.push(roll_north(o));
		q.push(roll_south(o));
		q.push(roll_east(o));
		q.push(roll_west(o));
	}
	int O = orients.size(); // should be 24
	//
	cerr << "O=" << O << "\n";
	for (int i = 0; i < O; ++i) {
		auto &o = orients[i];
		cerr << i << ": top=" << o.top << " bottom=" << o.bottom << " north=" << o.north << " south=" << o.south
		     << " west=" << o.west << " east=" << o.east << "\n";
	}
	cerr << "startCell=" << startCell.first << "," << startCell.second << "\n";

	vector<array<int, 4> > trans(O);
	for (int i = 0; i < O; i++) {
		Orient o = orients[i];
		Orient on = roll_north(o);
		Orient os = roll_south(o);
		Orient oe = roll_east(o);
		Orient ow = roll_west(o);
		trans[i][0] = orientId[make_tuple(on.top, on.bottom, on.north, on.south, on.west, on.east)];
		trans[i][1] = orientId[make_tuple(os.top, os.bottom, os.north, os.south, os.west, os.east)];
		trans[i][2] = orientId[make_tuple(oe.top, oe.bottom, oe.north, oe.south, oe.west, oe.east)];
		trans[i][3] = orientId[make_tuple(ow.top, ow.bottom, ow.north, ow.south, ow.west, ow.east)];
	}

	// find start orientation robustly by scanning the generated orientations
	int startOrient = -1;
	for (int i = 0; i < O; i++) {
		Orient &o = orients[i];
		if (o.top == 6 && o.north == 4 && o.west == 2) {
			startOrient = i;
			break;
		}
	}
	// fallback to tuple lookup (very unlikely needed)
	if (startOrient == -1) {
		auto keyStart = make_tuple(6, 1, 4, 3, 2, 5);
		if (orientId.count(keyStart))
			startOrient = orientId[keyStart];
	}
	if (startOrient == -1) {
		cerr << "start orientation not found\n";
		return 0;
	}

	int totalNodes = n * m * O;
	auto nodeId = [&](int r, int c, int o) { return (r * m + c) * O + o; };

	vector<vector<int> > g(totalNodes);
	vector<char> isObstacle(n * m, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (a[i][j] == 'x')
				isObstacle[i * m + j] = 1;
	int dr[4] = { -1, 1, 0, 0 }, dc[4] = { 0, 0, 1, -1 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (isObstacle[i * m + j])
				continue;
			for (int o = 0; o < O; o++) {
				int u = nodeId(i, j, o);
				for (int d = 0; d < 4; d++) {
					int ni = i + dr[d], nj = j + dc[d];
					if (ni < 0 || ni >= n || nj < 0 || nj >= m)
						continue;
					if (isObstacle[ni * m + nj])
						continue;
					int no = trans[o][d];
					int v = nodeId(ni, nj, no);
					g[u].push_back(v);
				}
			}
		}
	}

	vector<int> nodeCell(totalNodes, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (isObstacle[i * m + j])
				continue;
			if (cellIndex[i][j] == -1)
				continue;
			int want = a[i][j] - '0';
			for (int o = 0; o < O; o++) {
				Orient &orv = orients[o];
				if (orv.top == want) {
					nodeCell[nodeId(i, j, o)] = cellIndex[i][j];
				}
			}
		}
	}

	// Tarjan
	vector<int> disc(totalNodes, -1), low(totalNodes), inSt(totalNodes, 0), comp(totalNodes, -1);
	vector<int> st;
	int timeD = 0, compCnt = 0;
	function<void(int)> dfs = [&](int u) {
		disc[u] = low[u] = timeD++;
		st.push_back(u);
		inSt[u] = 1;
		for (int v : g[u]) {
			if (disc[v] == -1) {
				dfs(v);
				low[u] = min(low[u], low[v]);
			} else if (inSt[v]) {
				low[u] = min(low[u], disc[v]);
			}
		}
		if (low[u] == disc[u]) {
			while (true) {
				int v = st.back();
				st.pop_back();
				inSt[v] = 0;
				comp[v] = compCnt;
				if (v == u)
					break;
			}
			compCnt++;
		}
	};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (isObstacle[i * m + j])
				continue;
			for (int o = 0; o < O; o++) {
				int id = nodeId(i, j, o);
				if (disc[id] == -1)
					dfs(id);
			}
		}
	}

	vector<vector<int> > dag;
	dag.assign(compCnt, {});
	vector<bitset<MAXK> > own(compCnt);
	for (int u = 0; u < totalNodes; u++) {
		int cellIdx = (u / O);
		if (isObstacle[cellIdx])
			continue;
		int cu = comp[u];
		if (nodeCell[u] != -1) {
			own[cu].set(nodeCell[u]);
		}
		for (int v : g[u]) {
			int cv = comp[v];
			if (cu != cv)
				dag[cu].push_back(cv);
		}
	}
	for (int i = 0; i < compCnt; i++) {
		sort(dag[i].begin(), dag[i].end());
		dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
	}

	vector<int> indeg(compCnt, 0);
	for (int u = 0; u < compCnt; u++)
		for (int v : dag[u])
			indeg[v]++;
	queue<int> q2;
	for (int i = 0; i < compCnt; i++)
		if (indeg[i] == 0)
			q2.push(i);
	vector<int> topo;
	while (!q2.empty()) {
		int u = q2.front();
		q2.pop();
		topo.push_back(u);
		for (int v : dag[u])
			if (--indeg[v] == 0)
				q2.push(v);
	}

	vector<bitset<MAXK> > dp(compCnt);
	for (int idx = (int)topo.size() - 1; idx >= 0; --idx) {
		int u = topo[idx];
		bitset<MAXK> best;
		for (int v : dag[u]) {
			bitset<MAXK> tmp = dp[v];
			tmp |= own[u];
			if (tmp.count() > (best | own[u]).count()) {
				best = dp[v];
			}
		}
		dp[u] = own[u];
		dp[u] |= best;
	}

	int sr = startCell.first, sc = startCell.second;
	int startNode = nodeId(sr, sc, startOrient);
	int startComp = comp[startNode];
	cout << dp[startComp].count() << "\n";
	return 0;
}
