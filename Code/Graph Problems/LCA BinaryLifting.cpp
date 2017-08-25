//LCA With Binary Lifting

/* USAGE

    Pass in and adjList to getDepths then run fillTable
    this will make the LCA function work as well as populate the 
    depth and table matrices correctly.
    
    if you need longs somehow make that change
*/

const int MAXN = 200000;

int table[32][MAXN];//can change out 32
int depth[MAXN];
int N ,D = 0;

int walk(int i, int k)
{
    for(int j = 0; j < D and i != -1; j++)
    {
        if(k&(1 << j))
            i = table[j][i];
    }
    return i;
}

int lca(int i, int j)
{
    int l= i, r = j;
    int ld = depth[i], rd = depth[j];
    if(ld > rd) l = walk(i, ld-rd);
    else if(rd > ld) r = walk(j, rd-ld);
    if(l == r) return l;
    for(int d = D; d >= 0; d--)
    {
        if(table[d][l] != table[d][r] and table[d][l] != -1)
        {
            l = table[d][l];
            r = table[d][r];
        }
    }
    return table[0][r];
}

void getDepths(vector<vector<int> > &al, int root)
{
    bool vis[(int)al.size()];
    memset(table, -1, sizeof table);
    memset(vis, false, sizeof vis);//if graph is not already rooted then this is needed
    depth[root] = 0;
    queue<int> q;
    q.push(root);
    int mx = 0;
    vis[root] = 1;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int i = 0; i <(int) al[u].size(); i++)
        {
            int v = al[u][i];
            if(!vis[v])
            {
                vis[v] = 1;
                table[0][v] = u;
                depth[v] = depth[u]+1;
                mx = max(mx, depth[v]);
                q.push(v);
            }
        }
    }
    while((1 << D) < mx and D != 31)D++;
}

void fillTable()
{
    for(int k = 1; k < D; k++)//this can be lowered as needed
    {
        for(int i = 0; i < N;i++)
        {
            int mid = table[k-1][i];
            if(mid != -1)
                table[k][i] = table[k-1][mid];
        }
    }
}

