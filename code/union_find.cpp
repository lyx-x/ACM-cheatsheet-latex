for (int i = 0; i < N; i++)  
    id[i] = i;
for (int i = 0; i < N; i++)  
    sz[i] = 1;

int find(int p)  
{  
    while (p != id[p])  
    {  //set the father of p as its grandfather  
        id[p] = id[id[p]];  
        p = id[p];  
    }  
    return p;  
}  
void union(int p, int q)  
{  
    int i = find(p);  
    int j = find(q);  
    if (i == j) return;  
    //make the smallest tree as the sub tree 
    if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }  
    else { id[j] = i; sz[i] += sz[j]; }  
    count--;  
} 
