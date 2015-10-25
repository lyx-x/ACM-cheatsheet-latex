/*input:a matrix of graph g
output:the cost of the min-covered-tree*/
void prime(){
    added[0]=true;
    int next_vertex;
    //we have n-1 vertexs to add
    int total_cost = 0;
    for (int i=1;i<n;i++){
        next_vertex=1;
        int min_cost;
        //find next vertex to be added
        for (int j=0;j<n;j++){
            if (!added[j] && distance_to_tree[j]<distance_to_tree[min]){
                next_vertex=j;
                min_cost = distance_to_tree[j];
            }
        }
        //add the new edge to the tree
        edge[i] = Edge(closed_vertex[next_vertex],next_vertex);
        total_cost += min_cost; 
        distance_to_tree[next_vertex] = Max_INT;
        for (int j=0;j<n;j++){
            if (!added[j] && g[next_vertex][j]<distance_to_tree[j]){
                distance_to_tree[j]=g[next_vertex][j];
                closed_vertex[j] = next_vertex;
            }
        }

    }
}
