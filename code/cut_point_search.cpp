int n, m;
vector <int> g[MAXN];
int tin[MAXN], mn[MAXN];
bool used[MAXN];
vector <int> cutVertices;
int timer;

void dfs(int v, int par = -1) {
	used[v] = true;
	timer++;
	tin[v] = timer;
	mn[v] = tin[v];

	int childNum = 0;
	bool isCutVertex = false;

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (!used[to]) {
			childNum++;
			dfs(to, v);
			if (par != -1 && mn[to] >= tin[v] && !isCutVertex) {	
				isCutVertex = true;
				cutVertices.push_back(v);
			}
			mn[v] = min(mn[v], mn[to]);
		}
		else if (to != par) {
			mn[v] = min(mn[v], tin[to]);
		}
	}

	if (par == -1 && childNum > 1)
		cutVertices.push_back(v);
}
