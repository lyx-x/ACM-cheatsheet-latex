struct edge_t {
    int from, to, c, f;
    edge_t(int from, int to, int c): from(from), to(to), c(c), f(0) {}
};
 
struct scaling_t {
 
    int init_flow = 1;
 
    vector<vector<int> > g;
    vector<edge_t> edges;
 
    vector<int> visited;
 
    scaling_t(int V): g(V), visited(V) {} // constructor
 
    void add_edge(int from, int to, int c) {
        g[from].push_back(edges.size());
        edges.push_back(edge_t(from, to, c));
        if (c > init_flow)
            init_flow <<= 1;
        g[to].push_back(edges.size());
        edges.push_back(edge_t(to, from, 0));
    }
 
    bool augment(int v, int t, int flow) {
        if (v == t)
            return true;
        if (visited[v])
            return false;
        visited[v] = true;
        for (int i: g[v]) {
            edge_t& e = edges[i];
            if (e.c - e.f >= flow && augment(e.to, t, flow)) {
                e.f += flow;
                edges[i ^ 1].f -= flow;
                return true;
            }
        }
        return false;
    }
 
    int maxflow(int s, int t) {
        int flow = init_flow;
        int ans = 0;
        while (flow > 0) {
            fill(visited.begin(), visited.end(), false);
            if (augment(s, t, flow))
                ans += flow;
            else
                flow /= 2;
        }
        return ans;
    }
 
    void print() {
        for (edge_t e: edges) {
            cout << e.from << ' ' << e.to << ' ' << e.f << ' ' << e.c << endl;
        }
    }
 
};