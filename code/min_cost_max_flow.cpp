using namespace std;

const int MAXN = 1050;
const long long INF = (long long) 1e15;

struct edge {
	int from, to;
	int flow, cap;
	long long cost;
};

int n;
int cost[MAXN][MAXN];
vector <edge> e;
vector <int> g[MAXN];
long long phi[MAXN];
long long dist[MAXN];
bool used[MAXN];
int par[MAXN];
int edge_num;
int s = 0, t = MAXN - 1;

void fordBellman() {
	for (int i = s; i <= t; i++) 
		dist[i] = INF;
	dist[s] = 0;
	while (true) {
		bool change = false;
		for (int i = 0; i < edge_num; i++) {
			int from = e[i].from, to = e[i].to;
			if (e[i].flow == e[i].cap)
				continue;
			if (dist[from] == INF)
				continue;
			if (dist[to] > dist[from] + e[i].cost) {
				dist[to] = dist[from] + e[i].cost;
				change = true;
			}
		}
		if (!change)
			break;
	}
}

void dijkstra() {
	for (int i = s; i <= t; i++) {
		dist[i] = INF;
		used[i] = false;
	}
	dist[s] = 0;

	for (int i = s; i <= t; i++) {
		int cur = -1;
		for (int j = s; j <= t; j++) 	
			if (!used[j])
				if (cur == -1 || dist[j] < dist[cur])
					cur = j;     

		used[cur] = true;

		for (int j = 0; j < (int) g[cur].size(); j++) {
			int ind = g[cur][j];
			if (e[ind].flow == e[ind].cap)
				continue;
			int to = e[ind].to;
			int w = e[ind].cost + phi[cur] - phi[to];
			if (dist[cur] + w < dist[to]) {
				dist[to] = dist[cur] + w;
				par[to] = ind;
			}
		}
	}
}

//flow: flow maximum
long long minCost(int flow) {
	long long result = 0;

	fordBellman();	
	for (int i = s; i <= t; i++)
		phi[i] = dist[i];

	while (true) {

		dijkstra();

		if (dist[t] == INF)
			return result;

		for (int i = s; i <= t; i++)
			phi[i] = min(phi[i] + dist[i], INF);

		int push = flow;
		int cur = t;
		while (cur != s) {
			edge tmp = e[par[cur]];
			int from = tmp.from, can_push = tmp.cap - tmp.flow;
			push = min(push, can_push);
			cur = from;
		}

		flow -= push;
		cur = t;
		while (cur != s) {
			edge tmp = e[par[cur]];
			int from = tmp.from;
			e[par[cur]].flow += push;
			e[par[cur] ^ 1].flow -= push;
			result += 1ll * push * tmp.cost;
			cur = from;
		}

		if (flow == 0)
			break;
	}
	return result;
}	

void addEdge(int from, int to, int cap, long long cost) {
	edge tmp;
	tmp.from = from; tmp.to = to; tmp.flow = 0; tmp.cap = cap; tmp.cost = cost;
	e.push_back(tmp);
	g[from].push_back(edge_num);

	tmp.from = to; tmp.to = from; tmp.flow = cap; tmp.cap = cap; tmp.cost = -cost;
	e.push_back(tmp);
	g[to].push_back(edge_num + 1);

	edge_num += 2;
}
