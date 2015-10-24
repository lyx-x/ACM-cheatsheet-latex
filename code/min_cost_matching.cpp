/* Min cost bipartite matching via shortest augmenting paths
 *
 * This is an O(n^3) implementation of a shortest augmenting path
 * algorithm for finding min cost perfect matchings in dense
 * graphs.	In practice, it solves 1000x1000 problems in around 1
 * second.
 *
 *	 cost[i][j] = cost for pairing left node i with right node j
 *	 Lmate[i] = index of right node that left node i pairs with
 *	 Rmate[j] = index of left node that right node j pairs with
 *
 * The values in cost[i][j] may be positive or negative. To perform 
 * maximization, simply negate the cost[][] matrix. */

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

double MinCostMatching(const vector<vector<double>> &cost, 
    vector<int> &Lmate, vector<int> &Rmate) {
	int n = int(cost.size());

	// construct dual feasible solution
	vector<double> u(n);
	vector<double> v(n);
	for (int i = 0; i < n; i++) {
		u[i] = cost[i][0];
		for (int j = 1; j < n; j++) u[i] = min(u[i], cost[i][j]);
	}
	for (int j = 0; j < n; j++) {
		v[j] = cost[0][j] - u[0];
		for (int i = 1; i < n; i++) v[j] = min(v[j], cost[i][j] - u[i]);
	}
	
	// construct primal solution satisfying complementary slackness
	Lmate = vector<int>(n, -1);
	Rmate = vector<int>(n, -1);
	int mated = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (Rmate[j] != -1) continue;
			if (fabs(cost[i][j] - u[i] - v[j]) < 1e-10) {
				Lmate[i] = j;
				Rmate[j] = i;
				mated++;
				break;
			}
		}
	
	vector<double> distance(n);
	vector<int> parent(n);
	vector<int> visited(n);
	
	// repeat until primal solution is feasible
	while (mated < n) {
		
		// find an unmatched left node
		int s = 0;
		while (Lmate[s] != -1) s++;
		
		// initialize Dijkstra
		fill(parent.begin(), parent.end(), -1);
		fill(visited.begin(), visited.end(), 0);
		for (int k = 0; k < n; k++) 
			distance[k] = cost[s][k] - u[s] - v[k];
		
		int j = 0;
		while (true) {
			
			// find closest
			j = -1;
			for (int k = 0; k < n; k++) {
				if (visited[k]) continue;
				if (j == -1 || distance[k] < distance[j]) j = k;
						}
						visited[j] = 1;
						
						// termination condition
						if (Rmate[j] == -1) break;
						
						// relax neighbors
						const int i = Rmate[j];
						for (int k = 0; k < n; k++) {
				if (visited[k]) continue;
				const double new_dist = distance[j] + cost[i][k] - u[i] - v[k];
				if (distance[k] > new_dist) {
					distance[k] = new_dist;
					parent[k] = j;
				}
			}
		}
		
		// update dual variables
		for (int k = 0; k < n; k++) {
			if (k == j || !visited[k]) continue;
			const int i = Rmate[k];
			v[k] += distance[k] - distance[j];
			u[i] -= distance[k] - distance[j];
		}
		u[s] += distance[j];
		
		// augment along path
		while (parent[j] >= 0) {
			const int d = parent[j];
			Rmate[j] = Rmate[d];
			Lmate[Rmate[j]] = j;
			j = d;
		}
		Rmate[j] = s;
		Lmate[s] = j;
		
		mated++;
	}
	
	double value = 0;
	for (int i = 0; i < n; i++)
		value += cost[i][Lmate[i]];
	
	return value;
}