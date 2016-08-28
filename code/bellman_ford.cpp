//vs start point, prev[]:previous point, dist[] distance minimum
void dijkstra(int vs, int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    bool flag[MAX];      // flag[i]=true:already treated

    for (i = 0; i < VexNum; i++)
    {	flag[i] = false;            
        prev[i] = 0;         
        dist[i] = graph[vs][i];
    }

    flag[vs] = true;
    dist[vs] = 0;

    for (i = 1; i < VexNum; i++)
    {	//find the nearest point of the start among all points non-visited
        min = INF;
        for (j = 0; j < mVexNum; j++)
        {
            if (!flag[j] && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        flag[k] = true;

        for (j = 0; j < mVexNum; j++)
        {
            tmp = (graph[k][j]==INF ? INF : (min + graph[k][j]));
            if (!flag[j] && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
}
