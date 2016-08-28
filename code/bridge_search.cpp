void dfs(int v, int par = -1) {
	used[v] = true;
	timer++;
	//current time
	tin[v] = timer;
	//lower time of accessible vertex
	mn[v] = tin[v];

	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (!used[to]) {
			dfs(to, v);
			if (mn[to] == tin[to]) {
				bridges.push_back(ind[v][i]);
			}
			mn[v] = min(mn[v], mn[to]);
		}
		else if (to != par) {
			mn[v] = min(mn[v], mn[to]);			
		}
	}
}
