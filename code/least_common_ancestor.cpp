void dfs(int v, int par = 1) //the direct parent of v is par(except when v=par=root=1)
{
	timer++;
	tin[v] = timer;//the index

	dp[v][0] = par;//the direct parent of v
	for (int i = 1; i < MAXLOG; i++) 
		dp[v][i] = dp[dp[v][i - 1]][i - 1];//the ith parent of v
	
	//update all childrens of v
	for (int i = 0; i < (int) g[v].size(); i++) {
		int to = g[v][i];
		if (to != par)
			dfs(to, v);
	}

	timer++;
	tout[v] = timer;
}

//if a is an ancestor of b
bool isParent(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

//return the least commom ancestor of a,b
int lca(int a, int b) {
	if (isParent(a, b))
		return a;
	if (isParent(b, a))
		return b;
	for (int i = MAXLOG - 1; i >= 0; i--) { 
		if (!isParent(dp[a][i], b))
			a = dp[a][i];
	}
	return dp[a][0];
}
