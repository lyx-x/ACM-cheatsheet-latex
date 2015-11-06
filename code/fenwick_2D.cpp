int n, m;
int qn;      
char q[10];
int f[MAXN][MAXN];
//add delta to value at x,y
void update(int x, int y, int delta) {
	for (int i = x; i <= n; i += (i & -i))
		for (int j = y; j <= m; j += (j & -j))
			f[i][j] += delta;
}

int getSum(int x, int y) {
	int res = 0;
	for (int i = x; i > 0; i -= (i & -i))
		for (int j = y; j > 0; j -= (j & -j))
			res += f[i][j];
	return res;
}

int getSum(int xFrom, int xTo, int yFrom, int yTo) {
	return getSum(xTo, yTo) - getSum(xTo, yFrom - 1) - getSum(xFrom - 1, yTo) + getSum(xFrom - 1, yFrom - 1);
}
