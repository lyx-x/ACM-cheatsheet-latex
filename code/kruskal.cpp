struct edge_t  
{  
    int u;  
    int v;  
    int weight;  
  
    edge(){}  
    edge_t(int u,int v,int w):u(u),v(v),weight(w){}  
};  
  
  
int *root;  
  
  
bool compare(edge_t a,edge_t b)  
{  
    return  a.weight < b.weight;//ÉýÐò..  
}  
  
int Find(int x)  
{  
    return root[x];  
}  
  
void Union(int a,int b,int V)  
{  
    int root_a = Find(a);  
    int root_b = Find(b);  
    if(root_a != root_b)  
    {  
        root[b] = root_a;  
        for(int i = 1 ; i <= V;i++)  
            if(root[i] == root_b)  
                root[i] = root_a;  
    }  
}  
  
void Kruskal(int V,int E,edge_t *e)  
{  
    for(int i = 1 ; i <= V;i++)  
        root[i] = i;  
  
    //order by weight in edge  
    sort(e,e+E,compare);  
  
    for(int i = 0 ; i < E;i++)  
        if(Find(e[i].u) != Find(e[i].v))  
        {  
            cout<<e[i].u<<"---"<<e[i].v<<" ";  
            Union(e[i].u,e[i].v,V);  
        }  
    cout<<endl;  
}  
