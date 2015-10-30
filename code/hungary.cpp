bool dfs(int u)//find augmenting path from the left
{
    int v;
    for(v=0;v<vN;v++)//try all points on the right
	{
		if(g[u][v]&&!used[v])
		{
			used[v]=true;
			//if fint the augmenting path
			if(link[v]==-1 || dfs(link[v]))
			{
				link[v]=u;
				return true;
			}
		}
	}
    return false;
}
int hungary()
{
    int res=0;
    int i,u;
    memset(link,-1,sizeof(link));
    for(u=0;u<uN;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u)) 
	res++;
    }
    return res;
} 
