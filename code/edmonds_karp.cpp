void bfs(){
	memset(a,0,sizeof(a));
       a[s]=INF;
       q.push(s);
       while(!q.empty())
       {
           int u=q.front(); q.pop();
           for(int v=0;v<n;++v)
           {
               if(!a[v]&&cap[u][v]-flow[u][v]>0)
               {
                  p[v]=u;
                  a[v]=(cap[u][v]-flow[u][v])<a[u] ? (cap[u][v]-flow[u][v]):a[u];
                  q.push(v);
               }
           }
       }
}

void EdmondsKarp()
{
   cin>>s>>t;
   queue<int> q;
   memset(flow,0,sizeof(flow));
   f=0;
   for(;;)
   {
       bfs();
       //if there is no augmenting path, print the min cut
       if(!a[t])
       {
           cout<<"\n\n min cuts S:";
           for(int i=0;i<n;++i)
           {
               if(a[i])
               {
                   cout<<i<<",";
               }
           }
           cout<<"\n min cut T:";
           for(int j=0;j<n;++j)
           {
               if(!a[j])
               {
                   cout<<j<<",";
               }
           }
           cout<<"\n max flow:"<<f<<endl;
           break;
       }
       for(int u=t;u!=s;u=p[u])
       {
           flow[p[u]][u]+=a[t];
           flow[u][p[u]]-=a[t];
       }
       //maxflow increase through the augmenting path:
       f+=a[t];
   }
}
