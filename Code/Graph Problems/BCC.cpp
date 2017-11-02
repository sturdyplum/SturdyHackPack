/*
  Usage:
  Create a BCC object, then call get components with an adjList. It will fill the variable components
  with all the bccs. The coponents will be given in the form of vectors of edges. To get nodes only you could
  use a set and throw in the nodes. 
*/
struct edge
{
    int u, v;
};

struct BCC{
    int cnt = 0;
    vii adjList;
    vector<int> disc, low, parent;
    vector<edge>st;
    vector<vector<edge> > components;
    void dfs(int u)
    {
        static int time = 0;
        disc[u] = low[u] = ++time;
        int children = 0;
        for (int v: adjList[u])
        {
            if (disc[v] == -1)
            {
                children++;
                parent[v] = u;
                st.push_back((edge){u,v});
                dfs(v);
                low[u]  = min(low[u], low[v]);
                if( (disc[u] == 1 && children > 1) ||(disc[u] > 1 && low[v] >= disc[u]) )
                {
                    vector<edge> new_component;
                    while(st.back().u != u || st.back().v != v)
                    {
                        new_component.push_back(st.back());
                        st.pop_back();
                    }
                    new_component.push_back(st.back());
                    st.pop_back();
                    components.push_back(new_component);
                    cnt++;
                }
            }

            else if(v != parent[u] && disc[v] < low[u])
            {
                low[u]  = min(low[u], disc[v]);
                st.push_back((edge){u,v});
            }
        }
    }

    // The function to do DFS traversal. It uses BCCUtil()
    void getComponents(vii &al)
    {
        int n = al.size();
        disc.assign(n, -1);
        low.assign(n, -1);
        parent.assign(n, -1);
        adjList = al;

        for (int i = 0; i < n; i++)
        {
            if (disc[i] == NIL)
                dfs(i);

            if(st.size())
            {
                vector<edge> new_component;
                while(st.size())
                {
                    new_component.push_back(st.back());
                    st.pop_back();
                }
                components.push_back(new_component);
                cnt++;
            }
        }
    }

};
