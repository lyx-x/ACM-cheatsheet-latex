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
                   a[v]= (cap[u][v]-flow[u][v]) < a[u] ?  (cap[u][v]-flow[u][v]) : a[u];
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
       //没有增广路,算法结束,打印最小割
       if(!a[t])
       {
           cout<<"\n\n最小割集S:";
           for(int i=0;i<n;++i)
           {
               if(a[i])
               {
                   cout<<i<<",";
               }
           }
           cout<<"\n最小割集T:";
           for(int j=0;j<n;++j)
           {
               if(!a[j])
               {
                   cout<<j<<",";
               }
           }
           cout<<"\n最大流:"<<f<<endl;
           break;
       }
       for(int u=t;u!=s;u=p[u])
       {
           flow[p[u]][u]+=a[t];
           flow[u][p[u]]-=a[t];
       }
       //这条增广路给最大流增加了:
       f+=a[t];
   }
}
