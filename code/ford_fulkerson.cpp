void SPFA(int s)//SPFA: shortest path 
{  
    queue<int> Q;  
    int u;  
    for(int i=0; i<=vertex; i++)
    {  
        dist[i]=MAX;  //distance
        pre[i]=-1;  //previous vertex
        inq[i]=0;  //if visited
    }  
    dist[s]=0;  
    Q.push(s);  
    inq[s] = 1;  
    while(!Q.empty())  
    {  
        u=Q.front();  
        Q.pop();  
        inq[u]=0;  
        for(int i=0; i<=vertex; i++)//update dist[], pre[], inq[]  
        {  
            int v=i;  
            if(G[u][v].c_f==0)     //no edge from u to v 
                continue;  
            if(G[u][v].v==MAX)  
                G[u][v].v=-G[v][u].v;  
            if(dist[v]>dist[u]+G[u][v].v)//relax  
            {  
                dist[v]=dist[u]+G[u][v].v;  
                pre[v]=u;  
                if(inq[v]==0)  
                {  
                    Q.push(v);  
                    inq[v]=1;  
                }  
            }  
        }  
    }  
}  
  
void ford_fulkerson(int s,int t)  
{  
    SPFA(s);  
    while(pre[t]!=-1)//if there is augmenting path from s to t  
    {  
        //cout<<dist[t]<<"^_^"<<endl;  
        sum+=dist[t];//add 
        min_c_f=MAX;  
        int u=pre[t], v=t;//calculate the remaining flow
        while(u!=-1)  
        {  
            if(min_c_f > G[u][v].c_f)  
                min_c_f=G[u][v].c_f;  
            v=u;  
            u=pre[v];  
        }  
        u=pre[t], v=t;  
        while(u!=-1)  
        {  
            G[u][v].f+=min_c_f; //modify the flow  
            G[v][u].f=-G[u][v].f;  
            G[u][v].c_f=G[u][v].c-G[u][v].f; //modify c_f 
            G[v][u].c_f=G[v][u].c-G[v][u].f;  
            v=u;  
            u=pre[v];  
        }  
        SPFA(s);  
    }  
} 
