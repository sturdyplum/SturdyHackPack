/*
  Centroid Decomp Tree, taken from geeksforgeeks
  Usage, create tree using addEdge then decompose it by runing
  decompose tree, this creates a new tree of centroids.
  
  The boolean removeCentroidEdges will remove edges so that dfs can be done safely.
  What this means is that is you are on tree with centroid A, then you move on to its subtree with centroid
  B, a dfs could then renter the tree with centroid A, which is undesirable as this woud lead to over counting and
  TLE. This removes the edge that would allow the subtree of B to renter the A tree so that dfs can be safely made. 

*/

#define MAXN 100010

set<int> tree[MAXN];
vector<int> centroidTree[MAXN];
bool centroidMarked[MAXN];
bool removeCentroidEdges = true;// Use this if you want it so that you can dfs without going into an old tree
void addEdge(int u, int v)
{
    tree[u].insert(v);
    tree[v].insert(u);
}

/* method to setup subtree sizes and nodes in current tree */
void DFS(int src, bool visited[], int subtree_size[], int* n)
{
    visited[src] = true;
    *n += 1;
    subtree_size[src] = 1;

    set<int>::iterator it;
    for (it = tree[src].begin(); it!=tree[src].end(); it++)
        if (!visited[*it] && !centroidMarked[*it])
        {
            DFS(*it, visited, subtree_size, n);
            subtree_size[src]+=subtree_size[*it];
        }
}

int getCentroid(int src, bool visited[], int subtree_size[], int n)
{
    bool is_centroid = true;
    visited[src] = true;
    int heaviest_child = 0;

    set<int>::iterator it;
    for (it = tree[src].begin(); it!=tree[src].end(); it++)
        if (!visited[*it] && !centroidMarked[*it])
        {
            if (subtree_size[*it]>n/2)
                is_centroid=false;
            if (heaviest_child==0 ||
                subtree_size[*it]>subtree_size[heaviest_child])
                heaviest_child = *it;
        }

    if (is_centroid && n-subtree_size[src]<=n/2)
        return src;
    return getCentroid(heaviest_child, visited, subtree_size, n);
}

int getCentroid(int src)
{
    bool visited[MAXN];
    int subtree_size[MAXN];

    memset(visited, false, sizeof visited);
    memset(subtree_size, 0, sizeof subtree_size);
    int n = 0;
    DFS(src, visited, subtree_size, &n);
    for (int i=1; i<MAXN; i++)
        visited[i] = false;

    int centroid = getCentroid(src, visited, subtree_size, n);
    centroidMarked[centroid]=true;
    return centroid;
}

int decomposeTree(int root)
{
    int cend_tree = getCentroid(root);
    set<int>::iterator it;

    for (it=tree[cend_tree].begin(); it!=tree[cend_tree].end(); it++)
    {
        if (!centroidMarked[*it])
        {
            if(removeCentroidEdges)tree[*it].erase(cend_tree);
            int cend_subtree = decomposeTree(*it);
            centroidTree[cend_tree].push_back(cend_subtree);
            centroidTree[cend_subtree].push_back(cend_tree);
        }
    }
     return cend_tree;
}
